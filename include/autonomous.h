#ifndef AUTONOMOUS
#define AUTONOMOUS

//#include "autonomous.h"
#include "driver_control.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"
#include "pid.h"
#include <cmath>
#include <ios>

using namespace pros;
using namespace std;

void flywheelStop(){
    FW.set_brake_mode(E_MOTOR_BRAKE_COAST);
	FW.brake();
}

void chassisBrake(){
    /*
    RF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    LF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    */
    RF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    RM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    RB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    LF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    RF.brake();
    RM.brake();
    RB.brake();

    LF.brake();
    LM.brake();
    LB.brake();
}

void timeDrive(int speed, int driveFor){
    RF.move(speed);
    RM.move(speed);
    RB.move(speed);

    LF.move(speed); //just testing to make sure the correct side is adjusted
    LM.move(speed);
    LB.move(speed);

    delay(driveFor);

    chassisBrake();
}

void jankRight(int turnFor){
    LF.move(65); //just testing to make sure the correct side is adjusted
    LM.move(65);
    LB.move(65);
    RF.move(-65); //just testing to make sure the correct side is adjusted
    RM.move(-65);
    RB.move(-65);
    delay(turnFor);
    LF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LF.brake();
    LM.brake();
    LB.brake();
    RF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RF.brake();
    RM.brake();
    RB.brake();

}

void jankLeft(int turnFor){
    RF.move(65); //just testing to make sure the correct side is adjusted
    RM.move(65);
    RB.move(65);
    LF.move(-65); //just testing to make sure the correct side is adjusted
    LM.move(-65);
    LB.move(-65);
    delay(turnFor);
    RF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    RF.brake();
    RM.brake();
    RB.brake();
    LF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LF.brake();
    LM.brake();
    LB.brake();

}

void roller(){
    intakeMotor.move(-100);
    delay(300);
    intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeMotor.brake();
}

#endif