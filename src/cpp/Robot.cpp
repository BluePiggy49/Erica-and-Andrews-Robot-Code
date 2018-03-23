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
#include <drivebase.h>

using namespace frc;
using namespace ValueControl;

class Robot: public IterativeRobot {
	TalonSRX *drive_talon_left_enc,*drive_talon_left_noenc,*drive_talon_right_enc,*drive_talon_right_noenc, *scissorlift_talon_left,*scissorlift_talon_right, *climber_talon_noenc, *intake_talon_left,*intake_talon_right, *climber_talon_enc;
	ScissorLift *scissorlift;
	Joystick *joy;
	Intake *intake;
	DigitalInput *limitswitch_scissorlift_left,*limitswitch_scissorlift_right;
	JoystickScissorLift *joystick_scissor_lift;
	PID *pid;
	DriveBase *drivebase;

//analog buttons
	double move, turn, scissorlift_down, scissorlift_up;

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
	scissorlift->start_loop();

//intake
	intake = new Intake(intake_talon_right, intake_talon_left, joy);

//joystick scissor lift
	joystick_scissor_lift = new JoystickScissorLift(joy, scissorlift);

//PID	
	pid = new PID(drive_talon_left_enc, drive_talon_right_enc);
	pid->pidSet();

//DriveBase
	drivebase = new DriveBase(drive_talon_left_enc, drive_talon_left_noenc, drive_talon_right_enc, drive_talon_right_noenc, joy);	
}


    void DisabledInit() {
	scissorlift->stop_loop();
}
    void DisabledPeriodic() { }

    void AutonomousInit() {
}
    void AutonomousPeriodic() {
}
    void TeleopInit() {
}
    void TeleopPeriodic() {
    drivebase->run_loop();
	joystick_scissor_lift->run_scissorjoystick();
	intake->Start_Intake(0.5, -0.5);
}

    void TestInit() {}
    void TestPeriodic() {}

};
START_ROBOT_CLASS(Robot);
