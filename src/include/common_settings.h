 #ifndef COMMON_SETTINGS_H
#define COMMON_SETTINGS_H

// Digital io pins
const int dio_idx_scissor_left = 1;
const int dio_idx_scissor_right = 2;

// Limits
const float scissorlift_one_rotation_nu = 4096.0;
const float scissorlift_minumum_height_in = 0.0;
//const float scissorlift_maximum_height_in = -7.75;
const float scissorlift_maximum_height_in = -8.75;
const float scissorlift_in_to_nu = scissorlift_one_rotation_nu * 5.0;

enum LimitSwitchState {
	Closed = 0,
	Open = 1,
};

// Scissor lift coeffs
const float scissorlift_p_gain = 1.4 / scissorlift_one_rotation_nu;
const float scissorlift_max_speed = 1.0;

#endif