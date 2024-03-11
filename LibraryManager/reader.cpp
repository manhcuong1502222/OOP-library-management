#include "reader.h"
#include "ui_reader.h"
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
#include "ObjReader.h"
#include "ObjBaRBook.h"

using namespace std;

QString fileReader = "C:/Users/84976/Documents/LibraryManager/txtfile/reader.txt";
QString filebb ="C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt";

reader::reader(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);
    ui->groupProfileReader->setVisible(false);
}

reader::~reader()
{
    delete ui;
}


void reader::on_tableListReader_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        QStandardItemModel *model = dynamic_cast<QStandardItemModel*>(ui->tableListReader->model());

        if (model) {
            ui->groupProfileReader->setVisible(true);
            QString ReaderID = model->item(row, 0)->text();
            QString ReaderName = model->item(row, 1)->text();
            QString ReaderSex = model->item(row, 2)->text();
            QString ReaderStatus = model->item(row,3)->text();

            ui->lbReaderID->setText(ReaderID);
            ui->txtNameReader->setPlainText(ReaderName);
            ui->txtReaderSex->setPlainText(ReaderSex);
            ui->lbReaderStatus->setText(ReaderStatus);
        }

    }
    else
    {
        ui->groupProfileReader->setVisible(false);
    }
}


void reader::on_btnRefreshreder_clicked()
{
    ListReader lrd;
    lrd.loadFromTextFile(fileReader);
    vector<ObjReader> listrd = lrd.getReaders();
    displaytableListReader(ui->tableListReader, listrd);
}


void reader::on_btnRegist_clicked()
{
    QString ipName = ui->txtinputName->toPlainText();
    QString ipSex = ui->txtinputSex->toPlainText();
    if(ipSex != "Nam" && ipSex != "Nu")
    {
        QMessageBox::critical(this, "Lỗi", "Giới tính phải là Nam hoặc Nu");
    }
    else{
        ListReader rd;
        rd.loadFromTextFile(fileReader);
        ObjReader newReader = rd.addReader(ipName,ipSex);
        vector<ObjReader> listrd = rd.getReaders();
        displaytableListReader(ui->tableListReader,listrd);
        int newReaderID = newReader.getReaderID();
        QString message = "Mã độc giả vừa thêm vào là " + QString::number(newReaderID);
        QMessageBox::information(this, "Thành công", message);
        ui->groupProfileReader->setVisible(true);
        ui->lbReaderID->setText(QString::number(newReaderID)); // Thêm dấu "->" và chuyển đổi dữ liệu thành QString
        ui->txtNameReader->setPlainText(newReader.getReaderName()); // Thêm .setText()
        ui->txtReaderSex->setPlainText(newReader.getReaderSex()); // Thêm .setText()
        ui->lbReaderStatus->setText("Đang hoạt động"); // Thêm .setText()
    }
}



void reader::on_btnRemoveReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->lbReaderID->text().toInt(&conversionSuccessful);
    ListReader rd;
    rd.loadFromTextFile(fileReader);
    if (!conversionSuccessful) {
            QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
            return;
    }
    else
    {

        ListBaRBook lbb;
        lbb.loadFromTextFile(filebb);
        rd.LoadBaRBookstoReader(lbb);
        if(rd.isReaderIDExists(ReaderID)==false)
        {
           QMessageBox::critical(this, "Lỗi", "Mã độc giả không có trong thư viện");
            return;

        }
        if(rd.isReadrhasBaRBook(ReaderID)==true)
        {
            QMessageBox::critical(this, "Lỗi", "Độc giả này đang mượn sách trong thư viện không thể xóa");
            return;
        }
        ObjReader newReader = rd.getReaderbyID(ReaderID);
        int newReaderID = newReader.getReaderID();
        QString message = "Đã xóa độc giả có mã " + QString::number(newReaderID);
        QMessageBox::information(this, "Thành công", message);
        rd.removeReader(ReaderID);
    }
    vector<ObjReader> listrd = rd.getReaders();
    displaytableListReader(ui->tableListReader,listrd);
}


