// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.

#include "ArrayList.hpp"
int main()
{
    ArrayList<int> a;
    for(int i=0;i<1000000000;i++)
    {a.add(i);}

    return 0;
}

