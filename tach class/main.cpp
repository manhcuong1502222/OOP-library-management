#include<iostream>
#include<string>
#include "header.cpp"

using namespace std;

int main() {
    Square square;
    int x;
    cout<<"Enter the number you want to square: " <<endl;
    cin>>x;
    
    square.displayResult(x);
    return 0;
}