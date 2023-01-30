#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "robot.h"
using namespace pros;

    //none of the ports are correct
    
    //chassis
	pros::Motor RF (13, E_MOTOR_GEARSET_18, false);
    pros::Motor RM (3, E_MOTOR_GEARSET_18, false);
	pros::Motor RB (5, E_MOTOR_GEARSET_18, false);

	pros::Motor LF (14, E_MOTOR_GEARSET_18, true);
    pros::Motor LM (14, E_MOTOR_GEARSET_18, true);
	pros::Motor LB (12, E_MOTOR_GEARSET_18, true);

	//intake
	pros::Motor intake (11, E_MOTOR_GEARSET_06, false);

	//flywheel
	pros::Motor FW (10, E_MOTOR_GEARSET_06, false);

	//pneumatics
	pros::ADIDigitalOut pistonL(1, LOW);
	pros::ADIDigitalOut pistonT(5, LOW);
	pros::ADIDigitalOut pistonR(2, LOW);

	//IMU
	pros::Imu imu (8); //change port it's just temp

	//controller
	pros::Controller con (CONTROLLER_MASTER);
