#include <drivebase.h>
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
#include <pneumatic.h>


void Pneumatic::run_pneumatics(){
	bool Getting_the_pneumatic_value = solenoid_1->Get();
	bool Getting_the_value_of_the_left_button = joy->GetRawButton(1);
	Left_Button = Getting_the_value_of_the_left_button;
	if (buttonstate_Left == 0)
            {
                if (Left_Button)
                {
                    Turning_Left_Button_On = 1;
                    Toggle_On_Variable_Left = 0;
                }
                else if (Turning_Left_Button_On)
                {
                    Toggle_On_Variable_Left = 1;
                    buttonstate_Left = 1;  
                }
            }
            if (Turning_Left_Button_On){
                solenoid_1->Set(Getting_the_pneumatic_value + 1);
                solenoid_2->Set(Getting_the_pneumatic_value);
               
			  }
            if (Toggle_On_Variable_Left)
            {
                if (Left_Button)
                {
                    Turning_Left_Button_Off = 1;
                    Toggle_Off_Variable_Left = 0;
                }
                else if (Turning_Left_Button_Off)
                {
                    Toggle_Off_Variable_Left = 1;
                }
            }
            if (Turning_Left_Button_Off)
            {
                solenoid_1->Set(Getting_the_pneumatic_value + 1);
                solenoid_2->Set(Getting_the_pneumatic_value);
              
            }
            if (Toggle_Off_Variable_Left)
            {
                buttonstate_Left = 0;
                Turning_Left_Button_Off = 0;
                Toggle_Off_Variable_Left = 0;
                Toggle_On_Variable_Left = 0;
                Turning_Left_Button_On = 0;
            }
}