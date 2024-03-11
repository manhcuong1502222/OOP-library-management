#include "barbook.h"
#include "ObjReader.h"
#include "ui_barbook.h"
#include "ObjHeadbook.h"
#include "ObjBook.h"
#include "displaylist.h"
#include "historybarbook.h"

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QList>
#include <QDebug>
#include <vector>
#include <QString>
#include <QMessageBox>
#include <QString>
#include <QTableView>

QString f1 = "C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt";
QString f2 = "C:/Users/84976/Documents/LibraryManager/txtfile/book.txt";
QString f3 = "C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt" ;
QString f4 = "C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt" ;

BARbook::BARbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BARbook)
{
    ui->setupUi(this);
    ui->btnReturnBook->setVisible(false);
    ui->btnBorrowBook->setVisible(false);
}

BARbook::~BARbook()
{
    delete ui;
}

void BARbook::on_btnFindHeadBook_clicked()
{
    int ISBN = ui->txtinputISBN->toPlainText().toInt();
    QString BookName  = ui->txtinputBookName->toPlainText();
    QString Author = ui->txtinputAuthor->toPlainText();
    QString TypeBook = ui->txtinputTypeBook->toPlainText();
    ListHeadBook lhb;
    ListBook lb;
    lhb.loadFromTextFile(f1);
    lb.loadFromTextFile(f2);
    vector<ObjBook> listbook;
    lhb.loadBooksToHeadBooks(lb);
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
       for(const ObjBook& b: hb.getBooks())
        {
            if(hb.getISBN() == ISBN || hb.getBookName() == BookName || hb.getAuthor() == Author || hb.getBookType() == TypeBook )
           {
               listbook.push_back(b);
           }
        }
    }
    displaytableListBooks(ui->tableListBook,listbook);
}


void BARbook::on_btnFindReader_clicked()
{
    bool conversionSuccessful = false;
    // Lấy dữ liệu từ các QPlainTextEdit và kiểm tra kiểu dữ liệu
    int ReaderID = ui->txtinputReaderID->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Ma Độc giả Khong hop le");
        return; // Không thực hiện xóa sách nếu ISBN không phải số nguyên.
    }

    ListReader lrd;
    lrd.loadFromTextFile(f3);
    ListBaRBook lbb;
    lbb.loadFromTextFile(f4);
    if(lrd.isReaderIDExists(ReaderID)==true)
    {
        lrd.LoadBaRBookstoReader(lbb);
        ObjReader newReader = lrd.getReaderbyID(ReaderID);
        ui->lbName->setText(newReader.getReaderName());
        ui->lbSex->setText(newReader.getReaderSex());
        if(newReader.getReaderStatus() == 0)
        {
           ui->lbStatusReader->setText("Thẻ bị khóa");
        }
        else{
           ui->lbStatusReader->setText("Đang hoạt động");
        }
        vector<ObjBaRBook> newBarBook = newReader.getBaRBooks();
        displaytableListBorrowBooks(ui->tableBookBorrow,newBarBook);
    }
    else
    {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không đúng");
    }
}


void BARbook::on_tableBookBorrow_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        int column = 0; // Lấy dữ liệu từ cột đầu tiên (0)

        // Lấy mã sách từ dòng được chọn
        QVariant data = ui->tableBookBorrow->model()->data(ui->tableBookBorrow->model()->index(row, column));

        bool ok;
        int bookCode = data.toInt(&ok);
        if (ok) {
           // Sử dụng mã sách để tìm thông tin sách trong ListBook
           ListBook listBook;
           if (listBook.loadFromTextFile(f2)) {
               const std::vector<ObjBook>& books = listBook.getBooks();
               for (const ObjBook& book : books) {
                   if (book.getBookID() == bookCode) {
                       // Tìm thấy sách, cập nhật các QLabel với thông tin sách
                       ui->lbIDBook->setText(QString::number(book.getBookID()));
                       ui->lbBookName->setText(book.getBookName());
                       ui->lbBookLocation->setText(book.getBookLocation());
                       if(book.getBookStatus() == 1)
                       {
                           ui->lbBookStatus->setText("Đã cho mượn");
                       }
                       else
                       {
                           ui->lbBookStatus->setText("Chưa cho mượn");
                       }
                       break;  // Thoát sau khi tìm thấy sách
                   }
               }
           }
           ui->btnReturnBook->setVisible(true);
           ui->btnBorrowBook->setVisible(false);
        } else {
           // Xử lý lỗi khi không thể chuyển đổi dữ liệu sang kiểu int
           qDebug() << "Không thể lấy mã sách từ dòng được chọn.";
           ui->btnReturnBook->setVisible(false);
           ui->btnBorrowBook->setVisible(false);
        }
    }
}


