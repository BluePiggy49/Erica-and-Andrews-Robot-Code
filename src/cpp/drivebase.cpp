#include <drivebase.h>
#include <valuecontrol.h>

void DriveBase::transform_the_stuff(){
	this->move=ValueControl::exponent_mirrored(this->move, 2);
	this->turn=ValueControl::exponent_mirrored(this->turn, 3);
	this->wheel_left=ValueControl::constrain( move-turn , -1.0,1.0);
	this->wheel_right=ValueControl::constrain( move+turn , -1.0,1.0);
}

void DriveBase::run_loop(){
	this->move=this->joy->GetRawAxis(1);
	this->turn=this->joy->GetRawAxis(4);

	this->transform_the_stuff();

	this->drive_talon_left_enc->Set(ControlMode::PercentOutput, wheel_left);
	this->drive_talon_right_enc->Set(ControlMode::PercentOutput, wheel_right);
}
