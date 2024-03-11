#include "historybarbook.h"
#include "ui_historybarbook.h"
#include "ObjBaRBook.h"
#include "displaylist.h"

QString filehistory = "C:/Users/84976/Documents/LibraryManager/txtfile/barbook.txt" ;

historyBaRBook::historyBaRBook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::historyBaRBook)
{
    ui->setupUi(this);
    ListBaRBook lbb;
    lbb.loadFromTextFile(filehistory);
    vector<ObjBaRBook> history = lbb.getBaRBooks();
    displayhistoryBaRBook(ui->tableHistoryBaRBook, history);
}

historyBaRBook::~historyBaRBook()
{
    delete ui;
}
