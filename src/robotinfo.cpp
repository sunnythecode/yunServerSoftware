#include "robotinfo.h"

RobotInfo::RobotInfo()
{

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
