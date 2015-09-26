#include "robotinfo.h"

RobotInfo::RobotInfo()
{
    for(int i =0;i<6;i++)
    {
        this->joys[i].buttons.bttns=0;
        this->joys[i].lX=0;
        this->joys[i].lY=1;
        this->joys[i].rX=2;
        this->joys[i].rY=3;
    }
}
void RobotInfo::updateVal(int index, QString name, JoystickData data)
{
    this->names[index]=name;
    this->joys[index]=data;
    this->updates[index]=QTime::currentTime();
}
QString* RobotInfo::getNames()
{
    return this->names;
}

QTime* RobotInfo::getUpdates()
{
    return this->updates;
}
JoystickData* RobotInfo::getJoys()
{
    return this->joys;
}
