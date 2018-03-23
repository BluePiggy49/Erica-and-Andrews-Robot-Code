#ifndef VALUE_CONTROL_H
#define VALUE_CONTROL_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>


namespace ValueControl
{ 
	
	double constrain(double val,double lower,double upper);
	float exponent_mirrored(float val, int expo);
	
};
#endif
