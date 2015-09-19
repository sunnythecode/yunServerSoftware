#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

#define DEBUG /* comment out this line to lower the verbosity of the program */
#define MULTICAST_PORT 2367
#define HOST_LISTEN_PORT 2380
#define BROADCAST_LISTEN 23005

#if  defined(DEBUG) || defined(GLOBAL_DEBUG)
#define D_MSG(a) qDebug()<<a;
#else
#define D_MSG(a)
#endif

class Client : public UdpSend
{
    Q_OBJECT
public:
    Client();
    ~Client();
    bool isConnected();
private:
    QUdpSocket *inSock;
    QUdpSocket *outSock;
    QUdpSocket *broadSock;
    bool connectedToHost;
    QHostAddress *hostAddr;
    QHostAddress *multiAddr;
public slots:
    void receivedPacket();
    void connectToHost(QString addr);
    void successConnection();
signals:
    void connectRequest(QString);
    void formattedPacket(QString);

};

#endif // CLIENT_H
