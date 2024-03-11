#ifndef OBJHEADBOOK_H
#define OBJHEADBOOK_H

#include "BaseObjBook.h"

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "ObjBook.h"
#include "ObjBaRBook.h"

using namespace std;


class ObjHeadBook : public ObjBaseBook {
private:
    vector<ObjBook> Books;
    vector<ObjBaRBook> BarBooks;

public:
    ObjHeadBook(int ISBN, QString BookName, int NumberPage, QString Author, int PublishingYear, QString TypeBook, int NumberBorrowedTime)
        : ObjBaseBook(ISBN, 0, BookName, PublishingYear, Author, NumberPage, TypeBook, 0, "", QDateTime(), QDateTime(), NumberBorrowedTime, 0) {
    }

    void addBookHB(const ObjBook& book){
        Books.push_back(book);
    }
    const vector<ObjBook>& getBooks() const {
        return Books;
    }

    void addBaRBookHB(const ObjBaRBook& barbook){
        BarBooks.push_back(barbook);
    }
    const vector<ObjBaRBook>& getBarBookofHB() const{
        return BarBooks;
    }
};


class ListHeadBook{
private:
    std::vector<ObjHeadBook> HeadBooks;

public:

    const vector<ObjBook> getBooksfromHeadBook(int ISBN)
    {
        vector<ObjBook> result;

        for (const ObjHeadBook& headBook : HeadBooks) {
            if (headBook.getISBN() == ISBN) {
                result = headBook.getBooks();
                break;
            }
        }

        return result;
    }

    const vector<ObjHeadBook> getHeadBooks()
    {
        return HeadBooks;
    }

    ObjHeadBook getHeadBookbyISBN(int ISBN){

        for (ObjHeadBook& headbook : HeadBooks) {
            {
                if(headbook.getISBN()==ISBN)
                    return headbook;
            }
        }
    }

    void addHeadBook(const ObjHeadBook& headbook) {

        // Thêm sách mới vào danh sách
        HeadBooks.push_back(headbook);

        // Lưu danh sách vào tệp văn bản
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");
    }

    void loadBooksToHeadBooks(ListBook& listBook) {
        for (ObjHeadBook& headbook : HeadBooks) {
            for (const ObjBook& book : listBook.getBooks()) {
                if (book.getBookName() == headbook.getBookName()) {
                    headbook.addBookHB(book);
                }
            }
        }
    }

    void loadNumberBorrowredtoHeadBook(ListBaRBook& lbb){

         for (ObjHeadBook& hb : HeadBooks) {
            int s = 0;
            for(const ObjBaRBook& bb: lbb.getBaRBooks() )
            {
                if(hb.getBookName()==bb.getBookName())
                {
                    s += bb.getNumberBorrowedTime();
                }
            }
            hb.setNumberBorrowedTime(s);
        }
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");

    }

    void deleteHeadBook(int ISBN)
    {
        for (auto it = HeadBooks.begin(); it != HeadBooks.end(); ++it) {
            if (it->getISBN() == ISBN) {
                HeadBooks.erase(it);
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");
                break;
            }
        }
    }

    bool FindHeadBookbyISBN(int ISBN)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getISBN() == ISBN) {
                return true; // Mã ISBN tồn tại trong danh sách
            }
        }
        return false; // Không tìm thấy đầu sách với mã ISBN
    }

    bool isHeadbookhasbook(int ISBN)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getISBN() == ISBN) {
                {
                    if(headbook.getBooks().size()>0)
                        return true;
                }
            }
        }
        return false;
    }

    void uppdateHeadBook(int ISBN, const QString& newBookName, int newNumberPage, const QString& newAuthor, int newPublishingYear, const QString& newTypeBook)
    {
        for (ObjHeadBook& headbook : HeadBooks) {
            if (headbook.getISBN() == ISBN) {
                // Sửa lại thông tin cho đối tượng `headbook`
                headbook = ObjHeadBook(ISBN, newBookName, newNumberPage, newAuthor, newPublishingYear, newTypeBook, headbook.getNumberBorrowedTime());

                // Lưu danh sách vào tệp văn bản sau khi đã sửa
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");

                // Đã tìm thấy và sửa xong, thoát khỏi vòng lặp
                break;
            }
        }
    }

    void SwapHeadbook(ObjHeadBook& a, ObjHeadBook& b) {
        ObjHeadBook temp = a;
        a = b;
        b = temp;
    }

    vector<ObjHeadBook> printtop10HeadBook() {
        vector<ObjHeadBook> top10Books;

        for (int i = 0; i < HeadBooks.size(); i++) {
            for (int j = i + 1; j < HeadBooks.size(); j++) {
                if (HeadBooks[i].getNumberBorrowedTime() < HeadBooks[j].getNumberBorrowedTime()) {
                    SwapHeadbook(HeadBooks[i], HeadBooks[j]);
                }
            }
        }

        for (int i = 0; i < std::min(10, static_cast<int>(HeadBooks.size())); i++) {
            top10Books.push_back(HeadBooks[i]);
        }

        return top10Books;
    }

    void loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        HeadBooks.clear();

        QTextStream in(&file);

        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 7) {
                int ISBN = tokens[0].toInt();
                QString BookName = tokens[1];
                int NumberPage = tokens[2].toInt();
                QString Author = tokens[3];
                int PublishingYear = tokens[4].toInt();
                QString TypeBook = tokens[5];
                int NumberBorrowed = tokens[6].toInt();

                ObjHeadBook headbook(ISBN, BookName, NumberPage, Author, PublishingYear, TypeBook, NumberBorrowed);
                HeadBooks.push_back(headbook);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
    }

    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);

        // Viết tiêu đề (hàng đầu tiên)
        out << "ISBN,Ten sach,So trang,Tac Gia,Nam xuat ban,The loai,So luot muon\n";

        for (const ObjHeadBook& headbook : HeadBooks) {
            out << headbook.getISBN() << ","
                << headbook.getBookName() << ","
                << headbook.getNumberPage() << ","
                << headbook.getAuthor() << ","
                << headbook.getPublishingYear() << ","
                << headbook.getBookType() << ","
                << headbook.getNumberBorrowedTime() <<"\n";
        }

        file.close();
    }
};

#endif // OBJHEADBOOK_H