void BARbook::on_tableListBook_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        int column = 0; // Lấy dữ liệu từ cột đầu tiên (0)

        QAbstractItemModel *model = ui->tableListBook->model(); // Chắc chắn rằng bạn đang sử dụng tableListBook
        QVariant data = model->data(model->index(row, column));

        bool ok;
        int bookCode = data.toInt(&ok);

        if (ok) {
           // Tải danh sách sách từ tệp tin chỉ một lần, chẳng hạn khi khởi đầu lớp BARbook
           ListBook lb;
           lb.loadFromTextFile(f2);
           ObjBook newbook = lb.getBookbyBookCode(bookCode);
           ui->lbIDBook->setText(QString::number(newbook.getBookID()));
           ui->lbBookName->setText(newbook.getBookName());
           ui->lbBookLocation->setText(newbook.getBookLocation());
           if (newbook.getBookStatus() == 0) {
               ui->lbBookStatus->setText("Chưa cho mượn");
           } else {
               ui->lbBookStatus->setText("Đã cho mượn");
           }
           ui->btnReturnBook->setVisible(false);
           ui->btnBorrowBook->setVisible(true);
        } else {
           // Xử lý lỗi khi không thể chuyển đổi dữ liệu sang kiểu int
           qDebug() << "Không thể lấy mã sách từ dòng được chọn.";
           ui->btnReturnBook->setVisible(false);
           ui->btnBorrowBook->setVisible(false);
        }
    }
}


void BARbook::on_btnBorrowBook_clicked()
{
    //Kiem tra ma doc gia va ma sach
    bool conversionSuccessful = false;
    // Lấy dữ liệu từ các QPlainTextEdit và kiểm tra kiểu dữ liệu
    int ReaderID = ui->txtinputReaderID->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Ma Reader Khong hop le");
        return;
    }
    int BookCode = ui->lbIDBook->text().toInt(&conversionSuccessful);
    QString BookNamelb = ui->lbBookName->text();
    //---------------------------MuonSach----------------------------------
    ListBook lb;
    lb.loadFromTextFile(f2);
    ListReader lrd;
    lrd.loadFromTextFile(f3);
    ListBaRBook lbb;
    lbb.loadFromTextFile(f4);
    lrd.LoadBaRBookstoReader(lbb);
    if(lrd.isReaderIDExists(ReaderID)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không tồn tại");
        return;
    }
    if(lrd.isReaderActive(ReaderID)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Độc giả không còn hoạt động không thể mượn sách");
        return;
    }
    if(lb.isBookExist(BookCode)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Hãy chọn sách để mượn");
        return;
    }
    if(lrd.isBaRBookFull(ReaderID)==true)
    {
        QMessageBox::critical(this, "Lỗi", "Độc giả đã mượn đủ sách, hãy trả sách để mượn thêm sách");
        return;
    }
    if(lrd.isReaderHasBaRLimited(ReaderID)==true)
    {
        QMessageBox::critical(this, "Lỗi", "Độc giả đang mượn sách quá hạn, hãy trả sách quá hạn để mượn thêm sách");
        return;
    }
    if(lb.isBookBorrowred(BookCode)==true)
    {
        QMessageBox::critical(this, "Lỗi", "Sách này đã được mượn");
        return;
    }
    lbb.borrowBook(BookCode,BookNamelb,ReaderID);
    lb.BorrowandUpdateStatusBook(BookCode);
    //---------------------------Load lai thong tin len table view----------------------------------
    lb.loadFromTextFile(f2);
    lbb.loadFromTextFile(f4);
    lrd.loadFromTextFile(f3);
    //---------------------------Load lên table view danh sách mượn----------------------------------
    lrd.LoadBaRBookstoReader(lbb);
    ObjReader newReader = lrd.getReaderbyID(ReaderID);
    ui->lbName->setText(newReader.getReaderName());
    ui->lbSex->setText(newReader.getReaderSex());
    if(newReader.getReaderStatus() == 0)
        {
           ui->lbStatusReader->setText("Thẻ bị khóa");
        }
    else{
           ui->lbStatusReader->setText("Đang hoạt động");
        }
    vector<ObjBaRBook> newBarBook = newReader.getBaRBooks();
    displaytableListBorrowBooks(ui->tableBookBorrow,newBarBook);
    //---------------------------Load lên table view danh sách tìm kiếm----------------------------------
    int ISBN = ui->txtinputISBN->toPlainText().toInt();
    QString BookName  = ui->txtinputBookName->toPlainText();
    QString Author = ui->txtinputAuthor->toPlainText();
    QString TypeBook = ui->txtinputTypeBook->toPlainText();
    ListHeadBook lhb;
    lhb.loadFromTextFile(f1);
    vector<ObjBook> listbook;
    lhb.loadBooksToHeadBooks(lb);
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        for(const ObjBook& b: hb.getBooks())
        {
           if(hb.getISBN() == ISBN || hb.getBookName() == BookName || hb.getAuthor() == Author || hb.getBookType() == TypeBook )
           {
               listbook.push_back(b);
           }
        }
    }
    displaytableListBooks(ui->tableListBook,listbook);
    QMessageBox::information(this, "Thành công", "Mượn sách thành công" );
}


