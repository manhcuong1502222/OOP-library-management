#include "headbook.h"
#include "ui_headbook.h"
#include "ObjHeadbook.h"
#include "ObjBook.h"
#include "displaylist.h"

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <vector>
#include <QString>
#include <QMessageBox>
using namespace std;

QString fileHeadBook = "C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt";
QString fileBook = "C:/Users/84976/Documents/LibraryManager/txtfile/book.txt";

Headbook::Headbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Headbook)
{
    ui->setupUi(this);

}

Headbook::~Headbook()
{
    delete ui;
}


void Headbook::on_BtnRefresh_clicked()
{
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    vector<ObjHeadBook> listhb = lhb.getHeadBooks();
    displaytableListHeadBooksfind(ui->TableListHeadbook,listhb);
}


void Headbook::on_TableListHeadbook_clicked(const QModelIndex &index)
{
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    ListBook lb;
    lb.loadFromTextFile(fileBook);
    lhb.loadBooksToHeadBooks(lb);

    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->TableListHeadbook->model());

        if (model) {
            QString ISBN = model->item(row, 0)->text();
            QString Bookname = model->item(row, 1)->text();
            QString PagesNumber = model->item(row, 2)->text();
            QString Author = model->item(row,3)->text();
            QString PublishingYear = model->item(row, 4)->text();
            QString TypeHeadbook = model->item(row, 5)->text();

            ui->txtISBN->setPlainText(ISBN);
            ui->txtBookname->setPlainText(Bookname);
            ui->txtPagesNumber->setPlainText(PagesNumber);
            ui->txtAuthor->setPlainText(Author);
            ui->txtPublishingYear->setPlainText(PublishingYear);
            ui->txtTypeHeadbook->setPlainText(TypeHeadbook);
            vector<ObjBook> a = lhb.getBooksfromHeadBook(ISBN.toInt());
            displaytableListBooks(ui->tableListBook, a);
        }
    }
}


void Headbook::on_btnAddHeadbook_clicked()
{
    bool conversionSuccessful = false;

    // Lấy dữ liệu từ các QPlainTextEdit và kiểm tra kiểu dữ liệu
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Ma ISBN Khong hop le");
        return; // Không thực hiện xóa sách nếu ISBN không phải số nguyên.
    }

    QString TextISBN =  ui->txtISBN->toPlainText();


    QString Bookname = ui->txtBookname->toPlainText();

    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Số trang không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thêm sách nếu số trang không phải số nguyên.
    }

    QString Author = ui->txtAuthor->toPlainText();

    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Năm xuất bản không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thêm sách nếu năm xuất bản không phải số nguyên.
    }

    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();

    // Tạo một đối tượng ObjBook từ dữ liệu
    ObjHeadBook headbook(ISBN, Bookname, PagesNumber, Author, PublishingYear, TypeHeadbook,0);

    // Thêm đối tượng vào ListBook
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    for (const ObjHeadBook& existingHeadbook : lhb.getHeadBooks()) {
        if (existingHeadbook.getISBN() == ISBN || existingHeadbook.getBookName() == Bookname) {
            QMessageBox::critical(this, "Lỗi", "Sách đã tồn tại trong thư viện.");
            return;
        }

    }
    lhb.addHeadBook(headbook);

    vector<ObjHeadBook> newlisthb = lhb.getHeadBooks();
    displaytableListHeadBooksfind(ui->TableListHeadbook,newlisthb);

    // Xóa dữ liệu từ các QPlainTextEdit sau khi đã thêm sách
    ui->txtISBN->clear();
    ui->txtBookname->clear();
    ui->txtPagesNumber->clear();
    ui->txtAuthor->clear();
    ui->txtPublishingYear->clear();
    ui->txtTypeHeadbook->clear();
    QMessageBox::information(this, "Thành công", "Đã thêm đầu sách " + Bookname + " có mã " + TextISBN + " Vào thư viện "  );
}


void Headbook::on_btnRemoveHeadBook_clicked()
{
    bool conversionSuccessful = false;
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    QString txtISBN = ui->txtISBN->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "ISBN không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện xóa sách nếu ISBN không phải số nguyên.
    }

    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    ListBook lb;
    lb.loadFromTextFile(fileBook);
    lhb.loadBooksToHeadBooks(lb);
    if(lhb.isHeadbookhasbook(ISBN))
    {
        QMessageBox::critical(this, "Lỗi", "Đang có các sách thuộc đầu sách này trong thư viện, không thể xóa");
        return;
    }
    QString Bookname = lhb.getHeadBookbyISBN(ISBN).getBookName();
    lhb.deleteHeadBook(ISBN);
    vector<ObjHeadBook> newlisthb = lhb.getHeadBooks();
    displaytableListHeadBooksfind(ui->TableListHeadbook,newlisthb);

    QMessageBox::information(this, "Thành công", "Đã xóa đầu sách " + Bookname + " có mã " + txtISBN + " Vào thư viện "  );
}


