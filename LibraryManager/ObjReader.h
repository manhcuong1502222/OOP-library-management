#ifndef OBJREADER_H
#define OBJREADER_H
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "ObjBaRBook.h"
#include <random>

using namespace std;
class ObjReader{
private:
    int ReaderID;
    QString ReaderName;
    QString ReaderSex;
    int ReaderStatus;
    vector<ObjBaRBook> BaRBooks;

public:
    ObjReader(int readerID, const QString& readerName, const QString& readerSex, int readerStatus)
        : ReaderID(readerID), ReaderName(readerName), ReaderSex(readerSex), ReaderStatus(readerStatus) {
    }

    int getReaderID() const {
        return ReaderID;
    }

    QString getReaderName() const {
        return ReaderName;
    }

    QString getReaderSex() const {
        return ReaderSex;
    }

    int getReaderStatus() const {
        return ReaderStatus;
    }
    void setReaderStatus(int stt)
    {
        ReaderStatus = stt;
    }
    void addBaRBooks(const ObjBaRBook& bar){
        BaRBooks.push_back(bar);
    }
    const vector<ObjBaRBook>& getBaRBooks() const {
            return BaRBooks;
    }


};
class ListReader{
private:
    vector<ObjReader> readers;
public:
    ObjReader getReaderbyID(int readerID) {
            for (const ObjReader& reader : readers) {
                if (reader.getReaderID() == readerID) {
                    return reader;
                }
            }
    }

    void LoadBaRBookstoReader(ListBaRBook& barbooks) {
            for (ObjReader& reader : readers) {
                for (const ObjBaRBook& bb : barbooks.getBaRBooks()) {
                    if (bb.getReaderID() == reader.getReaderID()) {
                        reader.addBaRBooks(bb);
                    }
                }
            }
    }

    bool isReaderIDExists(int readerID) {
        // Kiểm tra xem mã độc giả đã tồn tại trong danh sách chưa
        for (const ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                return true;
            }
        }
        return false;
    }
    bool isReaderActive(int readerID){
        for (const ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                if(reader.getReaderStatus()==1)
                {
                        return true;
                }
            }
        }
        return false;
    }
    bool isBaRBookFull(int readerID)
    {
        for (const ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                if (reader.getBaRBooks().size() == 3) {
                        return true;
                }
            }
        }
        return false;
    }

    bool isReaderHasBaRLimited(int readerID) {
        for (const ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                for (const ObjBaRBook& bb : reader.getBaRBooks()) {
                        if (bb.isBaRBookLimited()) {
                            return true;
                        }
                }
            }
        }
        return false;
    }

    bool isReaderBorrowingBook(int readerID, int bookID)
    {
        for (const ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                for (const ObjBaRBook& bb : reader.getBaRBooks()) {
                        if (bb.getBookID()==bookID) {
                            return true;
                        }
                }
            }
        }
    }

    bool isReadrhasBaRBook(int readerID){
        for (const ObjReader& reader : readers) {
            if(reader.getReaderID() == readerID)
            {
                vector<ObjBaRBook> list = reader.getBaRBooks();
                if(list.size()>0)
                {
                        return true;
                }
            }
        }
        return false;
    }

    ObjReader addReader(const QString& readerName, const QString& readerSex) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(100000, 999999);

        int readerID;
        do {
            readerID = dist(gen);
        } while (isReaderIDExists(readerID)==true);

        // Tạo độc giả mới với thông tin được cung cấp và thêm vào danh sách
        ObjReader reader(readerID, readerName, readerSex, 1);
        readers.push_back(reader);
        // Lưu danh sách độc giả vào tệp văn bản sau khi thêm độc giả mới
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt");
        return reader;
    }

    const vector<ObjReader> getReaders()
    {
        return readers;
    }

    bool hasBaRBooks(const ObjReader& reader) {
        const vector<ObjBaRBook>& barBooks = reader.getBaRBooks();
        return !barBooks.empty();
    }

    void BlockReader(int readerID)
    {
        for(ObjReader& rd: readers)
        {
            if(rd.getReaderID() == readerID)
            {
                rd.setReaderStatus(0);
            }
        }
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt");
    }

    void unBlockReader(int readerID)
    {
        for(ObjReader& rd: readers)
        {
            if(rd.getReaderID() == readerID)
            {
                rd.setReaderStatus(1);
            }
        }
        saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt");
    }

    // Phương thức xóa độc giả dựa trên ReaderID
    void removeReader(int readerID) {
        for (auto it = readers.begin(); it != readers.end(); ++it) {
            if (it->getReaderID() == readerID) {
                if (!hasBaRBooks(*it)) {
                    // Xóa độc giả khi không có BaRBooks
                    readers.erase(it);
                    saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt");
                } else {
                    // Xử lý trường hợp có BaRBooks (ví dụ: thông báo lỗi)
                    std::cerr << "Không thể xóa độc giả có BaRBooks." << std::endl;
                }
                break;
            }
        }
    }

    void updateReader(int readerID, const QString& newReaderName, const QString& newReaderSex) {
        for (ObjReader& reader : readers) {
            if (reader.getReaderID() == readerID) {
                // Cập nhật thông tin độc giả
                reader = ObjReader(readerID, newReaderName,newReaderSex,1);

                // Lưu danh sách độc giả vào tệp văn bản sau khi cập nhật
                saveToTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt");
                return; // Kết thúc hàm sau khi cập nhật
            }
        }
    }

    // Phương thức để lưu danh sách độc giả vào tệp văn bản
    void saveToTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return;
        }

        QTextStream out(&file);

        // Viết tiêu đề (hàng đầu tiên)
        out << "Ma doc gia,Ho ten,Gioi tinh,Trang thai the\n";
        for (const ObjReader& reader : readers) {
            out << reader.getReaderID() << ","
                << reader.getReaderName() << ","
                << reader.getReaderSex() << ","
                << reader.getReaderStatus() << "\n";
        }

        file.close();
    }
    bool loadFromTextFile(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Không thể mở tệp văn bản" << std::endl;
                return false;
        }

        readers.clear();

        QTextStream in(&file);

        // Đọc dòng tiêu đề (hàng đầu tiên) để bỏ qua
        QString header = in.readLine();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(",");

            if (tokens.size() == 4) {
                int readerID = tokens[0].toInt();
                QString readerName = tokens[1];
                QString readerSex = tokens[2];
                int readerStatus = tokens[3].toInt();

                ObjReader reader(readerID, readerName, readerSex, readerStatus);
                readers.push_back(reader);
            } else {
                std::cerr << "Dòng không hợp lệ: " << line.toStdString() << std::endl;
            }
        }

        file.close();
        return true;
    }
};


#endif // OBJREADER_H
