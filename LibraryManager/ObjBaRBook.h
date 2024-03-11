#ifndef OBJBARBOOK_H
#define OBJBARBOOK_H

#include"BaseObjBook.h"

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDateTime>


using namespace std;

class ObjBaRBook : public ObjBaseBook{
private:

public:
    ObjBaRBook(int bookID, const QString& bookName, const QDateTime& bookBorrowDate, const QDateTime& bookReturnDate, int numberBorrowTime, int readerID)
        : ObjBaseBook(0, bookID, bookName, 0, "", 0, "", 0, "", bookBorrowDate, bookReturnDate, numberBorrowTime, readerID) {
    }
};

class ListBaRBook{
private:
    vector<ObjBaRBook> barbooks;
public:
    // Phương thức thêm BaRBook
    void addBaRBook(const ObjBaRBook& barbook) {
        barbooks.push_back(barbook);
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt");
    }

    // Phương thức xóa BaRBook dựa trên BookCode
    void removeBaRBook(int bookID) {
        for (auto it = barbooks.begin(); it != barbooks.end(); ++it) {
            if (it->getBookID() == bookID) {
                barbooks.erase(it);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt");
                break;
            }
        }
    }

    bool isHasBaRBookLimited() {
        QDateTime currentTime = QDateTime::currentDateTime();
        int daysLimit = 15; // Số ngày giới hạn cho việc mượn sách

        for (auto it = barbooks.begin(); it != barbooks.end(); ++it) {
            if (it->getBookBorrowDate().daysTo(currentTime) > daysLimit) {
                return true;
            }
        }

        return false;
    }

    void borrowBook(int bookCode, const QString& bookName, int readerID) {
        QDateTime currentDateTime = QDateTime::currentDateTime(); // Lấy thời gian hiện tại

        // Tìm kiếm xem đã có ObjBaRBook với mã sách (bookCode) trong danh sách chưa
        bool found = false;
        for (ObjBaRBook& barbook : barbooks) {
            if (barbook.getBookID() == bookCode) {
                // Có đối tượng ObjBaRBook với mã sách đã tồn tại
                found = true;

                // Thay đổi thông tin đối tượng
                barbook.setReaderID(readerID);
                barbook.setBookBorrowDate(currentDateTime);
                barbook.setBookReturnDate(QDateTime()); // Đặt ngày trả là trống
                barbook.setNumberBorrowedTime(barbook.getNumberBorrowedTime() + 1);

                break;
            }
        }

        if (!found) {
            // Nếu không tìm thấy đối tượng ObjBaRBook với mã sách, tạo một mới
            ObjBaRBook newBarBook(bookCode, bookName, currentDateTime, QDateTime(), 1, readerID);
            barbooks.push_back(newBarBook);
        }

        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt");
    }

    void returnBook(int bookID, int readerID)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime(); // Lấy thời gian hiện tại
        for (ObjBaRBook& barbook : barbooks) {
            if (barbook.getBookID() == bookID) {
                barbook.setBookReturnDate(currentDateTime);
                barbook.setReaderID(0);
            }
        }
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt");

    }

    const vector<ObjBaRBook> getBaRBooks()
    {
        return barbooks;
    }

    // Phương thức để lưu danh sách BaRBook vào tệp văn bản
    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);
        out << "Ma sach,Ten Sach,Ngay muon,Ngay tra,Luot muon sach,Ma doc gia muon sach\n";
        for (const ObjBaRBook& barbook : barbooks) {
            out << barbook.getBookID() << ","
                << barbook.getBookName() << ","
                << barbook.getBookBorrowDate().toString("yyyy-MM-dd") << ","
                << barbook.getBookReturnDate().toString("yyyy-MM-dd") << ","
                << barbook.getNumberBorrowedTime() << ","
                << barbook.getReaderID() << "\n";
        }

        file.close();
    }


    // Phương thức để đọc dữ liệu BaRBook từ tệp văn bản
    bool loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        barbooks.clear();

        QTextStream in(&file);
        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 6) {
                int bookID = tokens[0].toInt();
                QString bookName = tokens[1];
                QDateTime bookBorrowDate = QDateTime::fromString(tokens[2], "yyyy-MM-dd");
                QDateTime bookReturnDate = QDateTime::fromString(tokens[3], "yyyy-MM-dd");
                int numberBorrowedTime = tokens[4].toInt();
                int readerID = tokens[5].toInt();

                ObjBaRBook barbook(bookID, bookName, bookBorrowDate, bookReturnDate, numberBorrowedTime, readerID);
                barbooks.push_back(barbook);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
        return true;
    }
};


#endif // OBJBARBOOK_H
