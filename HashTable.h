//
// Created by User on 12.12.2024.
//

#ifndef LAB3_HASHTABLE_H
#define LAB3_HASHTABLE_H

#include <cstddef>
#include <functional>
#include <stdexcept>


template<typename T>
size_t hash(const T &key) {
    return std::hash<T>{}(key);
}

template<class T1, class T2>
class THashTable {
public:
    class Node {
    public:
        T1 key_;
        T2 value_;
        Node() = default;
        Node(const T1 &key, const T2 &value, bool is_taken, bool is_last, size_t prev, size_t next) : key_(key), value_(value), is_taken_(is_taken), is_last_(is_last), prev_(prev), next_(next) {}

        ~Node() = default;

        bool isTaken() const {
            return is_taken_;
        }

        bool isLast() const {
            return is_last_;
        }

        size_t getPrev() const {
            return prev_;
        }

        size_t getNext() const {
            return next_;
        }

        void setTaken() {
            is_taken_ = true;
        }

        void setNotTaken() {
            is_taken_ = false;
        }

        void setLast() {
            is_last_ = true;
        }

        void setNotLast() {
            is_last_ = false;
        }

        void setNext(size_t next) {
            next_ = next;
        }

        void setPrev(size_t prev) {
            prev_ = prev;
        }
    private:
        bool is_taken_ = false;
        bool is_last_ = false;
        size_t prev_{};
        size_t next_{};

    };

    class Iterator {
    public:
        virtual Node &operator*() const {
            return *ptr;
        }
        virtual bool operator==(const Iterator &other) const {
            return ptr == other.ptr;
        }
        virtual bool operator!=(const Iterator &other) const {
            return ptr != other.ptr;
        }
        virtual Iterator &operator++() {
            if ((*ptr).isLast()) {
                ++ptr;
                return *this;
            }
            ++ptr;
            while (!(*ptr).isTaken() && !(*ptr).isLast()) {
                ++ptr;
            }
            return *this;
        }

        virtual ~Iterator() = default;

        Iterator(Node *init_ptr) : ptr(init_ptr) {}

    private:
        Node *ptr = nullptr;
    };

    virtual T2 &operator[](const T1 &key) {
        auto result = find(key);
        if (result == end()) {
            throw std::out_of_range("Key not found");
        }
        return (*result).value_;
    }

    THashTable &operator=(const THashTable &other) {
        clear();
        try { table_ = new Node[other.capacity_]; }
        catch (std::exception &e) {
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        size_ = 0;
        auto other_not_const = const_cast<THashTable &>(other);
        for (auto &i : other_not_const) {
            insert(i.key_, i.value_);
        }
        return *this;
    }

    THashTable &operator=(THashTable &&other) {
        if (this != &other) {
            clear();
            table_ = other.table_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            other.table_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    THashTable() = default;

    THashTable(size_t capacity) {
        table_ = new Node[capacity];
        capacity_ = capacity;
        for (size_t i = 0; i < capacity_; ++i) {
            table_[i].setNext(i);
            table_[i].setPrev(i);
        }
    }

    THashTable(THashTable &other) {
        try { table_ = new Node[other.capacity_]; }
        catch (std::exception &e) {
            throw std::bad_alloc();
        }
        capacity_ = other.capacity_;
        for (auto &i : other) {
            insert(i.key_, i.value_);
        }
        size_ = other.size();
    }

    THashTable(THashTable &&other) : table_(other.table_), capacity_(other.capacity_), size_(other.size_) {
        other.table_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    virtual ~THashTable() {
        clear();
    }

    virtual Iterator begin() {
        for (size_t i = 0; i < capacity_; ++i) {
            if (table_[i].isTaken()) {
                return Iterator(table_ + i);
            }
        }
        return end();
    }

    virtual Iterator end() {
        return Iterator(table_ + capacity_);
    }

    virtual Iterator find(const T1 &key) {
        if (size_ == 0) {
            return end();
        }
        auto index = hash(key) % capacity_;
        while (table_[index].key_ != key || !table_[index].isTaken()) {
            index = table_[index].getNext();
            if (index == (hash(key) % capacity_)) {
                return end();
            }
        }
        return Iterator(table_ + index);
    }

    virtual void insert(const T1 &key, const T2 &value) {
        if (size_ == capacity_) {
            resize();
        }
        auto index = hash(key) % capacity_;
        auto hash_index = index;
        auto prev_index = table_[index].getPrev();
        auto next_index = index;
        while (table_[index].isTaken()) {
            index = (index + 1) % capacity_;
        }
        if (index == (hash(key) % capacity_)) {
            prev_index = index;
        }
        auto is_last_ = (index == capacity() - 1) ? true : false;
        table_[index] = Node(key, value, true, is_last_, prev_index, next_index);
        if (table_[hash_index].getPrev() != hash_index) {
            auto pre_hash_index = table_[hash_index].getPrev();
            table_[pre_hash_index].setNext(index);
        }
        table_[hash_index].setPrev(index);
        if (table_[hash_index].getNext() == hash_index) {
            table_[hash_index].setNext(index);
        }
        ++size_;
    }

    virtual void remove(const T1 &key) {
        auto hash_index = hash(key) % capacity_;
        auto element = find(key);
        if (element == end()) {
            throw std::out_of_range("Key not found");
        }
        if ((*element).key_ == table_[hash_index].key_) {
            auto next = table_[hash_index].getNext();
            table_[hash_index].key_ = table_[next].key_;
            table_[hash_index].value_ = table_[next].value_;
            table_[hash_index].setNext(table_[next].getNext());
            table_[next].setNotTaken();
            auto new_next = table_[hash_index].getNext();
            table_[new_next].setPrev(hash_index);
        }
        else {
            auto next = (*element).getNext();
            table_[next].setPrev((*element).getPrev());
            (*element).setNotTaken();
        }
        --size_;
    }

    virtual bool contains(const T1 &key) {
        return find(key) != end();
    }

    virtual size_t size() const {
        return size_;
    }

    virtual size_t capacity() const {
        return capacity_;
    }

    virtual void clear() {
        size_ = 0;
        capacity_ = 0;
        delete[] table_;
        table_ = nullptr;
    }
private:

    Node *table_ = nullptr;

    size_t capacity_ = 0;

    size_t size_ = 0;

    void resize() {
        auto old_capacity = capacity_;
        if (capacity_ == 0)
            capacity_ = 1;
        else capacity_ *= 2;
        Node *new_table;
        try { new_table = new Node[capacity_]; }
        catch (...) {
            delete[] table_;
            throw std::bad_alloc();
        }
        auto *old_table = table_;
        table_ = new_table;
        size_ = 0;
        for (size_t i = 0; i < old_capacity; ++i) {
            insert(old_table[i].key_, old_table[i].value_);
        }
        for (size_t i = 0; i < capacity_; ++i) {
            if (!table_[i].isTaken()) {
                table_[i].setNext(i);
                table_[i].setPrev(i);
            }
        }
        table_[capacity_ - 1].setLast();
        delete[] old_table;
    }
};


#endif //LAB3_HASHTABLE_H
