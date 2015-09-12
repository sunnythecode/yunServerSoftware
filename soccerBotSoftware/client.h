#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

#define DEBUG /* comment out this line to lower the verbosity of the program */


#if  defined(DEBUG) || defined(GLOBAL_DEBUG)
#define D_MSG(a) printf(a);
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
    QHostAddress *address;
public slots:
    void receivedPacket();
    void connectToHost(QString addr);
    void successConnection();
signals:
    void connectRequest(QString);
    void formattedPacket(QString);

};

#endif // CLIENT_H
