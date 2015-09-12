#include "host.h"

Host::Host()
{
    this->broadCastSock = new QUdpSocket();;
    this->commSock = new  QUdpSocket();

    this->commSock->bind(HOST_LISTENING_PORT); 
    this->broadCastSock->bind(BROADCAST_PORT);
    multiAddr = this->broadCastSock->localAddress();
    QString temp = multiAddr.toString();
    QString firstByte = temp.section(".",0,0);
    QString secondByte = temp.section(".",1,1);
    QString thirdByte = temp.section(".",2,2);
    int byte = thirdByte.toInt();
    byte++;
    thirdByte = QString::number(byte);
    QString fourthByte = temp.section(".",3,3);
    multiAddr.setAddress(firstByte+"."+secondByte+"."+thirdByte+"."+fourthByte);
    connect(this->commSock, SIGNAL(readyRead()), this, SLOT(readData()));
}
Host::~Host()
{
    this->broadCastSock->close();
    this->commSock->close();
    delete this->commSock;
    delete this->broadCastSock;
}
void Host::sendBroadcast()
{
    QByteArray datagram;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
             datagram.append(address.toString());
             D_MSG(address.toString());
        }
    }
    this->broadCastSock->writeDatagram(datagram, QHostAddress::Broadcast, BROADCAST_PORT);
}

void Host::sendGameSync(QByteArray dgram)
{
    this->commSock->writeDatagram(dgram,this->multiAddr,MULTI_CAST_PORT);
}

void Host::readData()
{
    QByteArray datagram;
    datagram.resize(this->commSock->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    this->commSock->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    D_MSG(datagram.data());
    this->checkValidDgram(datagram);
}
bool Host::checkValidDgram(QByteArray dgram)
{
    if(dgram.startsWith("gmd"))
    {
        emit receivedValidDgram(dgram);
        return true;
    }
    else
        return false;
}
