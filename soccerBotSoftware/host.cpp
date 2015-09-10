#include "host.h"

Host::Host()
{
    this->sock = new QUdpSocket();
    this->sock->bind(HOST_LISTENING_PORT);
    connect(this->sock, SIGNAL(readyRead()), this, SLOT(readData()));
}
Host::~Host()
{
    this->sock->close();
    delete this->sock;
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
    sock->writeDatagram(datagram,QHostAddress::Broadcast,BROADCAST_PORT);
}
void Host::sendGameSync()
{

}

void Host::readData()
{
    QByteArray datagram;
    datagram.resize(this->sock->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    this->sock->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    D_MSG(datagram.data());
}
