#ifndef DISPLAYLIST_H
#define DISPLAYLIST_H

#include <QTableView>
#include <QStandardItemModel>
#include <vector>
#include <QString>
#include "ObjBook.h"
#include "ObjHeadbook.h"
#include "ObjBaRBook.h"
#include "ObjReader.h"
static void displaytableListBooks(QTableView* tableView, const std::vector<ObjBook>& data){
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(4);  // Số cột, thay đổi tùy theo cần hiển thị

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("Mã "));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên "));
    model->setHorizontalHeaderItem(2, new QStandardItem("Trạng thái"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Vị trí"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjBook& book = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(book.getBookID())));
        model->setItem(row, 1, new QStandardItem(book.getBookName()));
        if(book.getBookStatus()==0){
            model->setItem(row, 2, new QStandardItem("Chưa cho mượn"));
        }
        else{
           model->setItem(row, 2, new QStandardItem("Đã cho mượn"));
        }
        model->setItem(row, 3, new QStandardItem(book.getBookLocation()));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
    for (int i = 0; i < 4; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

static void displaytableListBorrowBooks(QTableView* tableView, const std::vector<ObjBaRBook>& data){
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(3);  // Số cột dự kiến

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("Mã sách"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên sách"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Ngày mượn"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjBaRBook& book = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(book.getBookID())));
        model->setItem(row, 1, new QStandardItem(book.getBookName()));

        // Format ngày mượn thành chuỗi ngày tháng năm
        QString formattedBorrowDate = book.getBookBorrowDate().toString("yyyy-MM-dd");
        model->setItem(row, 2, new QStandardItem(formattedBorrowDate));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
    for (int i = 0; i < 2; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

static void displaytableListHeadBooksfind(QTableView* tableView, const std::vector<ObjHeadBook>& data){
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(6);  // Số cột, tùy thuộc vào dữ liệu của ObjHeadBook

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("ISBN"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên Sách"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Số Trang"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Tác Giả"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Năm Xuất Bản"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Loại Sách"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjHeadBook& headbook = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(headbook.getISBN())));
        model->setItem(row, 1, new QStandardItem(headbook.getBookName()));
        model->setItem(row, 2, new QStandardItem(QString::number(headbook.getNumberPage())));
        model->setItem(row, 3, new QStandardItem(headbook.getAuthor()));
        model->setItem(row, 4, new QStandardItem(QString::number(headbook.getPublishingYear())));
        model->setItem(row, 5, new QStandardItem(headbook.getBookType()));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
    for (int i = 0; i < 6; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

static void displayTop10Sach(QTableView* tableView, const std::vector<ObjHeadBook>& data)
{
    QStandardItemModel* model = new QStandardItemModel(data.size(), 7, tableView);

    // Đặt tiêu đề cho từng cột
    model->setHorizontalHeaderItem(0, new QStandardItem("ISBN"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên sách"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Số trang"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Tác giả"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Năm xuất bản"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Thể loại"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Lượt mượn"));

    // Đổ dữ liệu từ top10Books vào model
    for (int row = 0; row < data.size(); ++row) {
        const ObjHeadBook& headbook = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(headbook.getISBN())));
        model->setItem(row, 1, new QStandardItem(headbook.getBookName()));
        model->setItem(row, 2, new QStandardItem(QString::number(headbook.getNumberPage())));
        model->setItem(row, 3, new QStandardItem(headbook.getAuthor()));
        model->setItem(row, 4, new QStandardItem(QString::number(headbook.getPublishingYear())));
        model->setItem(row, 5, new QStandardItem(headbook.getBookType()));
        model->setItem(row, 6, new QStandardItem(QString::number(headbook.getNumberBorrowedTime())));
    }

    // Gán model cho tableView
    tableView->setModel(model);
    for (int i = 0; i < 7; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    for(int j = 0; j <=10;++j){
        tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

static void displaytableListReader(QTableView* tableView, const std::vector<ObjReader>& data)
{
    QStandardItemModel* model = new QStandardItemModel(data.size(), 4 , tableView);

    // Đặt tiêu đề cho từng cột
    model->setHorizontalHeaderItem(0, new QStandardItem("Mã độc giả"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên độc giả"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Giới tính"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Trạng thái thẻ"));

    // Đổ dữ liệu từ top10Books vào model
    for (int row = 0; row < data.size(); ++row) {
        const ObjReader& rd = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(rd.getReaderID())));
        model->setItem(row, 1, new QStandardItem(rd.getReaderName()));
        model->setItem(row, 2, new QStandardItem(rd.getReaderSex()));
        if(rd.getReaderStatus()==0)
        {
            model->setItem(row, 3, new QStandardItem("Thẻ bị khóa"));
        }
        else{
            model->setItem(row, 3, new QStandardItem("Đang hoạt động"));
        }
    }
    // Gán model cho tableView
    tableView->setModel(model);
    for (int i = 0; i < 4; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

static void displayhistoryBaRBook(QTableView* tableView, const std::vector<ObjBaRBook>& data)
{
    QStandardItemModel* model = new QStandardItemModel(tableView);
    model->setColumnCount(5);  // Số cột dự kiến

    // Đặt tên cột cho bảng
    model->setHorizontalHeaderItem(0, new QStandardItem("Mã sách"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Tên sách"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Ngày mượn"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Ngày trả"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Mã độc giả đang mượn sách"));

    // Đặt số hàng dựa trên kích thước vector
    model->setRowCount(data.size());

    // Lặp qua vector và thêm dữ liệu vào mô hình
    for (int row = 0; row < data.size(); ++row) {
        const ObjBaRBook& book = data[row];
        model->setItem(row, 0, new QStandardItem(QString::number(book.getBookID())));
        model->setItem(row, 1, new QStandardItem(book.getBookName()));
        QString formattedBorrowDate = book.getBookBorrowDate().toString("yyyy-MM-dd");
        model->setItem(row, 2, new QStandardItem(formattedBorrowDate));
        QString formattedReturnDate = book.getBookReturnDate().toString("yyyy-MM-dd");
        model->setItem(row, 3, new QStandardItem(formattedReturnDate));
        model->setItem(row, 4, new QStandardItem(QString::number(book.getReaderID())));
    }

    // Gán mô hình dữ liệu cho QTableView
    tableView->setModel(model);
    for (int i = 0; i < 5; ++i) {
        tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}
#endif // DISPLAYLIST_H
