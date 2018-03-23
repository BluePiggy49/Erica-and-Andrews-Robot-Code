#ifndef INTAKE_H
#define INTAKE_H
#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
class Intake
{
public:
	Intake(TalonSRX *intake_talon_left, TalonSRX *intake_talon_right, Joystick *joy) : intake_talon_right(intake_talon_right), intake_talon_left(intake_talon_left), joy(joy) {
		};
	bool Getting_Right_Button;
	bool Getting_Left_Button;
	void Start_Intake(float intake_speed_in, float intake_speed_out);
	
private:
	TalonSRX *intake_talon_left, *intake_talon_right;
	Joystick *joy;
};

#endif
