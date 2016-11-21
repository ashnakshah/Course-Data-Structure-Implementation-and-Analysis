#include <gtest/gtest.h>
#include "ArrayList.hpp"
#include <string>

TEST(ArrayListTest,testWhetherItemAddedAfterAdd){
    ArrayList<std::string> a;
    std::string s ("hello");
    a.add(s);
    ASSERT_EQ(s,a.at(0));
}

TEST(ArrayListTest, testWhetherArrayListChangedAfterAssignedToDifferentArrayList){
    ArrayList<int> a;
    ArrayList<int> b;
    for(int i=10;i>0;i--){b.add(i);}
    b=a;
    for(int i=0;i<a.size();i++){ASSERT_EQ(a.at(i),b.at(i));}
}
TEST(ArrayListTest, testSizeChangeAfterAdd){
    ArrayList<int> a;
    a.add(10);
    ASSERT_EQ(1,a.size());
}
TEST(ArrayListTest, testTheItemReturnedByAt){
    ArrayList<int> a;
    a.add(10);
    a.add(9);
    a.add(8);
    ASSERT_EQ(10,a.at(0));
    ASSERT_EQ(9,a.at(1));
    ASSERT_EQ(8,a.at(2));
}
