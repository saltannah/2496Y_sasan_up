#ifndef ROBOT_H
#define ROBOT_H

#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"

//chassis
extern pros::Motor RF;
extern pros::Motor RM;
extern pros::Motor RB;

extern pros::Motor LF;
extern pros::Motor LM;
extern pros::Motor LB;

//intake
extern pros::Motor intakeMotor;

//flywheel
extern pros::Motor FW;

//pneumatics
extern pros::ADIDigitalOut pistonL;
extern pros::ADIDigitalOut pistonT;
extern pros::ADIDigitalOut pistonR;
extern pros::ADIDigitalOut pistonA;

//IMU
extern pros::IMU imu;

//controller
extern pros::Controller con;
#endif
