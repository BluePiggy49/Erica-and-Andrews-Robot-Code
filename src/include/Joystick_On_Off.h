#ifndef JOYSTICK_ON_OFF_H
#define JOYSTICK_ON_OFF_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <constants.h>
#include <scissor.h>

class JoystickOnOff
{
public:
	JoystickOnOff(Joystick *joystick) : joystick(joystick){
	};
	enum JoystickEnum
	{
		toggle_on;
		toggle_off;
	}Joystick_Mode;

private:
		
};

#endif
