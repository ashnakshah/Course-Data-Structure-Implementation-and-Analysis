// EmptySet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A set implementation that is always empty.  This has value in our
// timing tests, where we want to factor out how much time is being
// spent inside our set implementations, as opposed to parsing input
// files or other tasks.

#ifndef EMPTYSET_HPP
#define EMPTYSET_HPP

#include "Set.hpp"



template <typename T>
class EmptySet : public Set<T>
{
public:
    virtual bool isImplemented() const;
    virtual void add(const T& element);
    virtual bool contains(const T& element) const;
    virtual unsigned int size() const;
};


template <typename T>
bool EmptySet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void EmptySet<T>::add(const T& element)
{
}


template <typename T>
bool EmptySet<T>::contains(const T& element) const
{
    return false;
}


template <typename T>
unsigned int EmptySet<T>::size() const
{
    return 0;
}



#endif // EMPTYSET_HPP

