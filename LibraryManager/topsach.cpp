#include "topsach.h"
#include "ui_topsach.h"
#include "ObjReader.h"
#include "ObjHeadBook.h"
#include "ObjBaRBook.h"
#include "displaylist.h"
#include <QStandardItemModel>

TopSach::TopSach(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TopSach)
{
    ui->setupUi(this);
    ListHeadBook lhb;
    lhb.loadFromTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/headbook.txt");
    ListBaRBook lbb;
    lbb.loadFromTextFile("C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt");
    lhb.loadNumberBorrowredtoHeadBook(lbb);
    vector<ObjHeadBook> top10 = lhb.printtop10HeadBook();
    displayTop10Sach(ui->tableTop10Book,top10);
}

TopSach::~TopSach()
{
    delete ui;
}
