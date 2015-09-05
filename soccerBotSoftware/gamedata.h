#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <QObject>
#include <QTimer>
#include <QtNetwork>

class GameData : public QObject
{
    Q_OBJECT

public:
    explicit GameData();
    ~GameData();

    QTimer gameDataTimer;

    int getGameTime();
    int  getGameSyncs();
    void setGameTime(int time);
    void setGameSyncs(int syncs);

    void startUpdatingGame();
public slots:
    //void updateGameData();

private:
   int gameTime;
   int gameSyncs;

};

#endif // GAMEDATA_H
