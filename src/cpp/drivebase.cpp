#include <drivebase.h>
#include <valuecontrol.h>

using namespace ValueControl;
void DriveBase::run_loop(){	
	float move= exponent_mirrored(joy->GetRawAxis(4), 2);
	//std::cout<<"Little Piggy, Big Piggy"<<std::endl;
	float turn= exponent_mirrored(joy->GetRawAxis(1), 3);
	float wheel_left= constrain( move-turn , -1.0,1.0);
	float wheel_right= constrain( move+turn , -1.0,1.0);
	//std::cout<<"Little Piggy, Big Piggy"<<std::endl;


	if (abs(intake_talon_left->GetMotorOutputPercent()) > 0 || abs(intake_talon_right->GetMotorOutputPercent()) )
	{
			drive_talon_left_enc->Set(ControlMode::PercentOutput, -0.25 * wheel_left);
			drive_talon_right_enc->Set(ControlMode::PercentOutput, -0.25 * wheel_right);
	}else{
			drive_talon_left_enc->Set(ControlMode::PercentOutput, -1 * wheel_left);
			drive_talon_right_enc->Set(ControlMode::PercentOutput, -1 * wheel_right);
	}
}
