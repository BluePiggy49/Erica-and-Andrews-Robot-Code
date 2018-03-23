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
		void start_loop();//sync_p_gain,max_peak_output
		void stop_loop();

		inline float get_sync_error();

		float getHeightL();
		float getHeightR();
		float getHeightM();
		
		void set_position(float target_inch);  
		void increment_position(float increment_direction);

		enum whichHeight{
			zero_position = 0,
			swtch,
			scale,
			manual
		};
		void starting_scissorjoystick();
		const float homing_height = -50;
		const float switch_height =  20;
		const float scaley_height =  84;
		const float manual_height =  90;

	private:
		float target_inch = 0.0;
		Notifier* notifier;
		TalonSRX *talon_left, *talon_right; 
		DigitalInput* dio_left, *dio_right;
		void run_loop();
		inline float inches_to_native (float inches);
		inline float native_to_inches (int native);
		inline void home();
		inline float clamp_max (float input);

		bool stopped=false;

		float sync_p_gain = 1.0;
		float max_peak_output = 0.3;

		const float scissor_arm_length = 20.5;
		const float rotations_per_inch = 5.0;
		const float increment_length   = 0.2;

};

