#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "robot.h"
using namespace pros;

    //none of the ports are correct
    
    //chassis
	pros::Motor RF (8, E_MOTOR_GEARSET_18, false);
    pros::Motor RM (17, E_MOTOR_GEARSET_18, true);
	pros::Motor RB (9, E_MOTOR_GEARSET_18, false);

	pros::Motor LF (11, E_MOTOR_GEARSET_18, true);
    pros::Motor LM (12, E_MOTOR_GEARSET_18, false);
	pros::Motor LB (13, E_MOTOR_GEARSET_18, true);

	//intake
	pros::Motor intakeMotor (14, E_MOTOR_GEARSET_06, false); 

	//flywheel
	pros::Motor FW (15, E_MOTOR_GEARSET_06, true);

	//pneumatics
	pros::ADIDigitalOut pistonL(1, LOW);
	pros::ADIDigitalOut pistonT(5, LOW);
	pros::ADIDigitalOut pistonR(2, LOW);
	pros::ADIDigitalOut expPiston(7, LOW);
	pros::ADIDigitalOut pistonA(3, LOW);

	//IMU
	pros::Imu imu (21); //change port it's just temp

	//controller
	pros::Controller con (CONTROLLER_MASTER);
