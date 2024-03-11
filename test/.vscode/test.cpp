#include <iostream>
using namespace std;

class Mayvitinh
{
public:
    Mayvitinh()
    {
        cout << "This is a computer's brand" << endl;
    }
};
class Maylaptop
{
public:
    Maylaptop()
    {
        cout << "This is a laptop's brand" << endl;
    }
};
class mayAcer : public Mayvitinh
{
};
class mayAsus : public Mayvitinh, public Maylaptop
{
};
int main()
{
    mayAsus may1; 
    mayAcer may2;
    return 0;
}