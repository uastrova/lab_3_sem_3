//
// Created by User on 17.12.2024.
//

#ifndef LAB3_DICTIONARY_H
#define LAB3_DICTIONARY_H

#include "HashTable.h"

template<typename KeyType, typename ValueType>
class Dictionary {
private:
    THashTable<KeyType, ValueType> hashTable;

public:
    Dictionary(size_t capacity = 16) : hashTable(capacity) {}

    void add(const KeyType &key, const ValueType &value) {
        if (hashTable.contains(key)) {
            throw std::runtime_error("Key already exists");
        }
        hashTable.insert(key, value);
    }

    void remove(const KeyType &key) {
        hashTable.remove(key);
    }

    ValueType &get(const KeyType &key) {
        return hashTable[key];
    }

    bool contains(const KeyType &key) {
        return hashTable.contains(key);
    }

    size_t size() const {
        return hashTable.size();
    }

    void clear() {
        hashTable.clear();
    }

    // Итерация по элементам хэш-таблицы
    class Iterator {
    private:
        typename THashTable<KeyType, ValueType>::Iterator it;
    public:
        Iterator(typename THashTable<KeyType, ValueType>::Iterator iterator) : it(iterator) {}

        std::pair<KeyType, ValueType> operator*() {
            return {(*it).key_, (*it).value_};
        }

        Iterator &operator++() {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return it != other.it;
        }
    };

    Iterator begin() {
        return Iterator(hashTable.begin());
    }

    Iterator end() {
        return Iterator(hashTable.end());
    }
};

#endif //LAB3_DICTIONARY_H
