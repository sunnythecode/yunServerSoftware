#include "robotinfo.h"

RobotInfo::RobotInfo()
{
    for(int i =0;i<6;i++)
    {
        this->joystickData.buttons.bttns=0;
        this->joystickData.lX=0;
        this->joystickData.lY=1;
        this->joystickData.rX=2;
        this->joystickData.rY=3;
        this->joystickData.lT=4;
        this->joystickData.rT=5;
    }
}
void RobotInfo::updateVal(QString name, JoystickData data)
{
    this->name=name;
    this->joystickData=data;
    this->lastUpdate=QTime::currentTime();
}


QString RobotInfo::getName()
{
    return this->name;
}

QTime RobotInfo::getUpdate()
{
    return this->lastUpdate;
}
JoystickData RobotInfo::getJoystickData()
{
    return this->joystickData;
}
