#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>

class Broadcast : public QObject
{
    Q_OBJECT
public:
    Broadcast();
    ~Broadcast();
public slots:
    void sendBroadcast();
private:
    QUdpSocket *sock;
};

#endif // BROADCAST_H
