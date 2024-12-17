//
// Created by User on 17.12.2024.
//

#ifndef LAB3_ARRAYITERATOR_H
#define LAB3_ARRAYITERATOR_H

#pragma once
#include "ArraySequence.h"
#include "Sequence.h"
#include <iterator>
#include <type_traits>
#include <cstddef>

template<typename T, bool is_const>
class ArraySequenceIterator
{
private:
    using elem_ptr_t = std::conditional_t<is_const, const T, T>*;

    elem_ptr_t elem_;

public:
    using  value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = std::conditional_t<is_const, const T, T>*;
    using reference = std::conditional_t<is_const, const T, T>&;
    using iterator_category = std::random_access_iterator_tag;

    friend ArraySequence<T>;
    friend ArraySequenceIterator<T, !is_const>;

    ArraySequenceIterator() : elem_(nullptr) {};

    ArraySequenceIterator(elem_ptr_t elem): elem_(elem) {};

    template<bool other_const>
    ArraySequenceIterator(ArraySequenceIterator<T, other_const>& o) noexcept requires (is_const >= other_const): elem_(o.elem_) {};

    template<bool other_const>
    ArraySequenceIterator& operator =(const ArraySequenceIterator<T, other_const>& o) noexcept requires (is_const >= other_const) // requires не позволяет скопировать из const
    {
        elem_ = o.elem_;
        return *this;
    }

    ArraySequenceIterator& operator ++ () noexcept  //префиксный
    {
        ++elem_;
        return *this;
    }

    ArraySequenceIterator operator ++ (int) noexcept  //постфиксный
    {
        ArraySequenceIterator res(elem_);
        elem_ ++;
        return res;
    }

    reference operator * () const noexcept
    {
        return *elem_;
    }

    template<bool other_const>
    bool operator == (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ == o.elem_;
    }

    template<bool other_const>
    bool operator != (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ != o.elem_;
    }

    ArraySequenceIterator& operator -- () noexcept
    {
        --elem_;
        return *this;
    }

    ArraySequenceIterator operator -- (int) noexcept
    {
        ArraySequenceIterator res(elem_);
        elem_ = elem_->prev;
        return res;
    }

    template<bool other_const>
    bool operator > (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ > o.elem_;
    }

    template<bool other_const>
    bool operator >= (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ >= o.elem_;
    }

    template<bool other_const>
    bool operator < (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ < o.elem_;
    }

    template<bool other_const>
    bool operator <= (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ <= o.elem_;
    }

    template<bool other_const>
    difference_type operator - (const ArraySequenceIterator<T, other_const>& o) const noexcept
    {
        return elem_ - o.elem_;
    }

    ArraySequenceIterator operator + (difference_type n) const noexcept
    {
        ArraySequenceIterator res(elem_ + n);
        return res;
    }


    ArraySequenceIterator& operator += (difference_type n) noexcept
    {
        elem_ += n;
        return *this;
    }

    ArraySequenceIterator operator - (difference_type n) const noexcept
    {
        ArraySequenceIterator res(elem_ - n);
        return res;
    }

    ArraySequenceIterator& operator -= (difference_type n) noexcept
    {
        elem_ -= n;
        return *this;
    }

    reference operator[](difference_type n) const
    {
        return elem_[n];
    }

    template<bool other_const>
    friend ArraySequenceIterator operator+(difference_type n, const ArraySequenceIterator<T, other_const>& o) {
        return ArraySequenceIterator(o.elem_ + n);
    }


};

#endif //LAB3_ARRAYITERATOR_H
