//
// Created by User on 17.12.2024.
//

#ifndef LAB3_GENERATOR_H
#define LAB3_GENERATOR_H
#include <string>
#include <ctime>
#include <random>

inline std::string helpful_array = "abcdefghijklmnopqrstuvwxyz";

inline std::string GenerateSequence(int count)
{
    std::string result = "";
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> dist1(0, 25);
    for (int i = 0; i < count; i++)
    {
        result += helpful_array[dist1(generator)];
    }

    return result;
}

#endif //LAB3_GENERATOR_H
