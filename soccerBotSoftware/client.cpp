#include "client.h"

Client::Client()
{
    this->sock = new QUdpSocket();
    this->sock->bind(400);
    connect(this->sock,SIGNAL(readyRead()),this,SLOT(receivedPacket()));
    connect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    connect(this->sock,SIGNAL(connected()),this,SLOT(successConnection()));

}
Client::~Client()
{
    disconnect(this->sock, SIGNAL(readyRead()), this, SLOT(receivedPacket()));
    disconnect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    connect(this->sock,SIGNAL(connected()),this,SLOT(successConnection()));
    this->sock->close();
    delete this->sock;
}

void Client::receivedPacket()
{
    while(this->sock->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->sock->pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        this->sock->readDatagram(datagram.data(),datagram.size(),&sender,&port);
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
    this->sock->connectToHost(*address,2367);
}
void Client::successConnection()
{
    qDebug() << "Connected to host";
    qDebug() << "Client info";
    qDebug() << "Peer " + this->sock->peerAddress().toString();
    qDebug() << "Local port " + this->sock->localPort();
    qDebug() << "Peer port " + this->sock->peerPort();
    this->connectedToHost = true;
    QByteArray data = "name";
    this->sock->writeDatagram(data,*address,2367);
}
