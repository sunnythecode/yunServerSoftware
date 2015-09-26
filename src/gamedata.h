#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include <udpsend.h>

typedef union {
    unsigned char data[200];
    struct {
        char signature[3];
        char delimiter;
        unsigned char gameTime;
    } comps;
} allGameData;

class GameData : public QObject
{
    Q_OBJECT

public:
    explicit GameData();
    ~GameData();

    QTimer gameDataTimer;

    float getGameTime();
    int  getGameSyncs();

    void startGameUpdates();
    void endGameUpdates();
public slots:
    void updateGameData();

private:
   float gameTime;
   int gameSyncs;
   QString robotNames[6];
   bool joystickConnections[6];
   bool robotConnections[6];

   QUdpSocket *socket;
   UdpSend *udpSender;
};

#endif // GAMEDATA_H
