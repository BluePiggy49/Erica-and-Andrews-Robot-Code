#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <Joystick.h>
#include <iostream>
#include <cmath>
#include <constants.h>
#include <scissor.h>
<<<<<<< Updated upstream
#include <scissor_controller.h>
#include <intake.h>
#include <valuecontrol.h>
=======
>>>>>>> Stashed changes

using namespace frc;

class Robot: public IterativeRobot {
<<<<<<< Updated upstream
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
=======
	TalonSRX *tDrivela,*tDrivelb,*tDrivera,*tDriverb, *tScizLeft,*tScizRght, *tHeadRear, *tSuckLeft,*tSuckRght, *tWinch;
	ScissorLift *scizzer;
	Joystick *joy;
	DigitalInput *lscizzl,*lscizzr, *lsucker, *lreardn,*lrearup;
//analog buttons
	double move, turn, scizdn, scizup;
//on-off buttons
	bool sucki,sucko,autoalign,wincher,headrear;
	
//misc variables
	int scizMode=0;
	bool scizdnLast=true;
	bool scizupLast=true;
	bool wasAtScale=false;
	
	bool AoffLast=true;
	bool suckingin=false;
	
	double constrain(double val,double lower,double upper){
		if(val<lower){
			return lower;
		}else if(val>upper){
			return upper;
		}else{
			return val;
		}
	}

    void RobotInit() {
//define talons
	tDrivela=new TalonSRX(num_tDrivela);
	tDrivela->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	tDrivelb=new TalonSRX(num_tDrivelb);
	tDrivelb->Set(ControlMode::Follower, num_tDrivela);
	tDrivera=new TalonSRX(num_tDrivera);
	tDrivera->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	tDriverb=new TalonSRX(num_tDriverb);
	tDriverb->Set(ControlMode::Follower, num_tDrivera);

	tScizLeft=new TalonSRX(num_tScizLeft);
	tScizRght=new TalonSRX(num_tScizRght);
	tHeadRear=new TalonSRX(num_tHeadRear);
	tSuckLeft=new TalonSRX(num_tSuckLeft);
	tSuckRght=new TalonSRX(num_tSuckRght);

	tWinch=new TalonSRX(num_tWinch);
>>>>>>> Stashed changes
	
//joystick
	joy=new Joystick(0);
	
//limit switches
	lscizzl=new DigitalInput(num_lscizzl);
	lscizzr=new DigitalInput(num_lscizzr);
	lreardn=new DigitalInput(num_lreardn);
	lrearup=new DigitalInput(num_lrearup);
	lsucker=new DigitalInput(num_lsucker);
	
//scissor lift
<<<<<<< Updated upstream
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

=======
	scizzer=new ScissorLift( tScizLeft,tScizRght, lscizzl,lscizzr );
	scizzer->start_loop();
}

