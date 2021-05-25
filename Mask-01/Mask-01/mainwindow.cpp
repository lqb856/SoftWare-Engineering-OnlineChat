#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_square.h"
#include "ui_chat.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    square = new Square;
    chat = new Chat;
    tcpsocket=new QTcpSocket;
    this->setFixedSize(this->width(),this->height());
    this->setWindowIcon(QPixmap("://maskicon.png"));
    this->setWindowTitle("Mask匿名聊天系统");

    connect(ui->LogBtn,&QPushButton::clicked,this,[=]()     //登录按钮点击
    {
        QString Ip = ui->serverIp->text();                      //从lineEdit获取输入的IP
        quint16 port = ui->serverPort->text().toInt();                    //获取端口号
        tcpsocket->connectToHost(QHostAddress(Ip),port);        //连接到服务器

        square->show();
        this->hide();
    });

    connect(square->ui->squareMatch, &QPushButton::clicked, this, [=]{   //匹配按钮点击
        QString Match ="001";
        QByteArray str = Match.toUtf8();
        str.append('\n');
        tcpsocket->write(str);
    } );

    connect(chat->ui->chatReturn, &QPushButton::clicked, this, [=]{   //退出私聊按钮点击
        QString Match ="006";
        QByteArray str = Match.toUtf8();
        str.append('\n');
        tcpsocket->write(str);

        chat->hide();
        square->show();
    } );

    connect(square->ui->squareSend,&QPushButton::clicked,this,[=]()        //群发消息
    {
        QString msg ="004"+ square->ui->squareText->text();             //为消息加标头
        QByteArray str = msg.toUtf8();                          //转换为Utf8编码
        str.append('\n');                                       //添加换行符
        tcpsocket->write(str);                                  //发送到socket

        msg = msg.remove(0,3);
        square->ui->squareShow->appendPlainText("[自己]："+msg+"\n");
        square->ui->squareText->clear();
        square->ui->squareText->setFocus();

    });

    connect(tcpsocket,&QTcpSocket::readyRead,this,[=]()         //从套接口读取消息
    {
        while(tcpsocket->canReadLine())                         //套接口有消息可读
        {
            QString msg =tcpsocket->readAll();                  //一次读取全部消息

            qDebug()<<msg;
            QString server=msg.left(3);                         //取得消息标头
            qDebug()<<server;

            int command = this->Judge_command(server);          //通过标头取得消息类型
            switch (command)
            {
            case 0:
            {
                qDebug()<<"新用户";                              //新用户到来提醒
                square->ui->squareCurOnline->display(msg.remove(0,3));
                break;
            }

            case 1:
            {
                qDebug()<<"匹配成功";                         //匹配提醒
                square->hide();
                chat->show();
                chat->setFixedSize(chat->width(), chat->height());
                break;
            }

            case 2:
            {
                qDebug()<<"取消匹配";                             //取消匹配成功
                //this->Match_cancel(socket);
                QMessageBox::information(square,"系统提示","取消成功！");
                break;
            }

            case 3:
            {
                qDebug()<<"这是to other命令";                     //私聊消息
                chat->ui->chatShow->appendPlainText(msg.remove(0,3));
                break;
            }

            case 4:
            {
                qDebug()<<"这是一个 to all命令";                   //群聊消息
                square->ui->squareShow->appendPlainText(msg.remove(0,3));
                break;
            }

            case 5:
            {
                qDebug()<<"这是一个 lalala命令";                   //聊天对象退出消息
                //square->ui->squareCurOnline->display(msg.remove(0,3).toDouble());
                QMessageBox::information(chat,"系统提示","你的聊天对象已退出！");
                break;
            }

            case 6:
            {
                qDebug()<<"这是一个 lalala1命令";                   //聊天对象退出消息
                //square->ui->squareCurOnline->display(msg.remove(0,3).toDouble());
                QMessageBox::information(chat,"系统提示","你还没有匹配！");
                break;
            }

            case 7:
            {
                qDebug()<<"这是一个 lalala1命令";                   //聊天对象退出消息
                //square->ui->squareCurOnline->display(msg.remove(0,3).toDouble());
                QMessageBox::information(square,"系统提示","现在匹配人数不足，稍后再试吧！");
                break;
            }

            default:
            {
                qDebug()<<"错误的命令";
                break;
            }
            }
        }
    });

    connect(tcpsocket,&QTcpSocket::connected,this,[=]()          //连接建立成功，发送新用户到达消息
    {
        QString newMsg = "000";                                  //新用户消息
        QByteArray str = newMsg.toUtf8();
        str.append('\n');
        qDebug()<<newMsg<<" "<<str;
        tcpsocket->write(str);
    });

    connect(chat->ui->chatSend,&QPushButton::clicked,this,[=]()     //私聊消息
    {
        QString toOtherMsg="003";                                //私聊信息发送
        QString msg =toOtherMsg+ chat->ui->chatText->text();
        QByteArray str = msg.toUtf8();
        str.append('\n');
        tcpsocket->write(str);

        chat->ui->chatShow->appendPlainText("[自己]："+chat->ui->chatText->text()+"\n");
        chat->ui->chatText->clear();
        chat->ui->chatText->setFocus();

    });

    connect(square,&Square::SquareClose,this,[=]()     //下线消息
    {
        qDebug()<<"lalal";
        QString offLineMsg="005";
        QByteArray str = offLineMsg.toUtf8();
        str.append('\n');
        tcpsocket->write(str);
        tcpsocket->disconnectFromHost();
        chat->close();
    });

    connect(chat,&Chat::ChatClose,this,[=]()     //下线消息
    {
        QString offLineMsg="005";
        QByteArray str = offLineMsg.toUtf8();
        str.append('\n');
        tcpsocket->write(str);
        tcpsocket->disconnectFromHost();
        chat->close();
    });

    connect(square->ui->squareMatchCancel,&QPushButton::clicked,this,[=]() //取消配对消息
    {
        QString MatchCancel ="002";
        QByteArray str = MatchCancel.toUtf8();
        str.append('\n');
        tcpsocket->write(str);
    });


}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("://background.jfif");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}

int MainWindow::Judge_command(QString command)                    //客户端接收到的消息
{
    if(command=="000"){return 0;}   //新用户消息
    if(command=="001"){return 1;}   //配对消息
    if(command=="002"){return 2;}   //取消配对
    if(command=="003"){return 3;}   //私聊
    if(command=="004"){return 4;}   //群聊
    if(command=="005"){return 5;}   //聊天对象退出私聊
    if(command=="006"){return 6;}   //找不到匹配对象
    if(command=="007"){return 7;}   //匹配不到消息
    return -1;
}


MainWindow::~MainWindow()
{
    tcpsocket->deleteLater();
    delete ui;
}

