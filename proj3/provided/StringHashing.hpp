// StringHashing.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A collection of hash functions that are capable of hashing strings.

#ifndef STRINGHASHING_HPP
#define STRINGHASHING_HPP

#include <string>



unsigned int hashStringAsZero(const std::string& word);
unsigned int hashStringAsSum(const std::string& word);
unsigned int hashStringAsProduct(const std::string& word);



#endif // STRINGHASHING_HPP

