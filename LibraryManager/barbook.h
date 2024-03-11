#ifndef BARBOOK_H
#define BARBOOK_H

#include <QMainWindow>

namespace Ui {
class BARbook;
}

class BARbook : public QMainWindow
{
    Q_OBJECT

public:
    explicit BARbook(QWidget *parent = nullptr);
    ~BARbook();

private slots:
    void on_btnFindHeadBook_clicked();

    void on_btnFindReader_clicked();

    void on_tableBookBorrow_clicked(const QModelIndex &index);

    void on_tableListBook_clicked(const QModelIndex &index);


    void on_btnBorrowBook_clicked();

    void on_btnReturnBook_clicked();

    void on_pushButton_clicked();

private:
    Ui::BARbook *ui;
};

#endif // BARBOOK_H
