#ifndef OBJBOOK_H
#define OBJBOOK_H

#include "BaseObjBook.h"

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <random>

using namespace std;


class ObjBook : public ObjBaseBook {
public:
    ObjBook(int bookID, const QString& bookName, int bookStatus, const QString& bookLocation)
        : ObjBaseBook(0, bookID, bookName, 0, "", 0, "", bookStatus, bookLocation, QDateTime(), QDateTime(), 0, 0) {
    }
};

class ListBook {
private:
    std::vector<ObjBook> books;

public:


    ObjBook addBook(const QString& BookName,const QString& BookLocation) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(10000, 99999);

        int bookID;
        do {
            bookID = dist(gen);
        } while (isBookExist(bookID)==true);

        // Tạo độc giả mới với thông tin được cung cấp và thêm vào danh sách
        ObjBook reader(bookID,BookName,0,BookLocation);
        books.push_back(reader);
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
        return reader;
    }



    void removeBook(int bookID) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getBookID() == bookID) {
                books.erase(it);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
                break;
            }
        }
    }

    void fixBookname(const QString& bookname, QString& newbookname)
    {
        for(ObjBook& b: books)
        {
            if(b.getBookName() == bookname)
            {
                b.setBookName(newbookname);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
                break;
            }
        }
    }

    bool isBookExist(int bookID)
    {
        for (ObjBook& book:books ) {
            if (book.getBookID()==bookID) {
                return true;
            }
        }
    }

    bool isBookBorrowred(int bookID)
    {
        for (ObjBook& book:books ) {
            if (book.getBookID()==bookID) {
                if(book.getBookStatus()==1)
                {
                    return true;
                }
            }
        }
    }

    const std::vector<ObjBook>& getBooks() const {
        return books;
    }

    void updateBookLocation(int bookID, const QString& newBookLocation) {
        for (ObjBook& book : books) {
            if (book.getBookID() == bookID) {
                // Chỉ cập nhật vị trí sách cho đối tượng `book`
                book.setBookLocation(newBookLocation);

                // Lưu danh sách vào tệp văn bản sau khi đã sửa
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");

                // Đã tìm thấy và sửa xong, thoát khỏi vòng lặp
                break;
            }
        }
    }


    void BorrowandUpdateStatusBook(int bookID){
        for (ObjBook& book : books) {
            if (book.getBookID() == bookID) {
                book.setBookStatus(1);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
                break;
            }
        }
    }

    void ReturnandUpdateStatusBook(int bookID){
        for (ObjBook& book : books) {
            if (book.getBookID() == bookID) {
                book.setBookStatus(0);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/book.txt");
                break;
            }
        }
    }

    const ObjBook getBookbyBookCode(int bookID)
    {
        for (ObjBook& book : books) {
            if (book.getBookID() == bookID) {
                return book;
            }
        }
    }

    bool findBook(int bookID)
    {
        for (const ObjBook& book : books) {
            if (book.getBookID() == bookID) {
                return true; // Mã sách tồn tại trong danh sách
            }
        }
        return false; // Không tìm thấy sách với mã tương ứng
    }

    loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        books.clear();
        QTextStream in(&file);

        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 4) {
                int bookID = tokens[0].toInt();
                QString bookname = tokens[1];
                int bookstatus = tokens[2].toInt();
                QString booklocation = tokens[3];

                ObjBook book(bookID, bookname, bookstatus, booklocation);
                books.push_back(book);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
        return true;
    }

    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);

        // Viết tiêu đề (hàng đầu tiên)
        out<< "Ma Sach,Ten sach,Trang Thai,Vi tri\n";
        for (const ObjBook& book : books) {
            out << book.getBookID() << ","
                << book.getBookName() << ","
                << book.getBookStatus() << ","
                << book.getBookLocation() << "\n";
        }

        file.close();
    }
};

#endif // OBJBOOK_H
