#include "joystickhandler.h"

JoyStickHandler::JoyStickHandler()
{
#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
    XInputEnable(FALSE); //start with all controllers disabled

#elif __linux

#elif __APPLE__

#endif

    this->joy_dx_index = JOYSTICK_NOT_CONNECTED;
    this->axisCount =6;
    this->axisVal = new int16_t[this->axisCount];
    this->buttonCount = 14;
    this->buttonVal = new buttonArry;
}

JoyStickHandler::~JoyStickHandler()
{
}





#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
void JoyStickHandler::initJoystick(int index)
{
    if(XInputGetState(index,&this->controller) !=  0)
    {
        this->joy_dx_index = index;
    }
    else
    {
        this->joy_dx_index = JOYSTICK_NOT_CONNECTED;
    }
}

void JoyStickHandler::updateJoystick()
{
    if(this->joy_dx_index != JOYSTICK_NOT_CONNECTED)
    {
        XInputGetState(this->joy_dx_index, this->controller);
        this->axisVal[0] = this->controller.Gamepad.sThumbLX;
        this->axisVal[1] = this->controller.Gamepad.sThumbLY;
        this->axisVal[2] = this->controller.Gamepad.sThumbRX;
        this->axisVal[3] = this->controller.Gamepad.sThumbRY;
        this->axisVal[4] = this->controller.Gamepad.bLeftTrigger <<7;   /*The left and right triggers are scaled up from 8 bit to ~16 bit*/
        this->axisVal[5] = this->controller.Gamepad.bRightTrigger << 7; /*The left and right triggers are scaled up from 8 bit to ~16 bit*/
        this->buttonVal[0] = this->controller.Gamepad.wButtons;
    }
}

void JoyStickHandler::rumbleJoystick(unsigned int lMtr, unsigned int rMtr)
{
    XINPUT_VIBRATION val;
    val.wLeftMotorSpeed = lMtr;
    val.wRightMotorSpeed = rMtr;

    XInputSetState(this->joy_dx_index, &val);
}

#elif __linux
void JoyStickHandler::initJoystick(int index)
{

}

void JoyStickHandler::updateJoystick()
{

}

void JoyStickHandler::rumbleJoystick(int lMtr, int rMtr)
{

}
#elif __APPLE__
void JoyStickHandler::initJoystick(int index)
{

}

void JoyStickHandler::updateJoystick()
{

}

void JoyStickHandler::rumbleJoystick(int lMtr, int rMtr)
{

}
#endif
