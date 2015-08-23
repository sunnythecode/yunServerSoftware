#include "host.h"

Host::Host()
{
    this->sock = new QUdpSocket();
    this->sock->bind(2367);
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
    sock->writeDatagram(datagram,QHostAddress::Broadcast,400);
}
