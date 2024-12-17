//
// Created by User on 17.12.2024.
//

#ifndef LAB3_ROWS_H
#define LAB3_ROWS_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fstream>
#include <sstream>
#include "vector.h"

class Row
{
private:
    std::string row_;
public:
    Row() = default;

    Row(std::string& get_row)
    {
        row_ = get_row;
    }

    void append(std::string& word)
    {
        row_ = row_ + word;
    }

    const std::string& get() const
    {
        return row_;
    }
};

Vector<Row> lexer(std::string& text, int row_size)
{
    Vector<Row> result;
    int count = 0;
    std::istringstream wordsStream(text);
    std::string line;
    std::string word;
    while (wordsStream >> word)
    {
        line = line + word + " ";
        count++;
        if (count == row_size)
        {
            Row item(line);
            result.push_back(item);
            line.clear();
            count = 0;
        }
    }
    if (!line.empty())
    {
        Row item2(line);
        result.push_back(item2);
        line.clear();
        count = 0;
    }
    return result;
}


#endif //LAB3_ROWS_H
