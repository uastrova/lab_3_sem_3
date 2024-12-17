//
// Created by User on 17.12.2024.
//

#ifndef LAB3_BOOK_H
#define LAB3_BOOK_H

#include "Pages.h"
#include "vector.h"

class Book
{
private:
    Vector<Page> book_; // хранит страницы книги
public:
    Book() = default;

    void append(Page& insert_page)
    {
        book_.push_back(insert_page);
    }

    Book(Vector<Page>& book)
    {
        book_ = book;
    }

    Book(Vector<Page>&& other) noexcept
        : book_(std::move(other)) {};

    size_t GetPageCount()
    {
        return book_.get_size();
    }

    Page GetPage(int i)
    {
        return book_[i];
    }
};

#endif //LAB3_BOOK_H

#endif //LAB3_BOOK_H
