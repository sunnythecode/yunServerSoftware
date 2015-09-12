#include "client.h"

Client::Client()
{
    this->connectedToHost = false;
    this->sock = new QUdpSocket();
    this->sock->bind(400);
    connect(this->sock,SIGNAL(readyRead()),this,SLOT(receivedPacket()));
    connect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    connect(this->sock,SIGNAL(connected()),this,SLOT(successConnection()));
    connect(this, SIGNAL(updateGameData(QString)), this, SLOT(receivedGameData(QString)));
}
Client::~Client()
{
    disconnect(this->sock, SIGNAL(readyRead()), this, SLOT(receivedPacket()));
    disconnect(this,SIGNAL(connectRequest(QString)),this,SLOT(connectToHost(QString)));
    disconnect(this, SIGNAL(updateGameData(QString)), this, SLOT(receivedGameData()));
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
            if (messStr.contains("gmd"))
                emit updateGameData(messStr);
            else
                emit formattedPacket(messStr);
        }
    }
}
/*
// colon symbol after gmd, pound symbol between game time and everything else, semicolons between individual player data
QTextStream allGameData;
allGameData << "gmd:" << this->gameTime << "#";
for (int i = 0; i < 6; i++) {
    if (i == 0)
        allGameData << "P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
    else
        allGameData << ";P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
}*/
void Client::receivedGameData(QString data) {

    QString allGameData = "gmd:500#P1:NameORobot:1:2;P2:SecondName:0:1";

    // collects the game time
    QStringList gameSplits = allGameData.split("#");
    QString gameTime = gameSplits.at(0).split(":").at(1);
    qDebug() << gameTime;

    // collects the data for each player
    QStringList playerData = gameSplits.at(1).split(";");

    QString playerText;
    foreach (QString text, playerData) {
        if (text.contains(playerText)) {

        }
    }
        //qDebug() << text;
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


bool Client::isConnected()
{
    return this->connectedToHost;
}
