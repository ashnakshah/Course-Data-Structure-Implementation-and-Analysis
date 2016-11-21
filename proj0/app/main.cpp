#include <iostream>
#include <string>
#include "ArrayList.hpp"
//#include "ArrayList.cpp"


int main()
{
    ArrayList<std::string> a;
    ArrayList<std::string> b;
    std::string s;
    for(int i=0;i<10;++i){
        std::getline(std::cin,s);
        a.add(s);
    }
    //std::cout<<"size "<<a.size()<<std::endl;
    for(int i=0;i<a.size()-1;i++){
        std::string sa=a.at(i);
        char *c=new char [sa.length()+1];
        std::strcpy(c,sa.c_str());
        char *id=std::strtok(c," ");
        std::cout<<std::strtok(NULL,"")<<" (ID#"<<id<<")"<<std::endl;
        delete [] c;
    }
    b=a;
    //for(int i=0;i<b.size();i++){std::cout<<b.at(i)<<std::endl;}
//    a.at(100000);
    return 0;
}

