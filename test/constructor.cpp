#include <iostream>
using namespace std;

class Square {
    private:
    int number;

public:
    Square() {
        number = 10;
        cout<<"10^2 = " << number*number<<endl;
    }
    void displayResult(int a) {
        number = a;
        cout << "The square of " << number << " is: " << number*number << endl;
    }
};

int main() {
    Square square;
    int x;
    cout<<"Enter the number you want to square: " <<endl;
    cin>>x;
    
    square.displayResult(x);
    return 0;
}




