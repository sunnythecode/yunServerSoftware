#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include<stdint.h>

#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
#include <xinput.h>
//#include <windowsJoystick.h>
#elif __linux
#include <linuxJoystick.h>
#elif __APPLE__
#include <osxJoystick.h>
#endif

typedef union
{
  struct
  {
    bool bttn1 : 1;
    bool bttn2 : 1;
    bool bttn3 : 1;
    bool bttn4 : 1;
    bool bttn5 : 1;
    bool bttn6 : 1;
    bool bttn7 : 1;
    bool bttn8 : 1;
  }indvBttn;
  unsigned char bttns;
}buttonArry;

class joyStickHandler
{
private:
   int axisCount;
   int16_t *axisVal;
   int buttonCount;
   buttonArry *buttonVal;

public:
    joyStickHandler();
    ~joyStickHandler();
};

#endif // JOYSTICKHANDLER_H
