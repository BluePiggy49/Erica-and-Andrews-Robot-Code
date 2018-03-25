/*#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>
#include <joystickscissor.h>

void JoystickScissorLift::run_scissorjoystick(){
	bool scissorlift_down=joy->GetRawAxis(2);
	bool scissorlift_up=joy->GetRawAxis(3);	
	//only go down if the scissor is higher than 0
	if(scissorlift_down<throttle_cutoff && scissorlift_downLast){
		if(scissorlift_position_mode>0 && scissorlift_position_mode<3){
			scissorlift_position_mode--;
		//if in manual and scissor was already at scale when throttle was pressed
		}else if(scissorlift_position_mode==3 && wasAtScale){
			scissorlift_position_mode--;
			wasAtScale=false;
		}
	//only go up if the scissor is lower than scale level
	}else if(scissorlift_up<throttle_cutoff && scissorlift_upLast){
		if(scissorlift_position_mode<2){
			scissorlift_position_mode++;
		}
	}
	
	//when in manual, only be ready to lower to switch height on down throttle release...
	//...if scissor was at scale height on down throttle press
	if(scissorlift_down>throttle_cutoff&&!scissorlift_downLast && scissorlift_position_mode==3 && scissorlift->getHeightM()<=scissorlift->scaley_height){
		wasAtScale=true;
	}
	
	//when scissor reaches scale height and up throttle is held down, shift to manual
	if(scissorlift_up>throttle_cutoff && scissorlift_position_mode==2 && scissorlift->getHeightM()>=scissorlift->scaley_height){
		scissorlift_position_mode++;
	}
	
	//set target height
	switch (scissorlift_position_mode){
	case ScissorLift::zero_position:
		scissorlift->set_position(scissorlift->homing_height);
		break;
	case ScissorLift::swtch:
		scissorlift->set_position(scissorlift->switch_height);
		break;
	case ScissorLift::scale:
		scissorlift->set_position(scissorlift->scaley_height);
		break;
	case ScissorLift::manual:
		//when the down button is being pressed and scissor is above scale height
		if(scissorlift_down>throttle_cutoff && scissorlift->getHeightM()>scissorlift->scaley_height){
			scissorlift->increment_position(-1);
		}else if(scissorlift_up>throttle_cutoff){
			scissorlift->increment_position(1);
		}
		break;
	}
	
	//vibrate when scissor hits a certain height
	if(scissorlift_down>throttle_cutoff || scissorlift_up>throttle_cutoff){
		if(scissorlift->getHeightL()==scissorlift->homing_height
		|| scissorlift->getHeightL()==scissorlift->switch_height
		|| scissorlift->getHeightL()==scissorlift->scaley_height
		  ){
			joy->SetRumble(GenericHID::kLeftRumble,0.5);
		}
		if(scissorlift->getHeightR()==scissorlift->homing_height
		|| scissorlift->getHeightR()==scissorlift->switch_height
		|| scissorlift->getHeightR()==scissorlift->scaley_height
		  ){
			joy->SetRumble(GenericHID::kRightRumble,0.5);
		}
	}
	
	//store states of sensors for next frame
	if(scissorlift_down>throttle_cutoff){
		scissorlift_downLast=true;
	}else{
		scissorlift_downLast=false;
	}
	if(scissorlift_up>throttle_cutoff){
		scissorlift_upLast=true;
	}else{
		scissorlift_upLast=false;
	}
}*/