#include "joystickhandler.h"

JoyStickHandler::JoyStickHandler()
{
    this->axisCount =6;
    this->axisVal = new int16_t[this->axisCount];
    this->buttonCount = 20;
    this->buttonVal = new buttonArry[this->buttonCount%8?(int)this->buttonCount+1 : (int)this->buttonCount];

    this->axisVal[0] = 0;
    this->buttonVal[0].bttns = 0xff;
    this->buttonVal[0].indvBttn.LEFT_THUMB =false;

#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
    XInputEnable(FALSE); //start with all controllers disabled

#elif __linux

#elif __APPLE__

#endif

}

JoyStickHandler::~JoyStickHandler()
{
}

#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
void JoyStickHandler::initJoystick(int index)
{

    DWORD error=XInputGetState(index,&this->controller);
    if(error!=1)
    {

    }
}

void JoyStickHandler::updateJoystick()
{

}

#elif __linux

#elif __APPLE__

#endif
