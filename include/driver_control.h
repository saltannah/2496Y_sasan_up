#ifndef DRIVER_CONTROL
#define DRIVER_CONTROL

#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include "pid.h"
#include <cmath>
#include <ios>

using namespace pros;
using namespace std;

bool buttonR2;
bool buttonL2;
bool angle;
bool intakeAng;
bool flywheelOn;
bool slowFlywheel = false;
bool expand = false;
int launch = 0;
bool spamExpand = false;

void chassis(){
	RF.move(con.get_analog(ANALOG_RIGHT_Y));
    RM.move(con.get_analog(ANALOG_RIGHT_Y));
    RB.move(con.get_analog(ANALOG_RIGHT_Y));

    LF.move(con.get_analog(ANALOG_LEFT_Y) * 0.90); //just testing to make sure the correct side is adjusted
    LM.move(con.get_analog(ANALOG_LEFT_Y) * 0.90);
    LB.move(con.get_analog(ANALOG_LEFT_Y) * 0.90);
}

void flywheelSpin(){
    FW.move(114); //107 //100   //113 ///114
	//FW.move_velocity(480);
	//when changing remember to update flywheelLower
}

void flywheelSpinSlow(){
	//FW.move(102);
	FW.move_velocity(440);
}

void revFlywheel(){
	FW.move(-60);
}

void intake(){
    intakeMotor.move(-130); //-120  //127
}

void indexer(){
    intakeMotor.move(89);//103  95
}

void indexerBrake(){
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	intakeMotor.brake();
}

void flywheelBrake(){
	FW.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	FW.brake();
}


// void driverFlywheel(){
//     //bool buttonA; //why are we still using A if the button is R2 lol
// 	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
// 		slowFlywheel = !slowFlywheel;
// 	}

//     if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
// 		buttonR2 = !buttonR2;

// 	    if(buttonR2){
// 			flywheelOn = true;
// 			if(!slowFlywheel){
// 				flywheelSpin();
// 			}
// 			else if(slowFlywheel){
// 				flywheelSpinSlow();
// 			}
//             con.clear();
// 			con.print(0, 0, "flywheel ON");
// 			//con.clear();
// 		}
			
// 		else if(!buttonR2){
// 			flywheelOn = false;
// 			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
// 			FW.brake();
//             con.clear();
// 			con.print(0, 0, "flywheel OFF");
// 		}

// 	}
// }

void driverFlywheel(){
    //bool buttonA; //why are we still using A if the button is R2 lol

    if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
		buttonR2 = !buttonR2;

	    if(buttonR2){
			flywheelOn = true;
			flywheelSpin();
            con.clear();
			con.print(0, 0, "flywheel ON");
			//con.clear();
		}
			
		else if(!buttonR2){
			flywheelOn = false;
			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
			FW.brake();
            con.clear();
			con.print(0, 0, "flywheel OFF");
		}

	}
}

void flywheelSlow(){
		//CHANGE WHEN UPDATING FLYWHEEL SPEED
	if(flywheelOn == true){
		if(con.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
			FW.move(95);
		}
		else{
			FW.move(100);
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

// void expansion(){
// 	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){ //possibly add time conditions as well
// 		if(launch == 0){
// 			launch++;
// 			con.print(0, 0, "%d", launch);
// 		}
// 		else if(launch > 0){
// 			expand = !expand;
// 			if(!expand){
// 				expPiston.set_value(HIGH);
// 				//con.print(0, 0, "expansion");
// 			}
// 			else if(expand){
// 				expPiston.set_value(LOW);
// 			}
// 		}
// 	}
// }

void expansion(){
 	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){ //possibly add time conditions as well
 		if(spamExpand == false){
			expPiston.set_value(LOW);
			spamExpand = true;
			//launch++;
 		}
 		else if(spamExpand == true){
 			expPiston.set_value(HIGH);
 			//launch ++;
			spamExpand = false;
			con.print(0, 0, "expansion");
		}
	}
}


// void angler(){
// 	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
// 		angle = !angle;
// 	}

// 	if(angle){
// 		pistonAngler.set_value(HIGH);
// 		if(flywheelOn){
// 			FW.move(120); //120 117
// 		}
		
// 		else if(!flywheelOn){
// 			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
// 			FW.brake();
// 		}
		
// 	}


// 	else if(!angle){
// 		pistonAngler.set_value(LOW);
// 		if(flywheelOn){
// 			if(!slowFlywheel){
// 				flywheelSpin();
// 			}
// 			else if(slowFlywheel){
// 				flywheelSpinSlow();
// 			}
// 		}
// 		else if(!flywheelOn){
// 			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
// 			FW.brake();
// 		}

// 	}
// }

void angler(){
	if(con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)){
		angle = !angle;
	}

	if(angle){
		pistonAngler.set_value(HIGH);
		if(flywheelOn){
			FW.move(120);
		}
		
		else if(!flywheelOn){
			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
			FW.brake();
		}
		
	}


	else if(!angle){
		pistonAngler.set_value(LOW);
		if(flywheelOn){
			flywheelSpin();
		}
		else if(!flywheelOn){
			FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
			FW.brake();
		}
		
	}
}

void intakeHeight(){
	if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
		intakeAng = !intakeAng;
	}

	if(intakeAng){
		intakePistoon.set_value(LOW);
		con.print(0, 0, "intake up");
		
	}

	else if(!intakeAng){
		intakePistoon.set_value(HIGH);

	}
}

void testPID(){
	if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
		// con.clear();
		// delay(5);
		newTurn(-90);
		delay(50);
		con.print(0,0,"all done");
	}
}



#endif