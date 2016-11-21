// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"
#include <iostream>


template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key;
        Node* left;
        Node* right;
    };

    Node* root;
    int n;

    void deleteNodes(Node* n)
    {
        if (n==nullptr)
            return;
        else
        {
            if (n->left!=nullptr)
            {
                deleteNodes(n->left);
            }
            if (n->right!=nullptr)
            {
                deleteNodes(n->right);
            }
            delete n;
        }   
    }
    Node* insert(T e, Node* n)
    {
        if (n==nullptr)
        {
            ++this->n;
            return new Node{e,nullptr,nullptr};
        }
        else
        {
            T c=n->key;
            Node* t;
            if (e>c)
            {
                t=insert(e,n->right);
                if (n->right==nullptr)
                    n->right=t;
            }
            else if (e<c)
            {
                t=insert(e,n->left);
                if (n->left==nullptr)
                    n->left=t;
            }
            else ;
            return n;
        }
    }
    bool lookUp(T t, Node* n) const
    {
        if (n==nullptr)
            return 0;
        else
        {
            T c=n->key;
            if (c==t)
                return 1;
            else if (c>t)
                return lookUp(t,n->left);
            else
                return lookUp(t,n->right);
        }
    }
    Node* copyAll(Node* s)
    {
        if (s==nullptr)
            return nullptr;
        else
            return new Node{s->key,copyAll(s->left),copyAll(s->right)};
    }
    int depth(Node* n, int d) const
    {
        if (n==nullptr)
            return d-1;
        else
        {
            int le=depth(n->left,d+1);
            int ri=depth(n->right,d+1);
            //std::cout<<"d="<<d<<" "<<le<<" "<<ri<<std::endl;
            if (ri>le)
                return ri;
            else 
                return le;
        }

    }
    void traverse(Node* n) const
    {
        if (n==nullptr)
            return;
        else
        {
            traverse(n->left);
            std::cout<<n->key<<std::endl;
            traverse(n->right);
        }
    }
};


template <typename T>
BSTSet<T>::BSTSet():root(nullptr),n(0)
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    deleteNodes(root);   
}



template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s):root(copyAll(s.root)),n(s.n)
{

}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if (this!=&s)
    {
        deleteNodes(root);
        root=copyAll(s.root);
        n=s.n;
    }
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    root=insert(element,root);
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    //int d=depth(root,0);
    //std::cout<<"depth "<<d<<std::endl;
//    traverse(root);
    return lookUp(element,root);
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return n;
}



#endif // BSTSET_HPP

