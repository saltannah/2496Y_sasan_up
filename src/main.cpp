#include "main.h"
#include "robot.h"
#include "driver_control.h"
#include "autonomous.h"
#include "pid.h"
#include <cmath>

using namespace pros;
using namespace std;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//flywheelSpin(); instead use:
	//FW.move(127);

	timeDrive(60, 150);
	delay(800);
	roller();
	delay(1000);
	//FW.move(100);
	FW.move(127);
	delay(500);
	/*
	timeDrive(-60, 300);
	delay(300);
	jankRight(400);
	delay(1000);
	intakeMotor.move(-100);
	delay(1000);
	indexerBrake();
	flywheelBrake();
	*/
	
	timeDrive(-60, 260);
	delay(1000);
	jankLeft(70);//115 with only one side
	delay(500);
	timeDrive(-60, 200);
	delay(1500);//wazzuuuuup!!!!!!
	//indexer(); instead trying:
	intakeMotor.move(-120);
	delay(210);
	indexerBrake();//you're not sasan, I'm Gerald!!
	delay(1000);
	intakeMotor.move(-120);
	delay(400);//
	indexerBrake();
	flywheelBrake();


}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// pistonL.set_value(LOW);
	// pistonR.set_value(LOW);
	// pistonT.set_value(LOW);
	while (true){
	chassis();
	/* just for testing
	RF.move(con.get_analog(ANALOG_RIGHT_Y));
    RM.move(con.get_analog(ANALOG_RIGHT_Y));
    RB.move(con.get_analog(ANALOG_RIGHT_Y));

    LF.move(con.get_analog(ANALOG_RIGHT_Y) * 0.90);
    LM.move(con.get_analog(ANALOG_RIGHT_Y) * 0.90);
    LB.move(con.get_analog(ANALOG_RIGHT_Y) * 0.90);
	*/
	driverIntake();
	driverFlywheel();
	expansion();
	angler();

	pros::delay(5);
	}
}
