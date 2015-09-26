#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include <QTime>
#include<stdint.h>
#include<joystickhandler.h>
typedef struct
{
 qint16 lX;
 qint16 lY;
 qint16 rX;
 qint16 rY;
 qint16 lT;
 qint16 rT;
 buttonArry buttons;
}JoystickData;
class RobotInfo
{
public:
    RobotInfo();
    void updateVal(int index, QString name, JoystickData data);
    QString* getNames();
    QTime* getUpdates();
    JoystickData* getJoys();
private:
    QTime updates[6];
    JoystickData joys[6];
    QString names[6];
};

#endif // ROBOTINFO_H
