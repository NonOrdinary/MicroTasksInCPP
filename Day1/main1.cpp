#include<iostream>

using namespace std;

int add(int a, int b){
    return a + b;
}

int max2(int a, int b){
    if(a > b) return a;
    return b;
}

void printLine(const string& s){
    cout << s << endl;
    return;
}
int lengthOf(const string& s){
    int len = 0;
    for(auto &i : s){
        len++;
    }
    return len;
}
bool isEven(int x){
    return ~(x & 1);
}
string toUpperCopy(const string& s){
    string cp = s;
    for(auto &i : cp){
        toupper(i);
    }
    return cp;
}
void increment(int &x){
    ++x;
    return;
}
void appendExclaim(string &s){
    s += '!';
    return;
}


int main(){
    
}