void BARbook::on_btnReturnBook_clicked()
{
    //Kiem tra ma doc gia va ma sach
    bool conversionSuccessful = false;
    // Lấy dữ liệu từ các QPlainTextEdit và kiểm tra kiểu dữ liệu
    int ReaderID = ui->txtinputReaderID->toPlainText().toInt(&conversionSuccessful);
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Ma Reader Khong hop le");
        return;
    }
    int BookCode = ui->lbIDBook->text().toInt(&conversionSuccessful);
    ListBook lb;
    lb.loadFromTextFile(f2);
    ListReader lrd;
    lrd.loadFromTextFile(f3);
    ListBaRBook lbb;
    lbb.loadFromTextFile(f4);
    lrd.LoadBaRBookstoReader(lbb);
    if(lrd.isReaderIDExists(ReaderID)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không tồn tại");
        return;
    }
    if(lb.isBookExist(BookCode)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Hãy chọn sách để trả");
        return;
    }
    if(lrd.isReaderBorrowingBook(ReaderID,BookCode)==false)
    {
        QMessageBox::critical(this, "Lỗi", "Độc giả không mượn sách này ");
        return;
    }
    lbb.returnBook(BookCode,ReaderID);
    lb.ReturnandUpdateStatusBook(BookCode);
    //---------------------------Load lai thong tin len table view----------------------------------
    lb.loadFromTextFile(f2);
    lbb.loadFromTextFile(f4);
    lrd.loadFromTextFile(f3);
    //---------------------------Load lên table view danh sách mượn----------------------------------
    lrd.LoadBaRBookstoReader(lbb);
    ObjReader newReader = lrd.getReaderbyID(ReaderID);
    ui->lbName->setText(newReader.getReaderName());
    ui->lbSex->setText(newReader.getReaderSex());
    if(newReader.getReaderStatus() == 0)
    {
        ui->lbStatusReader->setText("Thẻ bị khóa");
    }
    else{
        ui->lbStatusReader->setText("Đang hoạt động");
    }
    vector<ObjBaRBook> newBarBook = newReader.getBaRBooks();
    displaytableListBorrowBooks(ui->tableBookBorrow,newBarBook);
    //---------------------------Load lên table view danh sách tìm kiếm----------------------------------
    int ISBN = ui->txtinputISBN->toPlainText().toInt();
    QString BookName  = ui->txtinputBookName->toPlainText();
    QString Author = ui->txtinputAuthor->toPlainText();
    QString TypeBook = ui->txtinputTypeBook->toPlainText();
    ListHeadBook lhb;
    lhb.loadFromTextFile(f1);
    vector<ObjBook> listbook;
    lhb.loadBooksToHeadBooks(lb);
    for (const ObjHeadBook& hb : lhb.getHeadBooks()) {
        for(const ObjBook& b: hb.getBooks())
        {
           if(hb.getISBN() == ISBN || hb.getBookName() == BookName || hb.getAuthor() == Author || hb.getBookType() == TypeBook )
           {
               listbook.push_back(b);
           }
        }
    }
    displaytableListBooks(ui->tableListBook,listbook);
    QMessageBox::information(this, "Thành công", "Trả sách thành công" );
}



void BARbook::on_pushButton_clicked()
{
    historyBaRBook* nbb = new historyBaRBook(this);
    nbb -> show();
}

