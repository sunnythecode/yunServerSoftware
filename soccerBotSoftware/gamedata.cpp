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

    // colon symbol after gmd, pound symbol between game time and everything else, semicolons between individual player data
    QTextStream allGameData;
    allGameData << "gmd:" << this->gameTime << "#";
    for (int i = 0; i < 6; i++) {
        if (i == 0)
            allGameData << "P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
        else
            allGameData << ";P" << i + 1 << ":" << this->robotNames[i] << ":" << this->joystickConnections[i] << ":" << this->clientConnections[i];
    }
    this->gameSyncs++;

    this->udpSender->sendVals(allGameData.readAll());
}

float GameData::getGameTime() {
    return this->gameTime;
}
int GameData::getGameSyncs() {
    return this->gameSyncs;
}
