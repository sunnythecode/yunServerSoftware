#include "client.h"

Client::Client()
{
    this->connectedToHost = false;
    this->inSock = new QUdpSocket(this);
    if(!this->inSock->bind(450))
       D_MSG("Failed to bind");
    this->outSock = new QUdpSocket();
    connect(this->inSock,SIGNAL(readyRead()),this,SLOT(receivedPacket()));
    connect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    connect(this->inSock,SIGNAL(connected()),this,SLOT(successConnection()));

}
Client::~Client()
{
    disconnect(this->inSock, SIGNAL(readyRead()), this, SLOT(receivedPacket()));
    disconnect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    disconnect(this->inSock,SIGNAL(connected()),this,SLOT(successConnection()));
    this->inSock->close();
    delete this->inSock;
}

void Client::receivedPacket()
{
    while(this->inSock->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->inSock->pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        this->inSock->readDatagram(datagram.data(),datagram.size(),&sender,&port);
        QString messStr = QString::fromUtf8(datagram.data());
        QString sendStr = sender.toString();
        if(messStr.indexOf(sendStr)!=-1 && !this->connectedToHost)
        {
            emit connectRequest(sendStr);
        }
        else
        {
            emit formattedPacket(messStr);
        }
    }
}
void Client::connectToHost(QString addr)
{
    address = new QHostAddress(addr);
    this->outSock->connectToHost(*address,2367);
}
void Client::successConnection()
{
    qDebug() << "Connected to host";
    qDebug() << "Client info";
    qDebug() << "Peer " + this->inSock->peerAddress().toString();
    qDebug() << "Local port " + this->inSock->localPort();
    qDebug() << "Peer port " + this->inSock->peerPort();
    this->connectedToHost = true;
    QByteArray data = "name";
    this->inSock->writeDatagram(data,*address,2367);
}


bool Client::isConnected()
{
    return this->connectedToHost;
}
