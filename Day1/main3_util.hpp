#include<iostream>
int add(int a, int b){
    return a + b;
}

int max2(int a, int b){
    if(a > b) return a;
    return b;
}

void printLine(const std ::string& s){
   std :: cout << s << std::endl;
    return;
}
int lengthOf(const std :: string& s){
    int len = 0;
    for(auto &i : s){
        len++;
    }
    return len;
}
bool isEven(int x){
    return ~(x & 1);
}
std :: string toUpperCopy(const std:: string& s){
   std:: string cp = s;
    for(auto &i : cp){
        toupper(i);
    }
    return cp;
}
void increment(int &x){
    ++x;
    return;
}
void appendExclaim(std :: string &s){
    s += '!';
    return;
}