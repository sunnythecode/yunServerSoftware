#include "client.h"

Client::Client()
{
    this->connectedToHost = false;
    this->inSock = new QUdpSocket(this);
    this->broadSock = new QUdpSocket(this);
    if(!this->inSock->bind(QHostAddress::AnyIPv4, MULTICAST_PORT))
       D_MSG("Failed to bind multicast port");
    if(!this->broadSock->bind(BROADCAST_LISTEN))
       D_MSG("Failed to bind broadcast port");
    this->outSock = new QUdpSocket();
    connect(this->broadSock,SIGNAL(readyRead()),this,SLOT(receivedPacket()));
    connect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));

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
    D_MSG("Received packet");
    while(this->broadSock->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->broadSock->pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        this->broadSock->readDatagram(datagram.data(),datagram.size(),&sender,&port);
        QString messStr = QString::fromUtf8(datagram.data());
        QString sendStr = sender.toString();
        D_MSG(messStr);
        D_MSG(sendStr);
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
    QString firstByte = addr.section(".",0,0);
    QString secondByte = addr.section(".",1,1);
    QString thirdByte = addr.section(".",2,2);
    int byte = thirdByte.toInt();
    byte++;
    thirdByte = QString::number(byte);
    QString fourthByte = addr.section(".",3,3);
    multiAddr = new QHostAddress(firstByte+"."+secondByte+"."+thirdByte+"."+fourthByte);
    hostAddr = new QHostAddress(addr);
    if(!this->inSock->joinMulticastGroup(*multiAddr))
    {
        D_MSG("Failed to join multicast group at");
        D_MSG(this->inSock->errorString());
        D_MSG(multiAddr->toString());
    }
    if(!this->outSock->bind(HOST_LISTEN_PORT))
    {
        D_MSG("Failed to bind to host port");
    }

    QByteArray data = "CLI:name";
    if(this->outSock->writeDatagram(data,*this->hostAddr,HOST_LISTEN_PORT)==-1)
    {
        D_MSG("Failed to send datagram");
    }

}
void Client::successConnection()
{
    qDebug() << "Connected to host";
    qDebug() << "Client info";
    qDebug() << "Peer " + this->inSock->peerAddress().toString();
    qDebug() << "Local port " + this->inSock->localPort();
    qDebug() << "Peer port " + this->inSock->peerPort();
}


bool Client::isConnected()
{
    return this->connectedToHost;
}
