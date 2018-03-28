#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>

void Intake::Start_Intake(float intake_speed_in, float intake_speed_out){
	Getting_Right_Button = joy->GetRawButton(6);
	Getting_Left_Button = joy->GetRawButton(5);

	if (Getting_Right_Button)
	{
		intake_talon_left->Set(ControlMode::PercentOutput, intake_speed_in);
		intake_talon_right->Set(ControlMode::PercentOutput, intake_speed_in);
	}
	else if (Getting_Left_Button)
	{
		intake_talon_left->Set(ControlMode::PercentOutput, intake_speed_out);
		intake_talon_right->Set(ControlMode::PercentOutput, intake_speed_out);
	}
	else{
		intake_talon_left->Set(ControlMode::PercentOutput, 0);
		intake_talon_right->Set(ControlMode::PercentOutput, 0);
	}
}