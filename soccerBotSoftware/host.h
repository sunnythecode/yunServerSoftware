#ifndef BROADCAST_H
#define BROADCAST_H

#include <QObject>
#include <QtNetwork>
#include <udpsend.h>

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
private:
    QUdpSocket *sock;
};

#endif // BROADCAST_H
