#include "client.h"
#include <QTimer>

Client::Client()
{
    this->connectedToHost = false;
    this->inSock = new QUdpSocket();
    //this->inSock->setSocketOption(QAbstractSocket::UdpSocket);
    if (this->inSock->socketType() == QAbstractSocket::UdpSocket)
        qDebug() << "Udp Socket";
    else if (this->inSock->socketType() == QAbstractSocket::TcpSocket)
        qDebug() << "Tcp Socket";
    if (!this->inSock->bind())
        qDebug() << "Didn't bind successfully";
    qDebug() << this->inSock->localPort();
    this->outSock = new QUdpSocket();
    connect(this->inSock,SIGNAL(readyRead()),this,SLOT(receivedPacket()));
    connect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    connect(this, SIGNAL(updateGameData(QString)), this, SLOT(receivedGameData(QString)));
    QTimer::singleShot(8000, this, SLOT(receivedPacket()));
}
Client::~Client()
{
    disconnect(this->inSock, SIGNAL(readyRead()), this, SLOT(receivedPacket()));
    disconnect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    disconnect(this, SIGNAL(updateGameData(QString)), this, SLOT(receivedGameData(QString)));
    disconnect(this->inSock,SIGNAL(connected()),this,SLOT(successConnection()));
    this->inSock->close();
    delete this->inSock;
}

void Client::receivedPacket()
{
    qDebug() << "Received something";
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
            if (messStr.contains("gmd"))
                emit updateGameData(messStr);
            else
                emit formattedPacket(messStr);
        }
    }
}

void Client::receivedGameData(QString data) {

    qDebug() << "Following needs to be changed to data parameter";
    QString allGameData = "gmd:500#P1:NameORobot:1:2;P2:SecondName:0:1";

    // collects the game time
    QStringList gameSplits = allGameData.split("#");
    QString gameTime = gameSplits.at(0).split(":").at(1);
    qDebug() << gameTime;

    // collects the data for each player
    QStringList playerData = gameSplits.at(1).split(";");

    QString playerText;
    //playerText << "P" << this->currentPlayer;
    foreach (QString text, playerData) {
        if (text.contains(playerText)) {

        }
    }

    /*
    for (int i = 0; i < 6; i++) {
        if (i == 0)
            allGameData << "P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
        else
            allGameData << ";P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
            */
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
