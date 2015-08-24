#include "joystickhandler.h"

JoyStickHandler::JoyStickHandler()
{
#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
    XInputEnable(TRUE); //make sure xinput is enabled
#elif __linux

#elif __APPLE__

#endif

    this->joy_dx_index = JOYSTICK_NOT_CONNECTED;
    this->axisCount =6;
    this->axisVal = new int16_t[this->axisCount];
    this->buttonCount = 14;
    this->buttonVal = new buttonArry;

    for(int i = 0; i < this->axisCount; i++)
    {
        this->axisVal[i] = 0;
    }
    this->buttonVal->bttns = 0;
}

JoyStickHandler::~JoyStickHandler()
{
}

#if defined(__WIN32) || defined(__WIN64) || defined(__WINNT)
void JoyStickHandler::initJoystick(int index)
{
    if(XInputGetState(index,&this->controller) != ERROR_DEVICE_NOT_CONNECTED)
    {
        this->joy_dx_index = index;
    }
    else
    {
        emit joystickMissing(index);
        this->joy_dx_index = JOYSTICK_NOT_CONNECTED;    
    }
}

void JoyStickHandler::updateJoystick()
{
    if(this->joy_dx_index != JOYSTICK_NOT_CONNECTED)
    {
        if(XInputGetState(this->joy_dx_index, &this->controller) != ERROR_DEVICE_NOT_CONNECTED)
        {
            this->axisVal[0] = this->controller.Gamepad.sThumbLX;
            this->axisVal[1] = this->controller.Gamepad.sThumbLY;
            this->axisVal[2] = this->controller.Gamepad.sThumbRX;
            this->axisVal[3] = this->controller.Gamepad.sThumbRY;
            this->axisVal[4] = this->controller.Gamepad.bLeftTrigger <<7;   /*The left and right triggers are scaled up from 8 bit to ~16 bit*/
            this->axisVal[5] = this->controller.Gamepad.bRightTrigger << 7; /*The left and right triggers are scaled up from 8 bit to ~16 bit*/
            this->buttonVal[0].bttns = this->controller.Gamepad.wButtons;
        }
        else
        {
            emit joystickMissing(this->joy_dx_index);
            this->joy_dx_index = JOYSTICK_NOT_CONNECTED;
        }
    }
}

void JoyStickHandler::rumbleJoystick(unsigned int lMtr, unsigned int rMtr)
{
    if(this->joy_dx_index != JOYSTICK_NOT_CONNECTED)
    {
        XINPUT_VIBRATION val;
        val.wLeftMotorSpeed = lMtr;
        val.wRightMotorSpeed = rMtr;

        if(XInputSetState(this->joy_dx_index, &val) == ERROR_DEVICE_NOT_CONNECTED)
        {
            emit joystickMissing();
        }
    }
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
void JoyStickHandler::rumbleJoystick(unsigned int lMtr, unsigned int rMtr)
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
void JoyStickHandler::rumbleJoystick(unsigned int lMtr, unsigned int rMtr)
{

}
#endif
