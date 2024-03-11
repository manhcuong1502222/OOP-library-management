#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Calculator {
private:
    T a, b;

public:
    Calculator(T x, T y) : a(x), b(y) {}

    T add() const {
        return a + b;
    }

    T subtract() const {
        return a - b;
    }

    T multiply() const {
        return a * b;
    }

    T divide() const {
        if (b != 0) {
            return a / b;
        } else {
            cerr << "Error: Division by zero." << endl;
            return static_cast<T>(0);
        }
    }

    T square() const {
        return a * a;
    }

    T squareRoot() const {
        if (a >= 0) {
            return sqrt(a);
        } else {
            cerr << "Error: Cannot calculate square root of a negative number." << endl;
            return static_cast<T>(0);
        }
    }
};


int main() {
    
    Calculator<double> doubleCalc(9.0, 3.0);

    cout << "Addition: " << doubleCalc.add() << endl;
    cout << "Subtract: " << doubleCalc.subtract() << endl;
    cout << "Multiply: " << doubleCalc.multiply() << endl;
    cout << "Devide: " << doubleCalc.divide() << endl;
    cout << "Square: " << doubleCalc.square() << endl;
    cout << "SquareRoot: " << doubleCalc.squareRoot() << endl;
    

    return 0;
}
