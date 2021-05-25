#include "clients.h"

Clients::Clients()
{
    m_id=-1;
    m_matchId=-1;
    m_socket=NULL;
}

Clients::Clients(int id, int matchId, QTcpSocket * socket)
{
    this->m_id=id;
    this->m_matchId=matchId;
    this->m_socket=socket;
}

Clients::Clients(const Clients &client)
{
    this->m_id=client.m_id;
    this->m_matchId=client.m_matchId;
    this->m_socket=client.m_socket;
}
