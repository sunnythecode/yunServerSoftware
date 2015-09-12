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

    bool joystickConnected;
    int currentPlayer;
public slots:
    void receivedPacket();
    void connectToHost(QString addr);
    void successConnection();
    void receivedGameData(QString data);
signals:
    void connectRequest(QString);
    void formattedPacket(QString);
    void updateGameData(QString);
};

#endif // CLIENT_H
