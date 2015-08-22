#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

class Host : public UdpSend
{
    Q_OBJECT
public:
    Host();
    ~Host();
public slots:
    void sendBroadcast();
private:
    QUdpSocket *sock;
};

#endif // BROADCAST_H
