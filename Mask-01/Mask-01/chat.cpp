#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}


void Chat::closeEvent (QCloseEvent * e)
{
    if(QMessageBox::Yes==QMessageBox::question(this, "退出提醒", "确定退出？", QMessageBox::Yes,QMessageBox::No))
    {
        emit(ChatClose());
    }
    else
        e->ignore();
}

Chat::~Chat()
{
    delete ui;
}
