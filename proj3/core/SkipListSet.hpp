// SkipListSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A SkipListSet is an implementation of a Set that is a skip list, implemented
// as we discussed in lecture.  A skip list is a sequence of levels
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector), *except* that you can use
// std::vector to store your levels (e.g., pointers to the head node of each
// level) if you'd like.  Beyond that, you'll need to implement your own
// dynamically-allocated nodes with pointers connecting them.
//
// Each node should contain only two pointers: one to the node that follows it
// on the same level and another to the equivalent node on the level below it.
// Additional pointers use more memory but don't enable any techniques not
// enabled by the other two.
//
// A couple of utilities are included here: SkipListKind and SkipListKey.
// You can feel free to use these as-is and probably will not need to
// modify them.

#ifndef SKIPLISTSET_HPP
#define SKIPLISTSET_HPP

#include "Set.hpp"
#include <vector>
#include <random>
#include <iostream>



// SkipListKind indicates a kind of key: a normal one, the special key
// -INF, or the special key +INF.  It's necessary for us to implement
// the notion of -INF and +INF separately, since we're building a class
// template and not all types of keys would have a reasonable notion of
// -INF and +INF.

enum class SkipListKind
{
    Normal,
    NegInf,
    PosInf
};




// A SkipListKey represents a single key in a skip list.  It is possible
// to compare these keys using < or == operators (which are overloaded here)
// and those comparisons respect the notion of whether each key is normal,
// -INF, or +INF.

template <typename T>
class SkipListKey
{
public:
    SkipListKey(SkipListKind kind, const T& key);
    
//    void print(){std::cout<<"{"<<key<<"}";}
    bool operator==(const SkipListKey& other) const;
    bool operator<(const SkipListKey& other) const;

private:
    SkipListKind kind;
    T key;
};


template <typename T>
SkipListKey<T>::SkipListKey(SkipListKind kind, const T& key)
    : kind{kind}, key{key}
{
}


template <typename T>
bool SkipListKey<T>::operator==(const SkipListKey& other) const
{
    return kind == other.kind
        && (kind != SkipListKind::Normal || key == other.key);
}


template <typename T>
bool SkipListKey<T>::operator<(const SkipListKey& other) const
{
    switch (kind)
    {
    case SkipListKind::NegInf:
        return other.kind != SkipListKind::NegInf;

    case SkipListKind::PosInf:
        return false;

    default: // SkipListKind::Normal
        return other.kind == SkipListKind::PosInf
            || (other.kind == SkipListKind::Normal && key < other.key);
    }
}




template <typename T>
class SkipListSet : public Set<T>
{
public:
    // Initializes an SkipListSet to be empty.
    SkipListSet();

    // Cleans up the SkipListSet so that it leaks no memory.
    virtual ~SkipListSet();

    // Initializes a new SkipListSet to be a copy of an existing one.
    SkipListSet(const SkipListSet& s);

