#include "gamedata.h"

GameData::GameData()
{
    this->gameSyncs = 0;
    this->gameTime = 0;
    this->gameDataTimer.setInterval(100);
    connect(&this->gameDataTimer,  SIGNAL(timeout()), this, SLOT(updateGameData()));
}
GameData::~GameData()
{

}

void GameData::startGameUpdates() {
    gameDataTimer.start();
}
void GameData::endGameUpdates() {
    gameDataTimer.stop();
}
void GameData::updateGameData() {
    this->gameTime += 0.1;

    QString allGameData;
    for (int i = 0; i < 6; i++) {
        QString playerData = QString("P%i:%s:%c:%c").arg(i + 1).arg(this->robotNames[i]).arg(this->joystickConnections[i]).arg(this->clientConnections[i]);
        if (i == 0)
            allGameData = QString("%s").arg(playerData);
        else
            allGameData = QString("%s;%s").arg(allGameData).arg(playerData);
    }
    this->gameSyncs++;

    this->udpSender->sendVals(allGameData);
    this->udpSender->sendVals(QString("%f").arg(this->gameTime));
}

float GameData::getGameTime() {
    return this->gameTime;
}
int GameData::getGameSyncs() {
    return this->gameSyncs;
}
void GameData::setGameTime(float time) {
    this->gameTime = time;
}
void GameData::setGameSyncs(int syncs) {
    this->gameSyncs = syncs;
}
