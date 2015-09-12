#ifndef GAMESYNC_H
#define GAMESYNC_H
#include<QTimer>
#include<QObject>

#include<QTimer>
class GameSync : public QObject
{
    Q_OBJECT
public:
    GameSync();
    QTimer startUpdating;
public slots:
    void updateGameData();
};

#endif // GAMESYNC_H
