//
// Created by User on 17.12.2024.
//

#ifndef LAB3_MOSTFREQUENT_H
#define LAB3_MOSTFREQUENT_H

#include "Dictionary.h"
#include <fstream>

inline Dictionary<std::string, int> theMostFrequentSubsequences(const std::string &input, int lmin, int lmax) {
    Dictionary<std::string, int> result;

    for (int i = 0; i < input.length(); i++) {
        for (int j = lmin; j <= lmax; j++) {
            if (i + j <= input.length()) {
                std::string word = input.substr(i, j);
                if (result.contains(word)) {
                    result.get(word) += 1; // Увеличиваем значение
                } else {
                    result.add(word, 1); // Добавляем новую запись
                }
            }
        }
    }

    return result;
}

inline void FindingTheMostFrequentSubsequence(std::string input, int lmin, int lmax)
{
    Dictionary<std::string, int> result = theMostFrequentSubsequences(input, lmin, lmax);
    std::string outputFilePath = "C:/c++Programs/lab_3_sem_3/outputSequences.txt";
    // Открытие файла для записи
    std::ofstream outputFile(outputFilePath);
    if (!outputFile) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    // Запись результатов в файл
    for (auto it = result.begin(); it != result.end(); ++it) {
        auto [key, value] = *it;
        outputFile << "Subsequence: " << key << ", Frequency: " << value << std::endl;
    }

    outputFile.close(); // Закрытие файла

}


#endif //LAB3_MOSTFREQUENT_H
