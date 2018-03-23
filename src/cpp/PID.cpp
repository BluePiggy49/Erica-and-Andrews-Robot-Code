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

void PID::pidSet(){
		drive_talon_left_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_left_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_left_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

		drive_talon_right_enc->Config_kF(0, bunnybotFgainVelocity, talon_timeout_ms);
		drive_talon_right_enc->Config_kP(0, SmartDashboard::GetNumber("DB/Slider 1",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kI(0, SmartDashboard::GetNumber("DB/Slider 2",0.0) , talon_timeout_ms);
		drive_talon_right_enc->Config_kD(0, SmartDashboard::GetNumber("DB/Slider 3",0.0) , talon_timeout_ms);

	}