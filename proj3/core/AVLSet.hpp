// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <cmath>
#include <iostream>

template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
 
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        T key;
        Node* left;
        Node* right;
        int dep;
    };

    Node* root;
    int n;
    void deleteNodes(Node* n)
    {
        if (n==nullptr)
            return ;
        else
        {
            if (n->left!=nullptr)
                deleteNodes(n->left);
            if (n->right!=nullptr)
                deleteNodes(n->right);
            delete n;
        }
    }
    bool lookUp(T e, Node* n) const
    {
        if (n==nullptr)
            return 0;
        else
        {
            T c=n->key;
            if (c==e)
                return 1;
            else if (c>e)
                return lookUp(e,n->left);
            else
                return lookUp(e,n->right);
        }
    }
    Node* copyAll(Node* s)
    {
        if (s==nullptr)
            return nullptr;
        else
            return new Node{s->key,copyAll(s->left),copyAll(s->right),s->dep};
    }
    int depth(Node* n, int d)
    {
        if (n==nullptr)
            return d-1;
        else
        {
            int l=depth(n->left,d+1);
            int r=depth(n->right,d+1);
            if (r>l)
                return r;
            else
                return l;
        }
    }
    void rotate(Node* n, int lfd, int rgd)
    {
//        std::cout<<"Node:"<<n->key<<" Needs to rotate"<<std::endl;
        T tempK=n->key;
        Node* tempN;
        //int nl=depth(n->left,0);
        //int nr=depth(n->right,0);
        int nl=n->left!=nullptr?n->left->dep+1:0;
        int nr=n->right!=nullptr?n->right->dep+1:0;
        if (lfd>rgd)
        {
            if (nr>nl)
            {
                T tempS=n->left->key;
                n->left->key=n->left->right->key;
                n->left->right->key=tempS;
                Node* tempSN=n->left->right->right;
                n->left->right->right=n->left->right->left;
                n->left->right->left=n->left->left;
                n->left->left=n->left->right;
                n->left->right=tempSN;
                nl=n->left->left->left!=nullptr?n->left->left->left->dep+1:0;
                nr=n->left->left->right!=nullptr?n->left->left->right->dep+1:0;
                n->left->left->dep=nl>nr?nl:nr;
                int t=n->left->right!=nullptr?n->left->right->dep+1:0;
                n->left->dep=n->left->dep>t?n->left->dep+1:t;
            }
            n->key=n->left->key;
            n->left->key=tempK;
            tempN=n->left->left;
            n->left->left=n->left->right;
            n->left->right=n->right;
            n->right=n->left;
            n->left=tempN;
            int tempLD=n->right->left!=nullptr?n->right->left->dep+1:0;
            int tempRD=n->right->right!=nullptr?n->right->right->dep+1:0;
            n->right->dep=tempRD>tempLD?tempRD:tempLD;
            n->dep=n->left->dep>n->right->dep?n->left->dep+1:n->right->dep+1;
        }
        else
        {
            if (nl>nr)
            {
                T tempS=n->right->key;
                n->right->left->key=n->right->key;
                n->right->key=tempS;
                Node* tempSN=n->right->left->left;
                n->right->left->left=n->right->left->right;
                n->right->left->right=n->right->right;
                n->right->right=n->right->left;
                n->right->left=tempSN;
                nl=n->right->right->left!=nullptr?n->right->right->left->dep+1:0;
                nr=n->right->right->right!=nullptr?n->right->right->right->dep+1:0;
                n->right->right->dep=nl>nr?nl:nr;
                int t=n->right->left!=nullptr?n->right->left->dep+1:0;
                n->right->dep=t>n->right->right->dep?t:n->right->right->dep+1;
            }
            n->key=n->right->key;
            n->right->key=tempK;
            tempN=n->right->right;
            n->right->right=n->right->left;
            n->right->left=n->left;
            n->left=n->right;
            n->right=tempN;
            int tempLD=n->left->left!=nullptr?n->left->left->dep+1:0;
            int tempRD=n->left->right!=nullptr?n->left->right->dep+1:0;
            n->left->dep=tempLD>tempRD?tempLD:tempRD;
            n->dep=n->left->dep>n->right->dep?n->left->dep+1:n->right->dep+1;
        }
        //traverse(n);
    }
    Node* insert(T e, Node* n)
    {
        if (n==nullptr)
        {
            ++this->n;
            return new Node{e,nullptr,nullptr,0};
        }
        else
        {
            T c=n->key;
            Node* t;
            int lfd=n->left==nullptr?0:n->left->dep+1;
            int rgd=n->right==nullptr?0:n->right->dep+1;
            if (e>c)
            {
                t=insert(e,n->right);
                if (n->right==nullptr)
                    {
                        n->right=t;
                    }
                ++rgd;
            }
            else if (e<c)
            {
                t=insert(e,n->left);
                if (n->left==nullptr)
                {
                    n->left=t;
                }
                ++lfd;
            }
            else ;
            //lfd=depth(n->left,0);
            //rgd=depth(n->right,0);
            if (lfd>rgd)
                n->dep=lfd;
            else 
                n->dep=rgd;
            if (std::abs(lfd-rgd)>1)
                rotate(n,lfd,rgd);
            return n;
        }
    }
    void traverse(Node* n) const
    {
        if (n==nullptr)
            return ;
        else
        {
            traverse(n->left);
            std::cout<<n->key<<std::endl;
            traverse(n->right);
        }
    }

};


template <typename T>
AVLSet<T>::AVLSet():root(nullptr),n(0)
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    deleteNodes(root);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    root=copyAll(s.root);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    if (this!=&s)
    {
        deleteNodes(root);
        root=copyAll(s.root);
    }
    n=s.n;
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    root=insert(element,root);
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
//    std::cout<<"root:"<<root->key<<std::endl;
//    traverse(root);
    return lookUp(element,root);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return n;
}



#endif // AVLSET_HPP

