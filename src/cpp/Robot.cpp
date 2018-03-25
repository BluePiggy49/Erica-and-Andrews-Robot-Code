#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <scissor_controller.h>
#include <intake.h>
#include <valuecontrol.h>

using namespace frc;
using namespace ValueControl;

class Robot: public IterativeRobot {
	TalonSRX *drive_talon_left_enc,*drive_talon_left_noenc,*drive_talon_right_enc,*drive_talon_right_noenc, *scissorlift_talon_left,*scissorlift_talon_right, *climber_talon_noenc, *intake_talon_left,*intake_talon_right, *climber_talon_enc;
	ScissorLift *scissorlift;
	ScissorController *scissorcontroller;
	Joystick *joy;
	Intake *intake;
	DigitalInput *limitswitch_scissorlift_left,*limitswitch_scissorlift_right;
//analog buttons
	double move, turn, scissorlift_down, scissorlift_up;
//on-off buttons
	bool intake_in_button,intake_out_button,autoalign,winch_button;
	
//misc variables
	int scissorlift_position_mode;
	bool scissorlift_downLast=true;
	bool scissorlift_upLast=true;
	bool wasAtScale=false;
	
	bool AoffLast=true;
	bool intake_in=false;

    void RobotInit() {
//define talons
	std::cout<<"If you're happy and a pig, clap your hands! *clap, clap* orange pig"<<std::endl;
	drive_talon_left_enc = new TalonSRX(num_drive_talon_left_enc);
	drive_talon_left_enc->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	drive_talon_left_noenc = new TalonSRX(num_drive_talon_left_noenc);
	drive_talon_left_noenc->Set(ControlMode::Follower, num_drive_talon_left_enc);
	drive_talon_right_enc = new TalonSRX(num_drive_talon_right_enc);
	drive_talon_right_enc->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	drive_talon_right_noenc = new TalonSRX(num_drive_talon_right_noenc);
	drive_talon_right_noenc->Set(ControlMode::Follower, num_drive_talon_right_enc);

	//scissor
	scissorlift_talon_left = new TalonSRX(num_scissorlift_talon_left);
	scissorlift_talon_right = new TalonSRX(num_scissorlift_talon_right);

	//climber
	climber_talon_noenc = new TalonSRX(num_climber_talon_noenc);
	climber_talon_enc = new TalonSRX(num_climber_talon_enc);

	//intake
	intake_talon_left = new TalonSRX(num_intake_talon_left);
	intake_talon_right = new TalonSRX(num_intake_talon_right);
	
//joystick
	joy=new Joystick(0);
	
//limit switches
	limitswitch_scissorlift_left = new DigitalInput(num_limitswitch_scissorlift_left);
	limitswitch_scissorlift_right = new DigitalInput(num_limitswitch_scissorlift_right);
	
//scissor lift
	scissorlift = new ScissorLift(scissorlift_talon_left,scissorlift_talon_right, limitswitch_scissorlift_left, limitswitch_scissorlift_right);

	scissorcontroller = new ScissorController(joy, scissorlift);

	intake = new Intake(intake_talon_right, intake_talon_left, joy);
	
}

	void pidSet(){
		drive_talon_left_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_left_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

		drive_talon_right_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_right_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

	}

    void DisabledInit() {
	scissorlift->stop_loop();
}
    void DisabledPeriodic() { }

    void AutonomousInit() {
	pidSet();
	drive_talon_left_enc->Set(ControlMode::Velocity,500);
}
    void AutonomousPeriodic() {
//	std::cout<<drive_talon_left_enc->GetSelectedSensorVelocity(0)<<"\t"<<drive_talon_left_enc->GetClosedLoopError(0)<<std::endl;
}

/*    A2           A3			A2,A3=	scissorlift
   _/III\4_______/III\5			4=	rear head
  /  A1             3  \		3=	auto climb
 /  (8)A0  6 H 7  2   1 \<-trg		2=	auto align?
 \       ^          0   /<-top		0,1=	suck i/o
 /     <POV>    A5      \
/        v     (9)A4     \		A1,A4=	drive
\      ____________      /
 \____/            \____/
*/
    void TeleopInit() {
	//pidSet();
	scissorlift->start_loop(scissor_sync_p_gain, scissor_max_peak_output);
}
    void TeleopPeriodic() {
    	intake->Start_Intake(0.5, -0.5);
    
//drive
	move=joy->GetRawAxis(1);//forward axis
	move=pow(move,3);
	
	turn=joy->GetRawAxis(4);//angular axis
	turn=pow(move,3);
	
	// left wheels
	drive_talon_left_enc->Set(ControlMode::PercentOutput, constrain(turn-move,0,1) * DRIVE_SPEED );
	//right wheels
	drive_talon_right_enc->Set(ControlMode::PercentOutput, constrain(turn+move,0,1) * DRIVE_SPEED );

////////////////////////////////////////////////////////////////
//scissorlift

//ScissorController
	scissorcontroller->run_loop();
/*
	throttle_down=joy->GetRawAxis(2);
	throttle_up=joy->GetRawAxis(3);
	
	//only go down if the scissor is higher than 0
	if(throttle_down<throttle_cutoff && scissor_downLast){
		if(scissor_position_mode>0 && scissor_position_mode<3){
			scissor_position_mode--;
		//if in manual and scissor was already at scale when throttle was pressed
		}else if(scissor_position_mode==3 && wasAtScale){
			scissor_position_mode--;
			wasAtScale=false;
		}
	//only go up if the scissor is lower than scale level
	}else if(throttle_up<throttle_cutoff && scissor_upLast){
		if(scissor_position_mode<2){
			scissor_position_mode++;
		}
	}
	
	//when in manual, only be ready to lower to switch height on down throttle release...
	//...if scissor was at scale height on down throttle press
	if(throttle_down>throttle_cutoff&&!scissor_downLast && scissor_position_mode==3 && scissorlift->getHeightM()<=scissorlift->scaley_height){
		wasAtScale=true;
	}
	
	//when scissor reaches scale height and up throttle is held down, shift to manual
	if(throttle_up>throttle_cutoff && scissor_position_mode==2 && scissorlift->getHeightM()>=scissorlift->scaley_height){
		scissor_position_mode++;
	}
	
	//set target height
	switch (scissor_position_mode){
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
		if(throttle_down>throttle_cutoff && scissorlift->getHeightM()>scissorlift->scaley_height){
			scissorlift->increment_position(-1);
		}else if(throttle_up>throttle_cutoff){
			scissorlift->increment_position(1);
		}
		break;
	}
	
	//vibrate when scissor hits a certain height
	if(throttle_down>throttle_cutoff || throttle_up>throttle_cutoff){
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
	if(throttle_down>throttle_cutoff){
		scissor_downLast=true;
	}else{
		scissor_downLast=false;
	}
	if(throttle_up>throttle_cutoff){
		scissor_upLast=true;
	}else{
		scissor_upLast=false;
	}
*/
////////////////////////////////////////////////////////////////
	
//Intake code is missing. Without the limit switches, it won't work. New code currently in construction.

}

    void TestInit() {}
    void TestPeriodic() {}

};
START_ROBOT_CLASS(Robot);
