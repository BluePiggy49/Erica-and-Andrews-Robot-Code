#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>
#include <scissor_controller.h>
#include <PID.h>
#include <drivebase.h>
#include <Solenoid.h>
#include <pneumatic.h>

using namespace frc;
using namespace ValueControl;

class Robot: public IterativeRobot {
	TalonSRX *drive_talon_left_enc,*drive_talon_left_noenc,*drive_talon_right_enc,*drive_talon_right_noenc, *scissorlift_talon_left,*scissorlift_talon_right, *climber_talon_noenc, *intake_talon_left,*intake_talon_right, *climber_talon_enc;
	ScissorLift *scissorlift;
	Joystick *joy;
	Intake *intake;
	DigitalInput *limitswitch_scissorlift_left,*limitswitch_scissorlift_right;
	ScissorLiftController *joystick_scissor_lift;
	PID *pid;
	Solenoid *solenoid_1, *solenoid_2;
	DriveBase *drivebase;
	Pneumatic *pneumatic;

    void RobotInit() {
//define talons
	drive_talon_left_enc = new TalonSRX(7);
	drive_talon_left_enc->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	drive_talon_left_noenc = new TalonSRX(3);
	drive_talon_left_noenc->Set(ControlMode::Follower, num_drive_talon_left_enc);
	drive_talon_right_enc = new TalonSRX(2);
	drive_talon_right_enc->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0,talon_timeout_ms);
	drive_talon_right_noenc = new TalonSRX(5);
	drive_talon_right_noenc->Set(ControlMode::Follower, num_drive_talon_right_enc);

//scissor
	scissorlift_talon_left = new TalonSRX(1);
	scissorlift_talon_right = new TalonSRX(8);

//climber
	climber_talon_noenc = new TalonSRX(num_climber_talon_noenc);
	climber_talon_enc = new TalonSRX(num_climber_talon_enc);

//intake
	intake_talon_left = new TalonSRX(num_intake_talon_left);
	intake_talon_right = new TalonSRX(num_intake_talon_right);
	
//joystick
	joy = new Joystick(0);
	
//scissor lift
	scissorlift = new ScissorLift(scissorlift_talon_left,scissorlift_talon_right);

//intake
	intake = new Intake(intake_talon_right, intake_talon_left, joy);

//joystick scissor lift
	joystick_scissor_lift = new ScissorLiftController(joy, scissorlift, 4096/10);

//PID	
	//pid = new PID(drive_talon_left_enc, drive_talon_right_enc, scissorlift_talon_left, scissorlift_talon_right);
	//pid->pidSet();
		drive_talon_left_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_left_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

		drive_talon_right_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_right_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

		scissorlift_talon_left->Config_kF(0, 0, talon_timeout_ms);
		scissorlift_talon_left->Config_kP(0, 1, talon_timeout_ms);
		scissorlift_talon_left->Config_kI(0, 0, talon_timeout_ms);
		scissorlift_talon_left->Config_kD(0, 10, talon_timeout_ms);

		scissorlift_talon_right->Config_kF(0, 0, talon_timeout_ms);
		scissorlift_talon_right->Config_kP(0, 1, talon_timeout_ms);
		scissorlift_talon_right->Config_kI(0, 0, talon_timeout_ms);
		scissorlift_talon_right->Config_kD(0, 10, talon_timeout_ms);

//DriveBase
	drivebase = new DriveBase(drive_talon_left_enc, drive_talon_left_noenc, drive_talon_right_enc, drive_talon_right_noenc, joy, intake_talon_left, intake_talon_right);	 
}


    

    void AutonomousInit() {
}
    void AutonomousPeriodic() {
}
   void TeleopInit() { 
   joystick_scissor_lift->start(1.4 / 4096, 1.0);
}
    void TeleopPeriodic() {
	//Manual
if(SmartDashboard::GetBoolean("DB/Button 1",0)){
	drivebase->run_loop();
	intake->Start_Intake(0.5, -0.5); 
	joystick_scissor_lift->update();
}else{
	drivebase->run_loop();
	intake->Start_Intake(0.5, -0.5); 
}
} 

void DisabledInit() {
	joystick_scissor_lift->stop();
}
    void DisabledPeriodic() { }
};
START_ROBOT_CLASS(Robot);
