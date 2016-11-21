// OutputSpellCheckerListener.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A SpellCheckListener that prints output describing misspellings
// as they're found.

#ifndef OUTPUTSPELLCHECKERLISTENER_HPP
#define OUTPUTSPELLCHECKERLISTENER_HPP

#include <iostream>
#include "SpellCheckerListener.hpp"



class OutputSpellCheckerListener : public SpellCheckerListener
{
public:
    OutputSpellCheckerListener(std::ostream& out);

    virtual void misspellingFound(
        const std::string& word, const std::string& line,
        const std::vector<std::string>& suggestions);

private:
    std::ostream& out;
};



#endif // OUTPUTSPELLCHECKERLISTENER_HPP

