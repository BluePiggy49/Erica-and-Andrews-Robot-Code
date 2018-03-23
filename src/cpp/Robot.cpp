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
	pid = new PID(drive_talon_left_enc, drive_talon_right_enc);
	pid->pidSet();
}


    void DisabledInit() {
	scissorlift->stop_loop();
}
    void DisabledPeriodic() { }

    void AutonomousInit() {
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
}
    void TeleopPeriodic() {
    	
   
//drive
	move=joy->GetRawAxis(1);//forward axis
	move=pow(move,3);
	
	turn=joy->GetRawAxis(4);//angular axis
	turn=pow(move,3);
	
	// left wheels
	drive_talon_left_enc->Set(ControlMode::PercentOutput, constrain(turn-move,0,1) * DRIVE_SPEED );
	//right wheels
	drive_talon_right_enc->Set(ControlMode::PercentOutput, constrain(turn+move,0,1) * DRIVE_SPEED );

				
	joystick_scissor_lift->run_scissorjoystick();
	intake->Start_Intake(0.5, -0.5);
}

    void TestInit() {}
    void TestPeriodic() {}

};
START_ROBOT_CLASS(Robot);
