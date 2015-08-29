#ifndef GAMESYNC_H
#define GAMESYNC_H

#include<QTimer>
class GameSync : public QObject
{
    Q_OBJECT
public:
    GameSync();
    QTimer startUpdating;
public slots:
    void updateGameInfo();
};

#endif // GAMESYNC_H
