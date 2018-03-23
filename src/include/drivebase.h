#pragma once
#define DRIVEBASE_H

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <constants.h>


class DriveBase {
	public:
		DriveBase( TalonSRX* drive_talon_left_enc,
			   TalonSRX* drive_talon_left_noenc,
			   TalonSRX* drive_talon_right_enc,
			   TalonSRX* drive_talon_right_noenc,
			   Joystick* joy
			: drive_talon_left_enc(drive_talon_left_enc), drive_talon_left_noenc(drive_talon_left_noenc), drive_talon_right_enc(drive_talon_right_enc), drive_talon_right_noenc(drive_talon_right_noenc) {};

		void run_loop;
	private:
		void transform_the_stuff;
		float move, turn, wheel_left, wheel_right;
};
