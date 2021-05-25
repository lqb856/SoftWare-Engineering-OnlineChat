#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QTcpSocket>
#include <QHostInfo>
#include <QMessageBox>

#include "square.h"
#include "chat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    Square *square;
    Chat *chat;

    int Judge_command(QString command);
    QTcpSocket * tcpsocket;
};
#endif // MAINWINDOW_H
