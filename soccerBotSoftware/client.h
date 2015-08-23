#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

class Client : public UdpSend
{
    Q_OBJECT
public:
    Client();
    ~Client();

    bool isConnected();
private:
    QUdpSocket *sock;
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
