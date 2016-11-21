// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "app" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.

#include <iostream>
#include <memory>
class X
{
public:
    X(){std::cout<<"X::X"<<std::endl;}
    ~X(){std::cout<<"X::~X"<<std::endl;}
};

int main()
{
    //even in python, garbage collect careful (i.e. file.close() )
    //even if bailout by exception, statically allocated gurantte deletion 
    //RAII: when resources that need to be managed are needed, best to acquire them in a constructor; for resources that need to be cleaned up, best to release them in a destructor 
    std::unique_ptr<X> x1(new X);
//    std::unique_ptr<X> x2=x1;
    std::shared_ptr<X> x2(new X);
    std::shared_ptr<X> x3=x2;
    std::cout<<"use_count "<<x3.use_count()<<std::endl;
    return 0;
}

