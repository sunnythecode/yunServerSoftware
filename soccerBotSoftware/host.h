#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>
#include <udpsend.h>
#include <gamedata.h>
#include <gamesync.h>

#define BROADCAST_PORT 472
#define HOST_LISTENING_PORT 2380
#define MULTI_CAST_PORT 2367

#define DEBUG /* comment out this line to lower the verbosity of the program */


#if  defined(DEBUG) || defined(GLOBAL_DEBUG)
#define D_MSG(a) qDebug()<<a
#else
#define D_MSG(a)
#endif


class Host : public UdpSend
{
    Q_OBJECT
public:
    Host();
    ~Host();
public slots:
    void sendBroadcast();
    void sendGameSync(QByteArray dgram);
    void readData();
    bool checkValidDgram(QByteArray dgram);
signals:
    void receivedValidDgram(QByteArray dgram);
private:
<<<<<<< HEAD
    QUdpSocket *sock;
    GameData *gameData;
    GameSync *gameSync;
=======
    QUdpSocket *broadCastSock;
    QUdpSocket *commSock;
    QHostAddress multiAddr;
>>>>>>> master
};

#endif // BROADCAST_H
