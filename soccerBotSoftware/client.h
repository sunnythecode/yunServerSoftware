#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
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
