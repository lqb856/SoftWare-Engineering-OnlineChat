#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化服务器，获取服务器Ip，设置监听端口"8848"
    m_tcpServer = new QTcpServer;
    QString ip = Get_local_ip();
    ui->lineEditIP->setText(ip);
    m_tcpServer->listen(QHostAddress(ip),8848);

    //槽函数，响应新连接
    connect(m_tcpServer,&QTcpServer::newConnection,this,&MainWindow::Handle_new_connect);
    connect(m_tcpServer,&QTcpServer::newConnection,this,[=]()
    {
        ui->plainTextEdit->appendPlainText("连接成功");
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Handle_new_connect()                           //处理新的到达连接
{
    QTcpSocket * socket = m_tcpServer->nextPendingConnection(); //取出到达连接
    m_socketList<<socket;                                       //加入socket列表
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::Read_msg);//注册处理函数
}

QString MainWindow::Get_local_ip()
{
    QString hostName =QHostInfo::localHostName();               //本地主机名
    QHostInfo hostInfo =QHostInfo::fromName(hostName);          //获取主机信息
    QString localIp="";
    QList<QHostAddress>addlist=hostInfo.addresses();            //取得主机所有IP地址

    if(!addlist.isEmpty())
    {
        for (int i=0;i<addlist.count();i++)
        {
            QHostAddress ahost=addlist.at(i);
            if(QAbstractSocket::IPv4Protocol==ahost.protocol())
            {
                localIp=ahost.toString();
                qDebug()<<localIp<<'\n';
                //break;
            }
        }
    }
    //localIp="192.168.43.46";
    return  localIp;
}


void MainWindow::Read_msg()                         //从socket中读出消息，根据消息类型进行不同的响应
{
    QTcpSocket *socket;

    for(int i=0;i<m_socketList.size();i++)          //轮询socket列表
    {

        if(m_socketList[i]->canReadLine())          //找到又消息到来的socket
        {

             socket = m_socketList[i];
             QString msg =socket->readAll();
             qDebug()<<"**";
             qDebug()<<msg;
             qDebug()<<"**";
             QString server=msg.left(3);
             qDebug()<<server;
             qDebug()<<"**";

             int command = this->Judge_command(server);
             switch (command)
             {
             case 0:
                 qDebug()<<"新用户";
                 this->New_client_come(socket);
                 break;

             case 1:
                 qDebug()<<"匹配聊天用户";
                 this->Match_client(socket);
                 break;

             case 2:
                 qDebug()<<"取消匹配";
                 this->Match_cancel(socket);
                 break;

             case 3:
                 qDebug()<<"这是to other命令";
                 this->Send_to_other(msg, socket);
                 break;

             case 4:
                 qDebug()<<"这是一个 to all命令";
                 this->Send_to_all(msg, socket);
                 break;

             case 5:
                 qDebug()<<"下线命令";
                 ui->plainTextEdit->appendPlainText(msg);
                 this->Offline(socket);
                 break;

             case 6:
                 qDebug()<<"离开聊天";
                 this->End_chat(socket);
                 break;

             default:
                 qDebug()<<"错误的命令";break;

             }
             qDebug()<<"*******************";
         }
    }

}

void MainWindow::New_client_come(QTcpSocket *skt)
{
    int tempId=m_clientsList.size();

    Clients tempClient(tempId, -1, skt);            //将新用户记录到用户信息表中
    m_clientsList<<tempClient;

    int j=0;
    for(;j<m_clientsList.size();j++)
    {
//        QString msg="上线！";
//        QString prefix = "["+QString::number(tempId)+"]:";
//        msg = prefix+msg;
//        QByteArray str = msg.toUtf8();
//        //str.append('\n');
//        m_clientsList[j].m_socket->write(str);      //向所有在线用户通知新用户

        QString msg=QString::number(m_clientsList.size()); //向该新用户发送在线人员信息
        QString prefix="000";
        msg = prefix+msg;
        QByteArray str = msg.toUtf8();
        str.append('\n');
        m_clientsList[j].m_socket->write(str);
        qDebug()<<"在线人数："<<m_clientsList.size()<<'\n';
    }

}

void MainWindow::Match_cancel(QTcpSocket *skt)
{
    int i=0;
    for(i=0; i<m_clientsForMatch.size(); i++)       //找到取消匹配的socket
    {
        if(m_clientsForMatch[i].m_socket==skt)
        {
            m_clientsForMatch.removeAt(i);          //从匹配池删除该用户

            qDebug()<<m_clientsForMatch.size()<<'\n';//发送取消成功提醒
            QString msg="002成功取消！";
            QByteArray str=msg.toUtf8();
            str.append('\n');
            skt->write(str);
            break;
        }
    }
}

void MainWindow::Match_client(QTcpSocket *skt)
{
    for(int i=0; i<m_clientsForMatch.size(); i++)
        if(m_clientsForMatch[i].m_socket==skt)
        {
            QString msg="007";
            QByteArray str=msg.toUtf8();
            str.append('\n');
            skt->write(str);
            return;
        }

    int i;
    for(i=0; i<m_clientsList.size(); i++)           //找到要进行匹配的socket
    {
        if(m_clientsList[i].m_socket==skt)
            break;
    }

    Clients tempClient(m_clientsList[i]);
    m_clientsForMatch<<tempClient;                  //加入匹配池

    if(m_clientsForMatch.size()<=1)                 //匹配池人数不足
    {
        QString msg="007";
        QByteArray str=msg.toUtf8();
        str.append('\n');
        skt->write(str);
    }
    else
        Match(skt);                                 //进行匹配
}

void MainWindow::Match(QTcpSocket *skt)             //在匹配池中进行匹配
{
    int i=0, M=-1;                                  //在匹配池中找到请求用户
    for(i; i<m_clientsForMatch.size()&&m_clientsForMatch[i].m_socket!=skt; i++);

    while(true)                                     //随机推推荐
    {
        M=qrand()%m_clientsForMatch.size();         //不能匹配到自己
        if(M>=0&&M!=i)
            break;
    }

    int j=0;                                        //在用户列表中找到请求用户
    for(j; j<m_clientsList.size()&&m_clientsList[j].m_id!=m_clientsForMatch[i].m_id; j++);
    m_clientsList[j].m_matchId=m_clientsForMatch[M].m_id;   //将请求用户的聊天对象设为匹配对象

    QString prefix = "001";                         //向请求对象发送匹配成功提醒
    QString msg=QString::number(m_clientsForMatch[M].m_id);
    msg = prefix+msg;
    QByteArray str = msg.toUtf8();
    str.append('\n');
    m_clientsList[j].m_socket->write(str);
    qDebug()<<msg<<'\n';

                                                    //在用户列表中找到匹配用户
    for(j=0; j<m_clientsList.size()&&m_clientsList[j].m_id!=m_clientsForMatch[M].m_id; j++);
    m_clientsList[j].m_matchId=m_clientsForMatch[i].m_id;   //将匹配用户的聊天对象设为请求对象

    prefix = "001";                                 //向匹配对象发送匹配成功消息
    msg=QString::number(m_clientsForMatch[i].m_id);
    msg = prefix+msg;
    str = msg.toUtf8();
    str.append('\n');
    m_clientsList[j].m_socket->write(str);

    m_clientsForMatch.removeAt(i);                  //将匹配了的用户从匹配池移除
    m_clientsForMatch.removeAt(M);
    qDebug()<<msg<<'\n';
}

void MainWindow::Send_to_all(QString msg,QTcpSocket *skt)   //群聊消息转发
{

    msg = msg.remove(0,3);                          //添加标头
    QString prefix = "004";
    QByteArray str = msg.toUtf8();

    qDebug()<<msg;

    int i=0;
    for(; i<m_clientsList.size(); i++)
        if(skt==m_clientsList[i].m_socket)
            break;

    for(int j=0;j<m_socketList.size();j++)          //向所有在线socket发送
    {
        if(skt!=m_socketList[j])
        {
            m_socketList[j]->write((prefix+"["+QString::number(m_clientsList[i].m_id,10)+"]："+msg).toUtf8());
        }

    }
    ui->plainTextEdit->appendPlainText(msg);

}

void MainWindow::Send_to_other(QString msg, QTcpSocket *skt)  //私聊消息转发
{
    msg = msg.remove(0,3);                           //处理标头
    qDebug()<<msg;

    int j=0;
    for(;j<m_clientsList.size();j++)                 //找到转发对象
    {
        if(skt==m_clientsList[j].m_socket&&m_clientsList[j].m_matchId>=0)
        {
            int temp=m_clientsList[j].m_matchId;
            int i=0;
            for(i=0; i<m_clientsList.size()&&m_clientsList[i].m_id!=temp; i++);

            QString prefix = "003["+QString::number(m_clientsList[j].m_id)+"]:";
            msg = prefix+msg;
            QByteArray str = msg.toUtf8();
            //str.append('\n');
            m_clientsList[i].m_socket->write(str);
            break;
        }
    }

    if(j==m_clientsList.size())                        //没有找到转发对象，提醒用户配对
    {
        QString prefix = "006\n";
        msg = prefix;
        QByteArray str = msg.toUtf8();
        str.append('\n');
        skt->write(str);
    }
}

void MainWindow::Offline(QTcpSocket *skt)
{
    for(int i=0; i<m_clientsList.size(); i++)
    {
        if(m_clientsList[i].m_socket==skt)              //发送下线提醒
        {
            if(m_clientsList[i].m_matchId>=0)
            {
                int temp=m_clientsList[i].m_matchId;
                int j=0;
                for(j; (j<m_clientsList.size())&&(m_clientsList[j].m_id!=temp); j++);

                QString prefix = "005";
                QString msg = prefix;
                QByteArray str = msg.toUtf8();
                str.append('\n');
                m_clientsList[j].m_socket->write(str);
                m_clientsList[j].m_matchId=-1;
                qDebug()<<str<<'\n';
            }

            m_clientsList.removeAt(i);                  //删除用户记录
            qDebug()<<m_clientsList.size()<<'\n'; 
        }
    }

    for(int i=0; i<m_socketList.size(); i++)            //移除下线的socket
    {
        if(m_socketList[i]==skt)
        {
            m_socketList.removeAt(i);
            break;
        }
    }

    for(int i=0; i<m_socketList.size(); i++)            //移除下线的socket
    {
        QString msg=QString::number(m_socketList.size()); //向该新用户发送在线人员信息
        QString prefix="000";
        msg = prefix+msg;
        QByteArray str = msg.toUtf8();
        str.append('\n');
        m_socketList[i]->write(str);
        qDebug()<<"在线人数："<<m_clientsList.size()<<'\n';
    }
}

void MainWindow::End_chat(QTcpSocket *skt)
{
    for(int i=0; i<m_clientsList.size(); i++)
    {
        if(m_clientsList[i].m_socket==skt)              //发送下线提醒
        {
            if(m_clientsList[i].m_matchId>=0)
            {
                int temp=m_clientsList[i].m_matchId;
                int j=0;
                for(j; j<m_clientsList.size()&&m_clientsList[j].m_id!=temp; j++);

                QString prefix = "005";
                QString msg = prefix;
                QByteArray str = msg.toUtf8();
                str.append('\n');
                m_clientsList[j].m_socket->write(str);
                m_clientsList[j].m_matchId=-1;
                qDebug()<<str<<'\n';
            }
            m_clientsList[i].m_matchId=-1;               //删除用户记录
            break;
        }
    }
}

int MainWindow::Judge_command(QString command)
{
    if(command=="000"){return 0;}
    if(command=="001"){return 1;}
    if(command=="002"){return 2;}
    if(command=="003"){return 3;}
    if(command=="004"){return 4;}
    if(command=="005"){return 5;}
    if(command=="006"){return 6;}
    return -1;
}
