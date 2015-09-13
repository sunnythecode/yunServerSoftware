#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

#define DEBUG /* comment out this line to lower the verbosity of the program */
#define MULTICAST_PORT 25001
#define HOST_LISTEN_PORT 25006

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
