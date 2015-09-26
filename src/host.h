#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>
#include <udpsend.h>
#include <gamedata.h>
#include <robotinfo.h>

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
typedef struct{
    QHostAddress addr;
    qint16 port;
    QString name;
}ConnectedRobot;
class Host : public UdpSend
{
    Q_OBJECT
public:
    Host();
    ~Host();
    QList<QString>getClientNames();
    QList<ConnectedClient> *getClients() const;
    void setClients(QList<ConnectedClient> *value);

    QList<ConnectedRobot> *getRobots() const;
    void setRobots(QList<ConnectedRobot> *value);

    RobotInfo *getMasterList() const;
    void setMasterList(RobotInfo *value);

public slots:
    void sendBroadcast();
    void sendGameSync(QByteArray dgram);
    void readData();
    bool checkValidDgram(QByteArray dgram,QHostAddress sender, quint16 senderPort);
    void parseDgram(QByteArray dgram);
    void sendRobotSync();
signals:
    void receivedValidDgram(QByteArray dgram);
    void newClient(QByteArray dgram);
    void clientAdded();
    void robotAdded();
private:
    GameData *gameData;
    QUdpSocket *broadCastSock;
    QUdpSocket *commSock;
    QHostAddress multiAddr;
    QList<ConnectedClient> *clients;
    QList<ConnectedRobot> *robots;
    RobotInfo *masterList;
};


#endif // BROADCAST_H
