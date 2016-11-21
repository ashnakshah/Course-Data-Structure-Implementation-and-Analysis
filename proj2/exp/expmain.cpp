// expmain.cpp
//
// ICS 46 Spring 2016
// Project #2: Black and White
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include <memory>
#include <iostream>
int main()
{
    std::unique_ptr<int> p;
    for(int i=0;i<10;i++)
    {
        p=std::unique_ptr<int>(new int(i));
        std::cout<<"i="<<*p<<std::endl;
    }
    bool i=(1==1);
    std::cout<<i*10<<std::endl;
    return 0;
}

