#ifndef DRIVER_CONTROL
#define DRIVER_CONTROL

#include "main.h"
#include "pros/misc.h"
#include "robot.h"
#include "pid.h"
#include <cmath>
#include <ios>

using namespace pros;
using namespace std;

bool buttonR2;
bool buttonL2;
bool angle;
int launch = 0;

void chassis(){
	RF.move(con.get_analog(ANALOG_RIGHT_Y));
    RM.move(con.get_analog(ANALOG_RIGHT_Y));
    RB.move(con.get_analog(ANALOG_RIGHT_Y));

    LF.move(con.get_analog(ANALOG_LEFT_Y) * 0.90); //just testing to make sure the correct side is adjusted
    LM.move(con.get_analog(ANALOG_LEFT_Y) * 0.90);
    LB.move(con.get_analog(ANALOG_LEFT_Y) * 0.90);
}

void flywheelSpin(){
    FW.move(103);
}

void revFlywheel(){
	FW.move(-60);
}

void intake(){
    intakeMotor.move(-120);
}

void indexer(){
    intakeMotor.move(103);
}

void driverFlywheel(){
    //bool buttonA; //why are we still using A if the button is R2 lol

    if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
		buttonR2 = !buttonR2;

	    if(buttonR2){
			flywheelSpin();
            con.clear();
			con.print(0, 0, "flywheel ON");
			//con.clear();
		}
			
		else if(!buttonR2){
			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
			FW.brake();
            con.clear();
			con.print(0, 0, "flywheel OFF");
		}

	}
}

void flywheelUnstuck(){
	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
		buttonL2 = !buttonL2;

	    if(buttonL2){
			revFlywheel;
		}
			
		else if(!buttonL2){
			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
			FW.brake();
		}

	}
}

void driverIntake(){
    if(con.get_digital(E_CONTROLLER_DIGITAL_L1))
		indexer();

	else if(con.get_digital(E_CONTROLLER_DIGITAL_R1))
		intake();
	
	else{
		intakeMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
		intakeMotor.brake();
	}

	}

void expansion(){

	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){ //possibly add time conditions as well
		if(launch == 0){
			launch++;
		}
		else if(launch == 1){
			pistonL.set_value(HIGH);
			pistonR.set_value(HIGH);
			pistonT.set_value(HIGH);
			launch ++;
		}
	}
}

void angler(){
	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
		angle = !angle;
	}

	if(angle){
		pistonA.set_value(HIGH);
	}

	else if(!angle){
		pistonA.set_value(LOW);
	}
}

#endif