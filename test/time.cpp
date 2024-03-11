#include <iostream>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int second;

public:

    Time(int h, int m, int s) {

        if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
            hour = h;
            minute = m;
            second = s;
        } else {
            cout << "Thoi gian khong hop le!\n";

            hour = minute = second = 0;
        }
    }


    void display12HourFormat() {
        string period = (hour < 12) ? "AM" : "PM";
        int displayHour = (hour > 12) ? hour - 12 : hour;

        cout << displayHour << ":" << minute << ":" << second << " " << period << endl;
    }


    void display24HourFormat() {
        cout << hour << ":" << minute << ":" << second << endl;
    }
};

int main() {
    int h, m, s;
    cout << "Nhap gio, phut, giay hien tai: ";
    cin >> h >> m >> s;

    Time currentTime(h, m, s);

    cout << "Thoi gian hien tai theo 12 gio: ";
    currentTime.display12HourFormat();

    cout << "Thoi gian hien tai theo 24 gio: ";
    currentTime.display24HourFormat();

    return 0;
}
