#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include <udpsend.h>

class GameData : public QObject
{
    Q_OBJECT

public:
    explicit GameData();
    ~GameData();

    QTimer gameDataTimer;

    float getGameTime();
    int  getGameSyncs();
    void setGameTime(float time);
    void setGameSyncs(int syncs);

    void startGameUpdates();
    void endGameUpdates();
public slots:
    void updateGameData();

private:
   float gameTime;
   int gameSyncs;
   QString robotNames[6];
   bool joystickConnections[6];
   char clientConnections[6];
   int robotConnections[6];

   QUdpSocket *socket;
   UdpSend *udpSender;
};

#endif // GAMEDATA_H
