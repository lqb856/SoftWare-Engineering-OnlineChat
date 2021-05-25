#ifndef CLIENTS_H
#define CLIENTS_H

#include<QTcpSocket>
class Clients
{
public:
    Clients();
    Clients(int id=-1, int matchId=-1, QTcpSocket * socket=NULL);
    Clients(const Clients &client);
public:
    int m_id;
    int m_matchId;
    QTcpSocket * m_socket;


};

#endif // CLIENTS_H
