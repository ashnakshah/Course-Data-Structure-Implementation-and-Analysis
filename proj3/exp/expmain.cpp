// expmain.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <iostream>
#include "BSTSet.hpp"
#include "AVLSet.hpp"
#include "HashSet.hpp"
#include "StringHashing.hpp"
//#include <functional>
#include <string>
#include "SkipListSet.hpp"

/*struct Node
{
    int key;
    Node* prev;
    Node* next;
};
*/
int main()
{
    /*Node** nn=new Node* [3];
    for (int i=0;i<3;i++)
    {
        nn[i]=new Node{i,nullptr};
    }
    nn[0]->next=new Node{4,nullptr};
    for (int i=0;i<3;i++)
    {
        Node* t=nn[i];
        while(t!=nullptr)
        {
        std::cout<<"key "<<t->key<<std::endl;
        t=t->next;
        }
    }
    delete nn[0]->next;
    for (int i=0;i<3;i++)
    {
        delete nn[i];
    }*/
    //std::string s ("EEE");
    //HashSet<std::string> h (hashStringAsZero);
    //h.add(s);
    //std::cout<<h.contains(s)<<std::endl;
    AVLSet<int> avl;
  //avl.add(19);
  //AVLSet<int> avl1=avl;
  // BSTSet<int> bst;
  // bst.add(19);
  //  BSTSet<int> bst1=bst;
    int t[]={42,30,24,45,29,33,39,40};
    for(int i=7;i>=0;i--)
    {
        avl.add(t[i]);
    }
/*    
    SkipListSet<int> sk;
    sk.add(1);
    sk.add(2);
    sk.add(3);
    sk.add(23);
    sk.add(33);
    SkipListSet<int> sk1=sk;
*/
//    std::cout<<"SK:"<<sk.contains(3)<<std::endl;
    std::cout<<std::endl;
    //std::cout<<"SK1:"<<sk1.contains(3)<<std::endl;
    //HashSet<std::string> h (hashStringAsProduct);
    //std::string s ("string");
    /*int n=s.size();
    for (int i=1;i<n && n>1;i++)
    {
        std::string clone (s);
        char temp=clone[i-1];
        clone[i-1]=clone[i];
        clone[i]=temp;
        std::cout<<i<<" "<<clone<<std::endl;
    }
    std::cout<<"string "<<s<<std::endl;
    std::string s1 (s);
    */
    //s1.insert(0,'a');
    //std::cout<<s1<<std::endl;
    /*for (int i=0;i<=s1.size();i++)
    {
        std::string s2 (s1);
        s2.insert(i,1,(char)97+i);
        std::cout<<s2<<std::endl;
    }*/
    //h.add(s);
    //h.add("ssss");
    //h.add("dwad");
    //HashSet<std::string> h1 (h);
    //h.add("str");
    //h.add("asdd");
    //BSTSet<int> b (bst);
    //bst.add(1);
    //b.add(10);
    //bst.add(2);
    //bst.add(3);
    //bst.add(0);
    //std::cout<<h.contains("ssss")<<std::endl;
    //std::cout<<bst1.contains(19)<<std::endl;
    return 0;
}

