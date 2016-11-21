// SpellChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun

#include "SpellChecker.hpp"



void SpellChecker::run(const WordChecker& wordChecker, TextFileReader& reader)
{
    while (!reader.noMoreWords())
    {
        if (!wordChecker.wordExists(reader.currentWord()))
        {
            notifyMisspellingFound(
                reader.currentWord(), reader.currentLine(),
                wordChecker.findSuggestions(reader.currentWord()));
        }

        reader.advanceToNextWord();
    }
}


void SpellChecker::notifyMisspellingFound(
    const std::string& word, const std::string& line,
    const std::vector<std::string>& suggestions)
{
    notifyObservers(
        [&](auto listener)
        {
            listener->misspellingFound(word, line, suggestions);
        });
}

