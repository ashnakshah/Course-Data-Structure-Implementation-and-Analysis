// WordChecker.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// The WordChecker class can check the spelling of single words and generate
// suggestions for words that have been misspelled.
//
// You can add anything you'd like to this class, but you will not be able
// to modify the declarations of any of its member functions, since the
// provided code calls into this class and expects it to look as originally
// given.

#ifndef WORDCHECKER_HPP
#define WORDCHECKER_HPP

#include <string>
#include <vector>
#include "Set.hpp"
#include <algorithm>
#include <iostream>

class WordChecker
{
public:
    // The constructor requires a Set of words to be passed into it.  The
    // WordChecker will store a reference to a const Set, which it will use
    // whenever it needs to look up a word.
    WordChecker(const Set<std::string>& words);


    // wordExists() returns true if the given word is spelled correctly,
    // false otherwise.
    bool wordExists(const std::string& word) const;


    // findSuggestions() returns a vector containing suggested alternative
    // spellings for the given word, using the five algorithms described in
    // the project write-up.
    std::vector<std::string> findSuggestions(const std::string& word) const;


private:
    const Set<std::string>& words;
    static int count;
    bool checker(std::string s, const std::vector<std::string>& v) const
    {
        return words.contains(s) && std::find(v.begin(),v.end(),s)==v.end();
    }
    void swapAdj(std::string s,std::vector<std::string>& v) const
    {
        for (int i=1;i<s.size() && s.size()>1;i++)
        {
            std::string clone (s);
            char temp=clone[i-1];
            clone[i-1]=clone[i];
            clone[i]=temp;
            if (checker(clone,v))
                v.push_back(clone);
        }
    }
    void replaceInBetween(std::string s, std::vector<std::string>& v) const
    {
        for (int i=0;i<=s.size();i++)
        {
            for (int j=65;j<91;j++)
            {
                std::string clone(s);
                clone.insert(i,1,(char)j);
//                std::cout<<"INB:"<<clone<<std::endl;
                if (checker(clone,v))
                    v.push_back(clone);
            }
        }
    }
    void replaceEach(std::string s, std::vector<std::string>& v) const
    {
        for (int i=0;i<s.size();i++)
        {
            for (int j=65;j<91;j++)
            {
                std::string clone(s);
                clone[i]=(char)j;
                if (checker(clone,v))
                    v.push_back(clone);
            }
        }
    }
    void deleteC(std::string s, std::vector<std::string>& v) const
    {
        for (int i=0;i<s.size();i++)
        {
            std::string clone(s);
            clone.erase(i,1);
            if (checker(clone,v))
                v.push_back(clone);
        }
    }
    void splitC(std::string s, std::vector<std::string>& v) const
    {
        int si=s.size();
        for (int i=1;si>1 && i<si;i++)
        {
            std::string clone (s);
            clone.insert(i,1,' ');
//            std::cout<<"SPLITC"<<std::endl;
//            std::cout<<"CLONE:"<<clone<<std::endl;
//            std::cout<<"first:"<<clone.substr(0,i)<<" | "<<clone.substr(i+1,si-i)<<std::endl;
            if (checker(clone.substr(0,i),v) && checker(clone.substr(i+1,si-i),v))
                v.push_back(clone);
        }
    }

};



#endif // WORDCHECKER_HPP

