// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"
#include <iostream>

template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;
    
private:
    struct Node
    {
        T key;
        Node* next;
    };
    HashFunction hashFunction;
    Node** hashArray;
    int n;
    int cap;
    
    void deleteHashArray()
    {
        for (int i=0;i<cap;i++)
        {
            Node* temp=hashArray[i];
            while (temp!=nullptr)
            {
                Node* next=temp->next;
                delete temp;
                temp=next;
            }
        }
            delete [] hashArray;
    }
    Node** copyAll(Node** s, int c, int mul=1)
    {
        int new_cap=c*mul;
        Node** nn=new Node* [new_cap]; 
        for (int i=0;i<c;i++)
        {
            Node* temp=s[i];
            int index;
            while (temp!=nullptr)
            {
//                std::cout<<"REHASHED VALUE of "<<temp->key<<" : "<<(hashFunction(temp->key)%(new_cap-1))<<std::endl;
                index=hashFunction(temp->key)%(new_cap-1);
                nn[index]=new Node{temp->key,nn[index]};
                temp=temp->next;
            }
        }
        return nn;
    }
    void resize()
    {
//        std::cout<<"RESIZE";
        Node** temp=copyAll(hashArray,cap,2);
        deleteHashArray();
        hashArray=temp;
        cap=cap*2;
//        std::cout<<"CAP:"<<cap<<std::endl;
//        traverse();
    }
    void traverse() const
    {
        for (int i=0;i<cap;i++)
        {
            Node* temp=hashArray[i];
            std::cout<<"I["<<i<<"]={";
            while (temp!=nullptr)
            {
                std::cout<<temp->key<<" ";
                temp=temp->next;
            }
            std::cout<<"}"<<std::endl;
        } 
    }
};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction},hashArray(new Node* [DEFAULT_CAPACITY]),n(0),cap(DEFAULT_CAPACITY)
{
    for (int i=0;i<cap;i++)
    {
        hashArray[i]=nullptr;
    }
}


template <typename T>
HashSet<T>::~HashSet()
{
    deleteHashArray();    
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction},hashArray(copyAll(s.hashArray,s.cap)),n(s.n),cap(s.cap)
{
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        hashFunction = s.hashFunction;
        deleteHashArray();
        hashArray=copyAll(s.hashArray,s.cap);
        n=s.n;
        cap=s.cap;
    }
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    if ((double)n/cap>0.8)
        resize();
    int value=hashFunction(element)%(cap-1);
    if (contains(element))
        return;
    ++n;
    hashArray[value]=new Node{element,hashArray[value]};
//    std::cout<<"ADD:"<<std::endl;  
//    traverse();
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
//    std::cout<<"ELEMENT:"<<element<<" HASHVALUE:"<<(hashFunction(element)%(cap-1))<<std::endl;
//    traverse();
    Node* no=hashArray[hashFunction(element)%(cap-1)];
    while (no!=nullptr)
    {
        if (element==no->key)
            return 1;
        no=no->next;
    }
    return 0;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return n;
}



#endif // HASHSET_HPP

