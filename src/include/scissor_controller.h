#pragma once
#define SCISSOR_CONTROLLER_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>

class ScissorController
{
	public:
		ScissorController(Joystick *joy, ScissorLift *scissorlift) : joy(joy), scissorlift(scissorlift) {};
		void run_loop();

	private:
		ScissorLift *scissorlift;
		Joystick *joy;
	
		void scissorlift_increment_position(float direction);

		double throttle_down, throttle_up;				

		int scissor_position_mode;
		bool scissor_downLast=true;
		bool scissor_upLast=true;
		bool wasAtScale=false;

		bool AoffLast=true;
		bool intake_in=false;

		enum whichHeight{
			zero_position = 0,
			swtch,
			scale,
			manual
		};

		const float homing_height = -50;
		const float switch_height =  20;
		const float scaley_height =  84;
		const float manual_height =  90;

		const float manual_step_length = 0.2;
};

