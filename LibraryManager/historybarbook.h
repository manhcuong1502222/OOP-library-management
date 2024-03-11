#ifndef HISTORYBARBOOK_H
#define HISTORYBARBOOK_H

#include <QMainWindow>

namespace Ui {
class historyBaRBook;
}

class historyBaRBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit historyBaRBook(QWidget *parent = nullptr);
    ~historyBaRBook();

private:
    Ui::historyBaRBook *ui;
};

#endif // HISTORYBARBOOK_H
