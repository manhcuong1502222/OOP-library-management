//Viết chương trình tính diện tích và chu vi các hình: Hình chữ nhật biết hai cạnh, hình tam giác biết ba cạnh, 
//hình tròn biết bán kính, hình vuông biết một cạnh. Chương trình cho phép Nhập kích thước các hình; 
//Hiển thị diện tích và chu vi các hình đã nhập. 
//Khi người sử dụng nhập kích thước thì hỏi người sử dụng nhập kích thước cho hình nào, 
//in ra kết quả diện tích và chu vi. Hỏi người sử dụng có tiếp tục tính không y/n? CT dừng khi người dùng nhập n

#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual void getInput() = 0;
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

class Rectangle : public Shape {
private:
    double length, width;

public:
    void getInput() override {
        cout << "Nhap chieu dai: ";
        cin >> length;
        cout << "Nhap chieu rong: ";
        cin >> width;
    }

    double area() override {
        return length * width;
    }

    double perimeter() override {
        return 2 * (length + width);
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    void getInput() override {
        cout << "Nhap canh 1: ";
        cin >> side1;
        cout << "Nhap canh 2: ";
        cin >> side2;
        cout << "Nhap canh 3: ";
        cin >> side3;
    }

    double area() override {
        double s = (side1 + side2 + side3) / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    double perimeter() override {
        return side1 + side2 + side3;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    void getInput() override {
        cout << "Nhap ban kinh: ";
        cin >> radius;
    }

    double area() override {
        return M_PI * radius * radius;
    }

    double perimeter() override {
        return 2 * M_PI * radius;
    }
};

class Square : public Shape {
private:
    double side;

public:
    void getInput() override {
        cout << "Nhap canh: ";
        cin >> side;
    }

    double area() override {
        return side * side;
    }

    double perimeter() override {
        return 4 * side;
    }
};

int main() {
    char choice;
    Shape* shape;

    do {
        cout << "Chon hinh muon tinh (R: Hinh chu nhat, T: Hinh tam giac, C: Hinh tron, S: Hinh vuong): ";
        cin >> choice;

        switch (choice) {
            case 'R':
                shape = new Rectangle();
                break;
            case 'T':
                shape = new Triangle();
                break;
            case 'C':
                shape = new Circle();
                break;
            case 'S':
                shape = new Square();
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
                continue;
        }

        shape->getInput();
        cout << "Dien tich: " << shape->area() << endl;
        cout << "Chu vi: " << shape->perimeter() << endl;

        delete shape;

        cout << "Ban co muon tiep tuc (y/n)? ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}






