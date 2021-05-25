#ifndef SQUARE_H
#define SQUARE_H

#include <QMainWindow>
#include <QToolButton>
#include <QMessageBox>
#include "chat.h"
namespace Ui {
class Square;
}

class Square : public QMainWindow
{
    Q_OBJECT

public:
     Ui::Square *ui;
    void closeEvent (QCloseEvent * e);
    explicit Square(QWidget *parent = nullptr);
    ~Square();

private:
    QAction *act ;
signals:
    void SquareClose();
};

#endif // SQUARE_H
