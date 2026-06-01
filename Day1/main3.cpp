// Task 3: write a small reusable helper file

// Make two files:

// utils.h
// utils.cpp

// Move your helper functions there.

#include<iostream>
#include"main3_util.hpp"

int main(){
    std :: cout << add(3,5) << std:: endl;
    std :: cout << max2(3,5) << std:: endl;
    std :: string s = "Sunny";
    printLine(s);
    std :: cout << lengthOf(s) << std:: endl;
    std :: cout << isEven(5) << std:: endl;
    std :: cout << toUpperCopy(s) << std:: endl;
    int a = 5;
    increment(a);
    appendExclaim(s);

}