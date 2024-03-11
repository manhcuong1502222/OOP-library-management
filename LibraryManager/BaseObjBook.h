#ifndef BASEOBJBOOK_H
#define BASEOBJBOOK_H

#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDateTime>

class ObjBaseBook {
private:
    int ISBN;
    int bookID;
    QString bookName;
    int publishingYear;
    QString Author;
    int numberPage;
    QString bookType;
    int bookStatus;
    QString bookLocation;
    QDateTime bookBorrowDate;
    QDateTime bookReturnDate;
    int numberBorrowedTime;
    int readerID;

public:
    ObjBaseBook(int ISBN, int bookID, const QString& bookName, int publishingYear, const QString& Author, int numberPage, const QString& bookType, int bookStatus, const QString& bookLocation, const QDateTime& bookBorrowDate, const QDateTime& bookReturnDate, int numberBorrowedTime, int readerID)
        : ISBN(ISBN), bookID(bookID), bookName(bookName), publishingYear(publishingYear), Author(Author), numberPage(numberPage), bookType(bookType), bookStatus(bookStatus), bookLocation(bookLocation), bookBorrowDate(bookBorrowDate), bookReturnDate(bookReturnDate), numberBorrowedTime(numberBorrowedTime), readerID(readerID) {
    }

    int getBookID() const {
        return bookID;
    }

    void setBookID(int newBookID) {
        bookID = newBookID;
    }

    int getISBN() const {
        return ISBN;
    }

    void setISBN(int newISBN) {
        ISBN = newISBN;
    }

    QString getBookName() const {
        return bookName;
    }

    void setBookName(const QString& newBookName) {
        bookName = newBookName;
    }

    int getPublishingYear() const {
        return publishingYear;
    }

    void setPublishingYear(int year) {
        publishingYear = year;
    }

    QString getAuthor() const {
        return Author;
    }

    void setAuthor(const QString& newAuthor) {
        Author = newAuthor;
    }

    int getNumberPage() const {
        return numberPage;
    }

    void setNumberPage(int numPages) {
        numberPage = numPages;
    }

    QString getBookType() const {
        return bookType;
    }

    void setBookType(const QString& newBookType) {
        bookType = newBookType;
    }

    int getBookStatus() const {
        return bookStatus;
    }

    void setBookStatus(int status) {
        bookStatus = status;
    }

    QString getBookLocation() const {
        return bookLocation;
    }

    void setBookLocation(const QString& location) {
        bookLocation = location;
    }

    QDateTime getBookBorrowDate() const {
        return bookBorrowDate;
    }

    void setBookBorrowDate(const QDateTime& borrowDate) {
        bookBorrowDate = borrowDate;
    }

    QDateTime getBookReturnDate() const {
        return bookReturnDate;
    }

    void setBookReturnDate(const QDateTime& returnDate) {
        bookReturnDate = returnDate;
    }

    int getNumberBorrowedTime() const {
        return numberBorrowedTime;
    }

    void setNumberBorrowedTime(int numBorrowTimes) {
        numberBorrowedTime = numBorrowTimes;
    }

    int getReaderID() const {
        return readerID;
    }

    void setReaderID(int newReaderID) {
        readerID = newReaderID;
    }

    bool isBaRBookLimited() const {
        QDateTime currentTime = QDateTime::currentDateTime();
        int daysLimit = 15; // Số ngày giới hạn cho việc mượn sách
        return bookBorrowDate.daysTo(currentTime) > daysLimit;
    }
};

#endif // BASEOBJBOOK_H
