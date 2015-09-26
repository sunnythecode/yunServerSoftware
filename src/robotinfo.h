#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include <QTime>
#include<stdint.h>
typedef union
{
  struct
  {
    bool DPAD_UP        : 1;
    bool DPAD_DOWN      : 1;
    bool DPAD_LEFT      : 1;
    bool DPAD_RIGHT     : 1;
    bool START          : 1;
    bool BACK           : 1;
    bool LEFT_THUMB     : 1;
    bool RIGHT_THUMB    : 1;
    bool LEFT_SHOULDER  : 1;
    bool RIGHT_SHOULDER : 1;
    bool A              : 1;
    bool B              : 1;
    bool X              : 1;
    bool Y              : 1;
  }indvBttn;
  struct
  {
      uint8_t lByte;
      uint8_t hByte;
  }byte;
  uint16_t bttns;

}buttonArry;

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
