#include "joystickhandler.h"

joyStickHandler::joyStickHandler()
{
    this->axisCount =6;
    this->axisVal = new int16_t[this->axisCount];
    this->buttonCount = 20;
    this->buttonVal = new buttonArry[this->buttonCount%8?(int)this->buttonCount+1 : (int)this->buttonCount];

    this->axisVal[0] = 0;
    this->buttonVal[0].bttns = 0xff;
    this->buttonVal[0].indvBttn.bttn4 =false;
}

joyStickHandler::~joyStickHandler()
{
}
