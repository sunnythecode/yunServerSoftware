#include "host.h"

Host::Host()
{
    this->broadCastSock = new QUdpSocket();;
    this->commSock = new  QUdpSocket();
    this->clients = new QList<ConnectedClient>;
    this->commSock->bind(HOST_LISTENING_PORT); 
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
    this->broadCastSock->writeDatagram(datagram,QHostAddress::Broadcast,BROADCAST_PORT);
}
void Host::sendGameSync(QByteArray dgram)
{
    //need to sending to each client
    //this->commSock->writeDatagram(dgram,this->multiAddr,MULTI_CAST_PORT);
}

void Host::readData()
{
    QByteArray datagram;
    datagram.resize(this->commSock->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    this->commSock->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    D_MSG(datagram.data());
    this->checkValidDgram(datagram,sender,senderPort);
}
bool Host::checkValidDgram(QByteArray dgram, QHostAddress sender, quint16 senderPort)
{
    if(dgram.startsWith("GMD"))
    {
        emit receivedValidDgram(dgram);
        return true;
    }
    if(dgram.startsWith("CLI"))
    {
        ConnectedClient cli;
        cli.addr = sender;
        cli.port = senderPort;
        QString name = QString::fromUtf8(dgram.data());
        cli.name = name.section(':',1);
        clients->append(cli);
        QByteArray dgram = "CLI:connected";
        this->broadCastSock->writeDatagram(dgram,sender,BROADCAST_PORT);
        return true;
    }
    else
        return false;
}
