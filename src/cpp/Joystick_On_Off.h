#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <iostream>
#include <Joystick.h>
#include <cmath>
#include <constants.h>
#include <scissor.h>

void JoystickOnOff::Start_Joystick_Use(){}
void JoystickOnOff::Joystick_Toggle_On(){
	 if (buttonstate_A == 0)
            {
                if (A_Button)
                {
                    Turning_A_Button_On = 1;
                    Toggle_On_Variable_A = 0;
			  }
                else if (Turning_A_Button_On)
                {
                    Toggle_On_Variable_A = 1;
                    buttonstate_A = 1;
                }
            }
            if (Turning_A_Button_On){
                talon_left_a->Set(ControlMode::PercentOutput, .2);
            }
            if (Toggle_On_Variable_A)
            {
                if (A_Button)
                {
                    Turning_A_Button_Off = 1;
                    Toggle_Off_Variable_A = 0;
                }
                else if (Turning_A_Button_Off)
                {
                    Toggle_Off_Variable_A = 1;
                }
            }
            if (Turning_A_Button_Off)
            {
                talon_left_a->Set(ControlMode::PercentOutput, 0);
            }
            if (Toggle_Off_Variable_A)
            {
                buttonstate_A = 0;
                Turning_A_Button_Off = 0;
                Toggle_Off_Variable_A = 0;
                Toggle_On_Variable_A = 0;
                Turning_A_Button_On = 0;
            }

}
void JoystickOnOff::Run_Autonomous(){
	
}