#ifndef GAMESYNC_H
#define GAMESYNC_H
#include<QTimer>
#include<QObject>

<<<<<<< HEAD
class GameSync : public QObject
{
    Q_OBJECT

=======
#include<QTimer>
class GameSync : public QObject
{
    Q_OBJECT
>>>>>>> master
public:
    GameSync();
    QTimer startUpdating;
public slots:
    void updateGameData();
};

#endif // GAMESYNC_H