	void pidSet(){
		tDrivela->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		tDrivela->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		tDrivela->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		tDrivela->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);
/*
		tDrivera->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		tDrivera->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		tDrivera->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		tDrivera->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);
*/
>>>>>>> Stashed changes
	}

    void DisabledInit() {
	scizzer->stop_loop();
}
    void DisabledPeriodic() { }

    void AutonomousInit() {
	pidSet();
<<<<<<< Updated upstream
	drive_talon_left_enc->Set(ControlMode::Velocity,500);
}
    void AutonomousPeriodic() {
//	std::cout<<drive_talon_left_enc->GetSelectedSensorVelocity(0)<<"\t"<<drive_talon_left_enc->GetClosedLoopError(0)<<std::endl;
=======
	tDrivela->Set(ControlMode::Velocity,500);
}
    void AutonomousPeriodic() {
//	std::cout<<tDrivela->GetSelectedSensorVelocity(0)<<"\t"<<tDrivela->GetClosedLoopError(0)<<std::endl;
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	scissorlift->start_loop(scissor_sync_p_gain, scissor_max_peak_output);
}
    void TeleopPeriodic() {
    	intake->Start_Intake(0.5, -0.5);
    
//drive
=======
}
    void TeleopPeriodic() {
//drive
/*
>>>>>>> Stashed changes
	move=joy->GetRawAxis(1);//forward axis
	move=pow(move,3);
	
	turn=joy->GetRawAxis(4);//angular axis
	turn=pow(move,3);
	
	// left wheels
<<<<<<< Updated upstream
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
=======
	tDrivela->Set(ControlMode::PercentOutput, constrain(turn-move,0,1) * DRIVE_SPEED );
	//right wheels
	tDrivera->Set(ControlMode::PercentOutput, constrain(turn+move,0,1) * DRIVE_SPEED );
*/	
//*scissorlift
	scizdn=joy->GetRawAxis(2);
	scizup=joy->GetRawAxis(3);
	
	//only go down if the scissor is higher than 0
	if(scizdn<throttle_cutoff && scizdnLast){
		if(scizMode>0 && scizMode<3){
			scizMode--;
		//if in manual and scissor was already at scale when throttle was pressed
		}else if(scizMode==3 && wasAtScale){
			scizMode--;
			wasAtScale=false;
		}
	//only go up if the scissor is lower than scale level
	}else if(scizup<throttle_cutoff && scizupLast){
		if(scizMode<2){
			scizMode++;
>>>>>>> Stashed changes
		}
	}
	
	//when in manual, only be ready to lower to switch height on down throttle release...
	//...if scissor was at scale height on down throttle press
<<<<<<< Updated upstream
	if(throttle_down>throttle_cutoff&&!scissor_downLast && scissor_position_mode==3 && scissorlift->getHeightM()<=scissorlift->scaley_height){
=======
	if(scizdn>throttle_cutoff&&!scizdnLast && scizzer->getHeight()==scizzer->scaley_height){
>>>>>>> Stashed changes
		wasAtScale=true;
	}
	
	//when scissor reaches scale height and up throttle is held down, shift to manual
<<<<<<< Updated upstream
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

=======
	if(scizup>throttle_cutoff && scizMode==2 && scizzer->getHeight()>=scizzer->scaley_height){
		scizMode++;
	}
	
	//set target height
	switch (scizMode){
	case ScissorLift::homey:
		scizzer->set_position(scizzer->homing_height);
		break;
	case ScissorLift::swtch:
		scizzer->set_position(scizzer->switch_height);
		break;
	case ScissorLift::scale:
		scizzer->set_position(scizzer->scaley_height);
		break;
	case ScissorLift::manual:
		//when the down button is being pressed and scissor is above scale height
		if(scizdn>throttle_cutoff && scizzer->getHeight()>scizzer->scaley_height){
			scizzer->increment_position(1);
		}else if(scizup>throttle_cutoff){
			scizzer->increment_position(-1);
		}
		break;
	}
					////////////////////////////////////////////////////////////////
	
	//store states of sensors for next frame
	if(scizdn>throttle_cutoff){
		scizdnLast=true;
	}else{
		scizdnLast=false;
	}
	if(scizup>throttle_cutoff){
		scizupLast=true;
	}else{
		scizupLast=false;
	}
	
//sucky i/o
	sucki=joy->GetRawButton(1);
	sucko=joy->GetRawButton(2);
	
	//A button is in 'press on press off' format; suck in
	if(sucki & AoffLast){
		if(suckingin){
			suckingin=false;
		}else{
			suckingin=true;
		}
	}
	
	//B button is in 'press and hold' mode; suck out
	//B overrides all
	if(sucko){
		suckingin=false;
		
//		tSuckLeft->Set(ControlMode::PercentOutput, -SUCKY_SPEED );
		tSuckRght->Set(ControlMode::PercentOutput,  SUCKY_SPEED );
	//limit switch to supress motors when they want to suck in
	}else /*if(lsucker && suckingin){
		tSuckLeft->Set(ControlMode::PercentOutput, 0);
		tSuckRght->Set(ControlMode::PercentOutput, 0);
	}else*/{
//		tSuckLeft->Set(ControlMode::PercentOutput, suckingin *  SUCKY_SPEED );
		tSuckRght->Set(ControlMode::PercentOutput, suckingin * -SUCKY_SPEED );
	}
	AoffLast=!joy->GetRawButton(1);

//+head tipper
	headrear=joy->GetRawButton(5);
	
//if either limit switch on the head is triggered, the motor stops
	if(lreardn || lrearup ){
		tHeadRear->Set(ControlMode::PercentOutput, 0);
		std::cout<<"wurking"<<std::endl;
	//when left bumper is pressed, motor goes up
	}else if(headrear){
		tHeadRear->Set(ControlMode::PercentOutput,  HEADY_SPEED);
		std::cout<<"yah"<<std::endl;
	//motor will always go down unless bumper or lower limit switch is triggered
	}else{
		tHeadRear->Set(ControlMode::PercentOutput, -HEADY_SPEED);
		std::cout<<"cake"<<std::endl;
	}
/*	
//+winch
	wincher=joy->GetRawButton(4);
	
//autoalign- not working yet!
	autoalign=joy->GetRawButton(6);
*/
>>>>>>> Stashed changes
}

    void TestInit() {}
    void TestPeriodic() {}

};
START_ROBOT_CLASS(Robot);
