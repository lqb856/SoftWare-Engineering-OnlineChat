#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>

#include "clients.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //客户端消息响应函数
    void New_client_come(QTcpSocket *skt);
    void Match_client(QTcpSocket *skt);
    void Match_cancel(QTcpSocket *skt);
    void Send_to_other(QString msg, QTcpSocket *skt);
    void Send_to_all(QString msg, QTcpSocket *skt);
    void End_chat(QTcpSocket *skt);
    void Offline(QTcpSocket *skt);
    void Match(QTcpSocket *skt);

    //服务器函数
    int Judge_command(QString command);
    QString Get_local_ip();
    void Send_msg();
    void Handle_new_connect();
    void Read_msg();

    QTcpServer * m_tcpServer;
    QList<QTcpSocket*> m_socketList;
    QList<Clients> m_clientsList;
    QList<Clients> m_clientsForMatch;


};
#endif // MAINWINDOW_H
