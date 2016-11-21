// ListSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An implementation of the Set<T> class template, which uses a singly-
// linked list with a head pointer to store its keys.  The keys are not
// sorted in any particular order.

#ifndef LISTSET_HPP
#define LISTSET_HPP

#include "Set.hpp"



template <typename T>
class ListSet : public Set<T>
{
public:
    ListSet();
    virtual ~ListSet();
    ListSet(const ListSet& s);
    ListSet& operator=(const ListSet& s);

    virtual bool isImplemented() const;
    virtual void add(const T& element);
    virtual bool contains(const T& element) const;
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key;
        Node* next;
    };


    Node* head;


private:
    void copyAll(const ListSet& s);
    void destroyAll();
};



template <typename T>
ListSet<T>::ListSet()
    : head{nullptr}
{
}


template <typename T>
ListSet<T>::~ListSet()
{
    destroyAll();
}


template <typename T>
ListSet<T>::ListSet(const ListSet& s)
    : head{nullptr}
{
    copyAll(s);
}


template <typename T>
ListSet<T>& ListSet<T>::operator=(const ListSet& s)
{
    if (this != &s)
    {
        destroyAll();
        head = nullptr;
        copyAll(s);
    }

    return *this;
}


template <typename T>
bool ListSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void ListSet<T>::add(const T& element)
{
    Node* curr = head;

    while (curr != nullptr)
    {
        if (curr->key == element)
        {
            return;
        }

        curr = curr->next;
    }

    head = new Node{element, head};
}


template <typename T>
bool ListSet<T>::contains(const T& element) const
{
    Node* curr = head;

    while (curr != nullptr)
    {
        if (curr->key == element)
        {
            return true;
        }

        curr = curr->next;
    }

    return false;
}


template <typename T>
unsigned int ListSet<T>::size() const
{
    Node* curr = head;
    unsigned int count = 0;

    while (curr != nullptr)
    {
        ++count;
        curr = curr->next;
    }

    return count;
}


template <typename T>
void ListSet<T>::copyAll(const ListSet& s)
{
    Node* curr = s.head;

    while (curr != nullptr)
    {
        head = new Node{curr->key, head};
        curr = curr->next;
    }
}


template <typename T>
void ListSet<T>::destroyAll()
{
    Node* curr = head;

    while (curr != nullptr)
    {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}



#endif // LISTSET_HPP

