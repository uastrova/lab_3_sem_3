//
// Created by User on 17.12.2024.
//

#ifndef LAB3_SEQUENCE_H
#define LAB3_SEQUENCE_H

#pragma once

template <typename T> class Sequence
{
public:
    virtual ~Sequence()
    {
    }
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual void Append(const T &item) = 0;
    virtual void Prepend(const T &item) = 0;
    virtual T& operator[](int index) = 0;
};

#endif //LAB3_SEQUENCE_H
