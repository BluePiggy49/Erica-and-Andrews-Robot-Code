#pragma once
#define SCISSOR_H

#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <settings.h>


class ScissorLift {
	public:
		ScissorLift(TalonSRX* talon_left, TalonSRX* talon_right, DigitalInput* dio_left, DigitalInput* dio_right)
			: talon_left(talon_left), talon_right(talon_right), dio_left(dio_left), dio_right(dio_right) {
				notifier = new Notifier(&ScissorLift::run_loop, this);
			};
		void start_loop(float sync_p_gain,float max_peak_output);
		void stop_loop();

		inline float get_sync_error();

		float get_position();
		float get_target();
		
		void set_position(float target);  
		void increment_position(float increment_direction);


	private:
		float target = 0.0;
		Notifier* notifier;
		TalonSRX *talon_left, *talon_right; 
		DigitalInput* dio_left, *dio_right;
		void run_loop();
		inline float inches_to_native (float inches);
		inline float native_to_inches (int native);
		inline float clamp_max (float input);

		bool stopped=false;

		float sync_p_gain = 1.0;
		float max_peak_output = 0.3;

		const float scissor_arm_length = 20.5;
		const float rotations_per_inch = 5.0;
		const float increment_length   = 0.2;

};