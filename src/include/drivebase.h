#ifndef DRIVEBASE_H
#define DRIVEBASE_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <scissor_controller.h>
#include <PID.h>
#include <Solenoid.h>
#include <intake.h>


class DriveBase {
	public:
		DriveBase( TalonSRX* drive_talon_left_enc,
			   TalonSRX* drive_talon_left_noenc,
			   TalonSRX* drive_talon_right_enc,
			   TalonSRX* drive_talon_right_noenc,
			   Joystick* joy, TalonSRX* intake_talon_left, TalonSRX* intake_talon_right)
			: drive_talon_left_enc(drive_talon_left_enc), drive_talon_left_noenc(drive_talon_left_noenc), drive_talon_right_enc(drive_talon_right_enc), 
			drive_talon_right_noenc(drive_talon_right_noenc), joy(joy), intake_talon_left(intake_talon_left), intake_talon_right(intake_talon_right) {};

		void run_loop();
	private:
		TalonSRX* drive_talon_left_enc;
			   TalonSRX* drive_talon_left_noenc;
			   TalonSRX* drive_talon_right_enc;
			   TalonSRX* drive_talon_right_noenc;
			   Joystick* joy;
			   TalonSRX* intake_talon_left;
			   TalonSRX* intake_talon_right;
	
};
#endif