void Headbook::on_btnFixHeadBook_clicked()
{
    bool conversionSuccessful = false;
    int ISBN = ui->txtISBN->toPlainText().toInt(&conversionSuccessful);
    QString txtISBN = ui->txtISBN->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "ISBN không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu ISBN không phải số nguyên.
    }

    QString Bookname = ui->txtBookname->toPlainText();
    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Số trang không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu số trang không phải số nguyên.
    }

    QString Author = ui->txtAuthor->toPlainText();
    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Năm xuất bản không phải là một số nguyên hợp lệ.");
        return; // Không thực hiện thay đổi thông tin đầu sách nếu năm xuất bản không phải số nguyên.
    }

    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();


    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    ListBook lb;
    lb.loadFromTextFile(fileBook);
    if (lhb.FindHeadBookbyISBN(ISBN)==true) {
        QString OldBookName = lhb.getHeadBookbyISBN(ISBN).getBookName();
        // Tìm thấy đầu sách với ISBN tương ứng
        lhb.uppdateHeadBook(ISBN, Bookname, PagesNumber, Author, PublishingYear, TypeHeadbook);
        for(const ObjBook& book: lb.getBooks())
        {
            lb.fixBookname(OldBookName, Bookname);
        }
    }
    else {
        QMessageBox::critical(this, "Lỗi", "Không có đầu sách có mã ISBN này trong thư viện.");
    }

    vector<ObjHeadBook> newlisthb = lhb.getHeadBooks();
    displaytableListHeadBooksfind(ui->TableListHeadbook,newlisthb);
    QMessageBox::information(this, "Thành công", "Đã sửa đầu sách có mã đầu sách " + txtISBN + " thành công" );

}



void Headbook::on_btnFindHeadBook_clicked()
{
    int ISBN = ui->txtISBN->toPlainText().toInt();
    QString Bookname = ui->txtBookname->toPlainText();
    int PagesNumber = ui->txtPagesNumber->toPlainText().toInt();
    QString Author = ui->txtAuthor->toPlainText();
    int PublishingYear = ui->txtPublishingYear->toPlainText().toInt();
    QString TypeHeadbook = ui->txtTypeHeadbook->toPlainText();

    vector<ObjHeadBook> findheadbook;
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        if(hb.getISBN()==ISBN || hb.getBookName() == Bookname || hb.getAuthor() == Author || hb.getBookType() == TypeHeadbook)
        {
            findheadbook.push_back(hb);
        }
    }
    displaytableListHeadBooksfind(ui->TableListHeadbook,findheadbook);
}


void Headbook::on_btnAddBook_clicked()
{
    QString BookName = ui->txtBookName->toPlainText();

    QString Location = ui->txtLocation->toPlainText();

    ListBook lb;
    ListHeadBook lhb;
    lhb.loadFromTextFile(fileHeadBook);
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        if (hb.getBookName() == BookName) {
            foundHeadBook = true;
            break;
        }
    }

    if (foundHeadBook) {
        ObjBook newbook = lb.addBook(BookName,Location);
        QString newBookID = QString::number(newbook.getBookID());

        QMessageBox::information(this, "Thành Công", "Đã thêm sách " + BookName + " Có mã " + newBookID );
    }
    else
    {
        QMessageBox::critical(this, "Lỗi", "Đầu sách này không có trong thư viện");
    }

}


void Headbook::on_btnDeleteBook_clicked()
{
    bool conversionSuccessful = false;
    int IDBook = ui->txtIDBook->toPlainText().toInt(&conversionSuccessful);
    QString txtIDBook = ui->txtIDBook->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã Sách Không hợp lệ");
        return; // Không thực hiện thêm sách nếu Mã Sách không phải số nguyên.
    }

    ListBook lb;
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjBook& book : lb.getBooks()) {
        if (book.getBookID() == IDBook) {
            foundHeadBook = true;
            break;
        }
    }

    if(lb.isBookBorrowred(IDBook)==true)
    {
        QMessageBox::critical(this, "Lỗi", "Sách này đang được mượn không thể xóa");
        return;
    }

    if (foundHeadBook) {
        lb.removeBook(IDBook);
        QMessageBox::information(this, "Thành công", "Đã xóa sách có mã " + txtIDBook );
    } else {
        QMessageBox::critical(this, "Lỗi", "Mã sách này không tồn tại");
    }
}


void Headbook::on_tableListBook_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->tableListBook->model());

        if (model) {
            QString IDBook = model->item(row, 0)->text();
            QString Bookname = model->item(row, 1)->text();
            QString Status = model->item(row, 2)->text();
            QString Location = model->item(row,3)->text();

            ui->txtIDBook->setPlainText(IDBook);
            ui->txtBookName->setPlainText(Bookname);
            ui->txtStatus->setPlainText(Status);
            ui->txtLocation->setPlainText(Location);
        }
    }
}


void Headbook::on_btnFixBook_clicked()
{
    bool conversionSuccessful = false;
    int IDBook = ui->txtIDBook->toPlainText().toInt(&conversionSuccessful);
    QString txtIDBook = ui->txtIDBook->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã Sách Không hợp lệ");
        return; // Không thực hiện thêm sách nếu Mã Sách không phải số nguyên.
    }

    QString Location = ui->txtLocation->toPlainText();

    ListBook lb;
    lb.loadFromTextFile(fileBook);

    bool foundHeadBook = false;
    for (const ObjBook& book : lb.getBooks()) {
        if (book.getBookID() == IDBook) {
            foundHeadBook = true;
            break;
        }
    }

    if(lb.isBookBorrowred(IDBook)==true)
    {
        QMessageBox::critical(this, "Lỗi", "Sách đang cho mượn không thể thay đổi vị trí");
        return;
    }

    if (foundHeadBook) {
        lb.updateBookLocation(IDBook,Location);
        QMessageBox::information(this, "Thành công", "Đã thay đổi vị trí sách có mã " + txtIDBook + " trong thư viện" );
    } else {
        QMessageBox::critical(this, "Lỗi", "Mã sách này không tồn tại");
    }
}

