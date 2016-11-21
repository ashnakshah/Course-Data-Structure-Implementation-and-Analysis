// WordSetLoader.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun

#include <algorithm>
#include <cctype>
#include <fstream>
#include "WordSetLoader.hpp"



void WordSetLoader::load(const std::string& wordFilePath, Set<std::string>& wordSet)
{
    std::ifstream wordFile{wordFilePath};

    std::string word;

    while (std::getline(wordFile, word))
    {
        std::transform(
            word.begin(), word.end(), word.begin(),
            [](auto c) { return std::toupper(c); });

        word.erase(
            std::remove_if(
                word.begin(), word.end(),
                [](auto c) { return c == '\r' || c == '\n'; }),
            word.end());

        wordSet.add(word);
    }
}

