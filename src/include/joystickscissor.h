/*#ifndef SCISSOR_JOY_H
#define SCISSOR_JOY_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>

class JoystickScissorLift
{
public:
	JoystickScissorLift(Joystick *joy, ScissorLift *scissorlift) : joy(joy), scissorlift(scissorlift) {
		};
		void run_scissorjoystick();
			double scissorlift_down, scissorlift_up;				
			//misc variables
				int scissorlift_position_mode;
				bool scissorlift_downLast=true;
				bool scissorlift_upLast=true;
				bool wasAtScale=false;
				
				bool AoffLast=true;
				bool intake_in=false;

private:
	ScissorLift *scissorlift;
	Joystick *joy;

		
};

#endif*/