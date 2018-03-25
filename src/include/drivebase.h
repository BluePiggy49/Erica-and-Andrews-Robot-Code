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
#include <intake.h>
#include <joystickscissor.h>
#include <PID.h>
#include <Solenoid.h>


class DriveBase {
	public:
		DriveBase( TalonSRX* drive_talon_left_enc,
			   TalonSRX* drive_talon_left_noenc,
			   TalonSRX* drive_talon_right_enc,
			   TalonSRX* drive_talon_right_noenc,
			   Joystick* joy)
			: drive_talon_left_enc(drive_talon_left_enc), drive_talon_left_noenc(drive_talon_left_noenc), drive_talon_right_enc(drive_talon_right_enc), drive_talon_right_noenc(drive_talon_right_noenc), joy(joy) {};

		void run_loop();
	private:
		TalonSRX* drive_talon_left_enc;
			   TalonSRX* drive_talon_left_noenc;
			   TalonSRX* drive_talon_right_enc;
			   TalonSRX* drive_talon_right_noenc;
			   Joystick* joy;
	
};
#endif