    // Assigns an existing SkipListSet into another.
    SkipListSet& operator=(const SkipListSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a SkipListSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in an expected time
    // of O(log n) (i.e., over the long run, we expect the average to be
    // O(log n)) with very high probability.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in an expected time of O(log n)
    // (i.e., over the long run, we expect the average to be O(log n))
    // with very high probability.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct Node
    {
        SkipListKey<T> sKey;
        Node* below;
        Node* next;
    };
    std::vector< Node* > skipList;
    int sizeS;

    void addEmptyLevel(std::vector< Node* >& v)
    {
        SkipListKey<T> negSen (SkipListKind::NegInf,T());
        SkipListKey<T> posSen (SkipListKind::PosInf,T());
        if (skipList.size()==0)
            skipList.push_back(new Node{negSen,nullptr,new Node{posSen,nullptr,nullptr}});
        else
        {
            int lastL=skipList.size()-1;
            Node* tail=skipList[lastL];
            while (tail->next!=nullptr)
            {
                tail=tail->next;
            }
            skipList.push_back(new Node{negSen,skipList[lastL],new Node{posSen,tail,nullptr}});
        }
    }
    bool search(const T& element) const
    {
        SkipListKey<T> tarKey (SkipListKind::Normal,element);
        Node* temp=skipList[skipList.size()-1];
        while (temp!=nullptr)
        {
            
            if (temp->sKey==tarKey)
            {
                return 1;
            }
            else if (temp->next!=nullptr && tarKey<temp->next->sKey)
            {
                temp=temp->below;
            }
            else
            {
                temp=temp->next;
            }
        }
        return 0;
    }
    void insert(const T& element, int level)
    {
        SkipListKey<T> tarK (SkipListKind::Normal,element);
        Node* temp=skipList[level];
        while (temp->next->sKey<tarK)
        {
            temp=temp->next;    
        }
        Node* n=temp->next;
        if (level==0)
            temp->next=new Node{tarK,nullptr,n};
        else
        {
            Node* nn=skipList[level-1];
            while (nn!=nullptr && !(nn->sKey==tarK))
            {
                nn=nn->next;        
            }
            temp->next=new Node{tarK,nn,n};
        }
    }
    
    void deleteAll()
    {
        for (int i=0;i<skipList.size();i++)
        {
            Node* temp=skipList[i];
            while (temp!=nullptr)
            {
                Node* next=temp->next;
                delete temp;
                temp=next;
            }
        }   
        skipList.clear();
    }
    Node* copyL(Node* source, std::vector<Node*>& skList, int level)
    {
        Node* blw=nullptr;
        /*if (level)
        {
            blw=skList[level-1];
            while (blw->next!=nullptr && !(blw->sKey==source->sKey))
            {blw=blw->next;}
        }*/
        while (level!=0 && (blw!=nullptr || (blw=skList[level-1])) && blw->next!=nullptr && !(blw->sKey==source->sKey))
        {
            blw=blw->next;
        }
        if (source->next==nullptr)
            return new Node{source->sKey,blw,nullptr};
        else
            return new Node{source->sKey,blw,copyL(source->next,skList,level)}; 
    }
    void copyAll(const SkipListSet& s)
    {
        for (int i=0;i<s.skipList.size();i++)
        {
            skipList.push_back(nullptr);
            skipList[i]=copyL(s.skipList[i],skipList,i);
        }
    }
    /*void traverse() const
    {
        std::cout<<"   TRAVERSE   "<<std::endl;
        for (int i=0;i<skipList.size();i++)
        {
            std::cout<<"LEVEL:"<<i<<"[ ";
            Node* n=skipList[i];
            while (n!=nullptr)
            {
                n->sKey.print();
                Node* t=n;
                std::cout<<"|BELOW:[";
                while (t->below!=nullptr)
                {
                    t=t->below;
                    t->sKey.print();
                }
                std::cout<<"] |";
                n=n->next;
            }
            std::cout<<" ] "<<std::endl;
        }
    }*/
    
};


template <typename T>
SkipListSet<T>::SkipListSet():sizeS(0)
{
    addEmptyLevel(skipList);
}


template <typename T>
SkipListSet<T>::~SkipListSet()
{
    deleteAll();
}


template <typename T>
SkipListSet<T>::SkipListSet(const SkipListSet& s):sizeS(s.sizeS)
{
    copyAll(s);
    //traverse();
    /*addEmptyLevel(skipList);
    insert(1,0);
    traverse();
    std::cout<<"STD:"<<(copyL(s.skipList[1],skipList,1)==nullptr)<<std::endl;
    while ()*/
    /*for (int i=0;i<s.skipList.size();i++)
    {
        skipList[i]=copyL(s.skipList[i],skipList,i);
    }*/
    /*addEmptyLevel(skipList);
    insert(T(),0);
    std::cout<<"COPYC"<<(copyL(s.skipList[1],skipList,1)==nullptr)<<std::endl;
    */
}


template <typename T>
SkipListSet<T>& SkipListSet<T>::operator=(const SkipListSet& s)
{
    if (this!=&s)
    {
        deleteAll();
        copyAll(s);
        sizeS=s.sizeS;
    }
    return *this;
}


template <typename T>
bool SkipListSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void SkipListSet<T>::add(const T& element)
{
    if (!search(element))
    {
        int level=0;
        insert(element,level);       
        ++sizeS;
        std::random_device device;
        std::default_random_engine engine (device());
        std::uniform_int_distribution<int> dis (0,1);
        while (dis(engine))
        {
            if (++level>=skipList.size())
                addEmptyLevel(skipList);
            insert(element,level);
        }
//        traverse();
    }
}


template <typename T>
bool SkipListSet<T>::contains(const T& element) const
{
//    std::cout<<"CON:"<<std::endl;
//    traverse();
    return search(element);
}


template <typename T>
unsigned int SkipListSet<T>::size() const
{
    return sizeS;
}



#endif // SKIPLISTSET_HPP

