//
// Created by User on 17.12.2024.
//

#ifndef LAB3_ARRAYSEQUENCE_H
#define LAB3_ARRAYSEQUENCE_H

#pragma once
#include "Sequence.h"

template <typename T, bool is_const>
class ArraySequenceIterator;

template <typename T> class ArraySequence : public Sequence<T>
{
private:
    T *elements = nullptr;
    int capacity;
    int size;

    void Reserve(int newCapacity)
    {
        if (newCapacity <= capacity)
        {
            capacity = newCapacity;
            return;
        }

        T *newElements = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ArraySequenceIterator<T, false>;
    using const_iterator = ArraySequenceIterator<T, true>;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

    ArraySequence() : size(0), capacity(0), elements(nullptr)
    {
    }

    ArraySequence(int size) : size(size), capacity(size + 1), elements(nullptr)
    {
        if (size <= 0)
        {
            throw std::out_of_range("invalid argument for size");
        }
        else
        {
            elements = new T[capacity];
        }
    }

    ArraySequence(T *items, int count) : ArraySequence(count)
    {
        if (items == nullptr)
        {
            throw std::out_of_range("invalid argument in elems for constructor");
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                elements[i] = items[i];
            }
        }
    }

    ~ArraySequence()
    {
        delete[] elements;
    }

    iterator begin() noexcept
    {
        return iterator(elements);
    }
    iterator end() noexcept
    {
        return iterator(elements + size);
    }

    value_type GetFirst() const override
    {
        return elements[0];
    }

    value_type GetLast() const override
    {
        return elements[size - 1];
    }

    value_type Get(int index) const override
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("invalid argument");
        }
        return elements[index];
    }

    int GetLength() const override
    {
        return size;
    }

    void Set(const_reference value, int index)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("invalid argument");
        }
        elements[index] = value;
    }

    void Resize(int newSize)
    {
        if (newSize < 0)
        {
            throw std::invalid_argument("invalid argument");
        }
        if (newSize == 0)
        {
            delete[] elements;
            elements = nullptr;
        }
        if (newSize >= capacity)
        {
            Reserve(newSize * 2);
        }
        size = newSize;
    }

    void Append(const_reference item) override
    {
        this->Resize(this->GetLength() + 1);
        elements[this->GetLength() - 1] = item;
    }

    void Prepend(const_reference item) override
    {
        this->Resize(this->GetLength() + 1);
        for (int i = this->GetLength(); i > 0; i--)
        {
            elements[i] = elements[i - 1];
        }
        elements[0] = item;
    }

    void Clear()
    {
        if (elements) {
            delete[] elements;
            elements = nullptr;
        }
        size = 0;
        capacity = 0;
    }

    reference operator[](int index) override
    {
        if (size <= index)
        {
            throw std::out_of_range("Invalid argument");
        }
        return elements[index];
    }

    const_reference operator[](int index) const
    {
        if (size <= index)
        {
            throw std::out_of_range("Invalid argument");
        }
        return elements[index];
    }

    bool operator==(const ArraySequence<T>& array)
    {
        if (array.size != size)
        {
            return false;
        }
        for (int i = 0; i < size; i++)
        {
            if (array[i] != elements[i])
            {
                return false;
            }
        }
        return true;
    }

    ArraySequence<T> getSubSequence(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
        {
            throw std::out_of_range("Invalid indices for getSubSequence");
        }

        // Количество элементов в подпоследовательности
        int subSequenceSize = endIndex - startIndex + 1;

        // Создаем новый ArraySequence и копируем элементы
        ArraySequence<T> subSequence;
        for (int i = 0; i < subSequenceSize; i++)
        {
            subSequence.Append(elements[startIndex + i]);
        }

        return subSequence;
    }
};

#endif //LAB3_ARRAYSEQUENCE_H
