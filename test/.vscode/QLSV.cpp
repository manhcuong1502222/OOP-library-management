#include<iostream>

#include<string>

using namespace std;

class QLSV {

private:

string tenSV;
string MSSV;

double diemQT;
double diemThi;


public:

void setTenSV(string tenSV, string MSSV) {

this->tenSV = tenSV;
this->MSSV = MSSV;
}

string getMSSV(){
    return MSSV;
}

string getTenSV() {

return tenSV;

}


void setDiem(double diemQT, double diemThi) {

this->diemQT = diemQT;
this->diemThi = diemThi;

}


double getDiem() {

return diemQT;
return diemThi;

}


void Display() {

cout << "Ten SV: " << getTenSV(tenSV) << endl;
cout << "MSSV: " << getTenSV(MSSV) << endl;

cout << "Diem QT: " << getDiem(diemQT) << endl;
cout << "Diem Thi: " << getDiem(diemThi) << endl;


}

};



int main() {

int n;

string tenSV;

double diemQT;

double diemThi;

cout << "Nhap so luong SV: ";

cin >> n;

cin.ignore();

while (n < 0 || n>75) {

cout << "Nhap lai so luong SV: ";

cin >> n;

}

QLSV mangSV[75];

for (int i = 0; i < n; i++) {

cout << "Nhap ten SV thu " << i + 1 << " : ";

getline(cin, tenSV);

mangSV[i].setTenSV(tenSV);

cout << "Nhap diem QT cua SV: ";

cin >> diemQT;

while (diemQT < 0 || diemQT > 10) {

cout << "Nhap diem QT cua SV: ";

cin >> diemQT;

}

mangSV[i].setDiem(diemQT);

cin.ignore();

}


}