#pragma once
#define CONSTANTS_H

const float DRIVE_SPEED=0.5;
const float SUCKY_SPEED=0.3;
const float HEADY_SPEED=0;

//drive talon indicies
const int num_drive_talon_left_enc = 2;
const int num_drive_talon_left_noenc = 3;
const int num_drive_talon_right_enc = 7;
const int num_drive_talon_right_noenc =	5;

//rest of the talon indicies
const int num_scissorlift_talon_left = 1;
const int num_scissorlift_talon_right = 8;
const int num_climber_talon_noenc = 6;
const int num_climber_talon_enc = 4;
const int num_intake_talon_left = 9;
const int num_intake_talon_right = 10;


//limit switches
const int num_limitswitch_scissorlift_left = 1;
const int num_limitswitch_scissorlift_right = 2;

//Turns out DIO pins float at '1' (Positive) So all of our limit switches are Normally Open and put 0 (Negative) when closed.
enum LimitSwitchState {
	Closed = 0,
	Open = 1,
};

const float throttle_cutoff=0.4;
const float talon_timeout_ms=10;

const float bunnybotFgainVelocity=1.45;