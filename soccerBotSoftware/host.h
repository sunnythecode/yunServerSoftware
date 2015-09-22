#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>
#include <udpsend.h>
#include <gamedata.h>
//#include <gamesync.h>

#define BROADCAST_PORT 23005
#define HOST_LISTENING_PORT 2380

#define DEBUG /* comment out this line to lower the verbosity of the program */


#if  defined(DEBUG) || defined(GLOBAL_DEBUG)
#define D_MSG(a) qDebug()<<a
#else
#define D_MSG(a)
#endif

typedef struct{
    QHostAddress addr;
    qint16 port;
    QString name;
}ConnectedClient;

class Host : public UdpSend
{
    Q_OBJECT
public:
    Host();
    ~Host();
    QList<QString>getClientNames();
public slots:
    void sendBroadcast();
    void sendGameSync(QByteArray dgram);
    void readData();
    bool checkValidDgram(QByteArray dgram,QHostAddress sender, quint16 senderPort);
signals:
    void receivedValidDgram(QByteArray dgram);
    void newClient(QByteArray dgram);
    void clientAdded();
private:
    GameData *gameData;
    QUdpSocket *broadCastSock;
    QUdpSocket *commSock;
    QHostAddress multiAddr;
    QList<ConnectedClient> *clients;
};


#endif // BROADCAST_H
