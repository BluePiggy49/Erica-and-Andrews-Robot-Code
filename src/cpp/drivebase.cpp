#include <drivebase.h>
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

using namespace ValueControl;
void DriveBase::run_loop(){
	
	std::cout<<"Blue Piggy, Red Piggy"<<std::endl;
	
	float move= exponent_mirrored(joy->GetRawAxis(4), 2);
	std::cout<<"Little Piggy, Big Piggy"<<std::endl;
	float turn= exponent_mirrored(joy->GetRawAxis(1), 3);
	float wheel_left= constrain( move-turn , -1.0,1.0);
	float wheel_right= constrain( move+turn , -1.0,1.0);

	drive_talon_left_enc->Set(ControlMode::PercentOutput, -1 * wheel_left);
	drive_talon_right_enc->Set(ControlMode::PercentOutput, -1 * wheel_right);

}
