//
// Created by User on 17.12.2024.
//

#ifndef LAB3_ITERATOR_H
#define LAB3_ITERATOR_H

#include <cstddef>
#include <iterator>
#include <iostream>

template <typename T> class Vector;


template <typename T> class Vector_iterator
{
private:
    T *p;

public:
    friend class Vector<T>;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

    Vector_iterator(T *p);
    Vector_iterator(const Vector_iterator &it);

    Vector_iterator<T> operator+(const size_t &num) const noexcept;
    Vector_iterator<T> operator-(const size_t &num) const noexcept;

    size_t operator-(const Vector_iterator &other) const;
    bool operator!=(const Vector_iterator &other) const noexcept;
    bool operator==(const Vector_iterator &other) const noexcept;
    bool operator>(const Vector_iterator &other) const noexcept;
    bool operator<(const Vector_iterator &other) const noexcept;

    T &operator*() const noexcept;

    Vector_iterator &operator++() noexcept;
    Vector_iterator &operator--() noexcept;
};

template <typename T> Vector_iterator<T>::Vector_iterator(T *p) : p(p)
{
}

template <typename T> Vector_iterator<T>::Vector_iterator(const Vector_iterator &it)
{
    p = it.p;
}

template <typename T> Vector_iterator<T> Vector_iterator<T>::operator+(const size_t &num) const noexcept
{
    return Vector_iterator<T>(p + num);
}

template <typename T> Vector_iterator<T> Vector_iterator<T>::operator-(const size_t &num) const noexcept
{
    return Vector_iterator<T>(p - num);
}

template <typename T> size_t Vector_iterator<T>::operator-(const Vector_iterator &other) const
{
    if (*this < other)
        throw std::invalid_argument("Cannot subtract iterators from different vectors");
    return p - other.p;
}

template <typename T> bool Vector_iterator<T>::operator!=(const Vector_iterator &other) const noexcept
{
    return p != other.p;
}

template <typename T> bool Vector_iterator<T>::operator==(const Vector_iterator &other) const noexcept
{
    return p == other.p;
}

template <typename T> bool Vector_iterator<T>::operator>(const Vector_iterator &other) const noexcept
{
    return p > other.p;
}


template <typename T> bool Vector_iterator<T>::operator<(const Vector_iterator &other) const noexcept
{
    return p < other.p;
}


template <typename T> T &Vector_iterator<T>::operator*() const noexcept
{
    return *p;
}

template <typename T> Vector_iterator<T> &Vector_iterator<T>::operator++() noexcept
{
    ++p;
    return *this;
}

template <typename T> Vector_iterator<T> &Vector_iterator<T>::operator--() noexcept
{
    --p;
    return *this;
}

#endif //LAB3_ITERATOR_H
