#ifndef PNEUMATIC_H
#define PNEUMATIC_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>
#include <joystickscissor.h>
#include <PID.h>
#include <Solenoid.h>


class Pneumatic {
	public:
		Pneumatic( Solenoid *solenoid_1, Solenoid *solenoid_2,
			   Joystick* joy)
			: solenoid_1(solenoid_1), solenoid_2(solenoid_2), joy(joy) {};

		bool buttonstate_Left = false;
        bool Left_Button = false;
        bool Turning_Left_Button_On = false;
        bool Toggle_On_Variable_Left = false;
        bool Turning_Left_Button_Off = false;
        bool Toggle_Off_Variable_Left = false;
		void run_pneumatics();
	private:
		Solenoid *solenoid_1;
		Solenoid *solenoid_2;
		Joystick *joy;
};
#endif