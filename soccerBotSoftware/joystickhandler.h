#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include<stdint.h>

#define JOYSTICK_NOT_CONNECTED -10

#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
#include <xinput.h>
#elif __linux
#elif __APPLE__
#endif

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
      uint8_t uByte;
      uint8_t lByte;
  }byte;
  uint16_t bttns;

}buttonArry;

class JoyStickHandler
{
private:
   int axisCount;
   int16_t *axisVal;
   int buttonCount;
   buttonArry *buttonVal;

    #if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
        int joy_dx_index;
        XINPUT_STATE controller;
    #elif __linux

    #elif __APPLE__

    #endif

public:
    JoyStickHandler();
    ~JoyStickHandler();
    bool readBttn(int index);
    int16_t readAxis(int index);
    void initJoystick(int index);
    void updateJoystick();
    void rumbleJoystick(unsigned int lMtr, unsigned int rMtr);
};

#endif // JOYSTICKHANDLER_H