void reader::on_btnUpdateReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->lbReaderID->text().toInt(&conversionSuccessful);
    QString ReaderName = ui->txtNameReader->toPlainText();
    QString ReaderSex = ui->txtReaderSex->toPlainText();
    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
        return;
    }
    if(ReaderSex != "Nam" && ReaderSex != "Nu")
    {
        QMessageBox::critical(this, "Lỗi", "Giới tính phải là Nam hoặc Nu");
        return;
    }

    ListReader rd;
    rd.loadFromTextFile(fileReader);
    if(rd.isReaderIDExists(ReaderID)==false)
        {
           QMessageBox::critical(this, "Lỗi", "Mã độc giả không có trong thư viện");
        }
    else
        {
           ObjReader newReader = rd.getReaderbyID(ReaderID);
           int newReaderID = newReader.getReaderID();
           QString message = "Đã sửa thông tin độc giả có mã " + QString::number(newReaderID);
           QMessageBox::information(this, "Thành công", message);
           rd.updateReader(ReaderID,ReaderName,ReaderSex);
        }
    vector<ObjReader> listrd = rd.getReaders();
    displaytableListReader(ui->tableListReader,listrd);
}


void reader::on_btnBlockReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->lbReaderID->text().toInt(&conversionSuccessful);

    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
        return;
    }

    ListReader rd;
    rd.loadFromTextFile(fileReader);

    if (!rd.isReaderIDExists(ReaderID)) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không tồn tại trong thư viện");
        return;
    }

    ObjReader newReader = rd.getReaderbyID(ReaderID);

    if (newReader.getReaderStatus() == 1) {
        rd.BlockReader(ReaderID);
        QString message = "Đã khóa thẻ độc giả có mã" + QString::number(ReaderID);
        QMessageBox::information(this, "Thành công", message);
    } else {
        QMessageBox::critical(this, "Lỗi", "Thẻ của độc giả bị khóa trước đó");
    }

    // Cập nhật giao diện người dùng
    vector<ObjReader> listrd = rd.getReaders();
    displaytableListReader(ui->tableListReader, listrd);

    // Cập nhật thông tin độc giả
    ui->lbReaderID->setText(QString::number(newReader.getReaderID()));
    ui->txtNameReader->setPlainText(newReader.getReaderName());
    ui->txtReaderSex->setPlainText(newReader.getReaderSex());
    ui->lbReaderStatus->setText(newReader.getReaderStatus() == 0 ? "Thẻ bị khóa" : "Đang hoạt động");
}


void reader::on_btnUnBlockReader_clicked()
{
    bool conversionSuccessful = false;
    int ReaderID = ui->lbReaderID->text().toInt(&conversionSuccessful);

    if (!conversionSuccessful) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không hợp lệ");
        return;
    }

    ListReader rd;
    rd.loadFromTextFile(fileReader);

    if (!rd.isReaderIDExists(ReaderID)) {
        QMessageBox::critical(this, "Lỗi", "Mã độc giả không tồn tại trong thư viện");
        return;
    }

    ObjReader newReader = rd.getReaderbyID(ReaderID);

    if (newReader.getReaderStatus() == 0) {
        rd.unBlockReader(ReaderID);
        QString message = "Đã mở lại thẻ độc giả có mã " + QString::number(ReaderID);
        QMessageBox::information(this, "Thành công", message);
    } else {
        QMessageBox::critical(this, "Lỗi", "Thẻ của độc giả đã được mở khóa trước đó");
    }

    // Cập nhật giao diện người dùng
    vector<ObjReader> listrd = rd.getReaders();
    displaytableListReader(ui->tableListReader, listrd);

    // Cập nhật thông tin độc giả
    ui->lbReaderID->setText(QString::number(newReader.getReaderID()));
    ui->txtNameReader->setPlainText(newReader.getReaderName());
    ui->txtReaderSex->setPlainText(newReader.getReaderSex());
    ui->lbReaderStatus->setText(newReader.getReaderStatus() == 0 ? "Thẻ bị khóa" : "Đang hoạt động");
}


void reader::on_btnFindReader_clicked()
{
    int ReaderID = ui->txtinputReaderIDFind->toPlainText().toInt();
    QString ReaderName = ui->txtinputReaderNameFind->toPlainText();
    vector<ObjReader> listrd;
    ListReader lrd;
    lrd.loadFromTextFile(fileReader);
    for(const ObjReader& rd: lrd.getReaders())
    {
           if(rd.getReaderID()==ReaderID||rd.getReaderName()==ReaderName)
           {
            listrd.push_back(rd);
           }
    }
    displaytableListReader(ui->tableListReader,listrd);
    ui->groupProfileReader->setVisible(false);
}

