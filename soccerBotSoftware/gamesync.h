#ifndef GAMESYNC_H
#define GAMESYNC_H


class GameSync
{
public:
    GameSync();
    QTimer startUpdating;
public slots:
    void updateGameInfo();
};

#endif // GAMESYNC_H
