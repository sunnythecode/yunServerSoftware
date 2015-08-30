#include "gamedata.h"

GameData::GameData()
{
    connect(&this->gameDataTimer,  SIGNAL(timeout()), this, SLOT(updateGameData()));
}
GameData::~GameData()
{

}

void GameData::startUpdatingGame() {
    gameDataTimer.start();
}

int GameData::getGameTime() {
    return this->gameTime;
}
int GameData::getGameSyncs() {
    return this->gameSyncs;
}
void GameData::setGameTime(int time) {
    this->gameTime = time;
}
void GameData::setGameSyncs(int syncs) {
    this->gameSyncs = syncs;
}
