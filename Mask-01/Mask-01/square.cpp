#include "square.h"
#include "ui_square.h"


Square::Square(QWidget *parent) :
    ui(new Ui::Square),
  QMainWindow(parent)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap("://maskicon.png"));
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("广场");

}

void Square::closeEvent (QCloseEvent * e)
{
    if(QMessageBox::Yes==QMessageBox::question(this, "退出提醒", "确定退出？", QMessageBox::Yes,QMessageBox::No))
    {
        emit(SquareClose());

    }
    else
        e->ignore();
}


Square::~Square()
{
    delete ui;
}
