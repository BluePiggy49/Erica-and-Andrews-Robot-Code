#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <scissor_controller.h>

void ScissorController::scissorlift_increment_position(float direction){
	scissorlift->set_position( scissorlift->get_target() + direction * manual_step_length);
}

void ScissorController::run_loop(){	
	throttle_down = joy->GetRawAxis(2) > throttle_cutoff;
	throttle_up = joy->GetRawAxis(3) > throttle_cutoff;
	
	//only go down if the scissor is higher than 0
	if(!throttle_down && scissor_downLast){
		if(scissor_position_mode>0 && scissor_position_mode<3){
			scissor_position_mode--;
		//if in manual and scissor was already at scale when throttle was pressed
		}else if(scissor_position_mode==3 && wasAtScale){
			scissor_position_mode--;
			wasAtScale=false;
		}
	//only go up if the scissor is lower than scale level
	}else if(!throttle_up && scissor_upLast){
		if(scissor_position_mode<2){
			scissor_position_mode++;
		}
	}
	
	//when in manual, only be ready to lower to switch height on down throttle release...
	//...if scissor was at scale height on down throttle press
	if(throttle_down && !scissor_downLast && scissor_position_mode==3 && scissorlift->get_position()<=this->scaley_height){
		wasAtScale=true;
	}
	
	//when scissor reaches scale height and up throttle is held down, shift to manual
	if(throttle_up && scissor_position_mode==2 && scissorlift->get_position()>=this->scaley_height){
		scissor_position_mode++;
	}
	
	//set target height
	switch (scissor_position_mode){
	case zero_position:
		scissorlift->set_position(this->homing_height);
		break;
	case swtch:
		scissorlift->set_position(this->switch_height);
		break;
	case scale:
		scissorlift->set_position(this->scaley_height);
		break;
	case manual:
		//when the down button is being pressed and scissor is above scale height
		if(throttle_down && scissorlift->get_position()>this->scaley_height){
			this->scissorlift_increment_position(-1);
		}else if(throttle_up>throttle_cutoff){
			this->scissorlift_increment_position(1);
		}
		break;
	}
	
	//store states of sensors for next frame
	scissor_downLast=throttle_down;
	scissor_upLast=throttle_up;
}
