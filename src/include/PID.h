#ifndef PID_H
#define PID_H

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <settings.h>
#include <scissor.h>
#include <valuecontrol.h>
#include <intake.h>

class PID
{
public:
	PID(TalonSRX *drive_talon_left_enc, TalonSRX *drive_talon_right_enc) : drive_talon_left_enc(drive_talon_left_enc), drive_talon_right_enc(drive_talon_right_enc) {
		};
		void pidSet();

private:
	TalonSRX *drive_talon_left_enc;
	TalonSRX *drive_talon_right_enc;
};

#endif