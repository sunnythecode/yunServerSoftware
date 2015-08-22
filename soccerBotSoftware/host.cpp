#include "host.h"

Host::Host()
{
    sock = new QUdpSocket();
    sock->bind(2367);
}
Host::~Host()
{

}
void Host::sendBroadcast()
{
    QByteArray datagram;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
             datagram.append(address.toString());
             //qDebug() << address.toString();
        }

    }
    sock->writeDatagram(datagram,QHostAddress::Broadcast,400);

}
