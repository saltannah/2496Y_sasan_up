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
	imu.reset();
	while(imu.is_calibrating()){
		delay(5);
	}
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
void competition_initialize() {
	imu.reset();
	while(imu.is_calibrating()){
		delay(5);
	}
}

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
//close roller side: one roller, attempts five discs
	FW.move_velocity(523);
	drivePID(47);//45 47
	//delay(700);
	roller();
	delay(500);
	drivePID(-90);
	//delay(500);
	autonTurn(-11);
	//delay(500);
	drivePID(-160);
	delay(800);
	
	//shooting
	intakeMotor.move(-127);
	delay(300);
	intakeMotor.brake();
	FW.move_velocity(535);
	delay(1100);
	intakeMotor.move(-127);
	delay(500);
	//

	//intakeMotor.brake();
	newTurn(-115);
	intakeMotor.move(127);
	intakePistoon.set_value(LOW);
	drivePID(350);
	delay(500);
	intakePistoon.set_value(HIGH);
	delay(1500);
	newTurn(99);
	FW.move_velocity(510);
	drivePID(-160);

	//shooting
	intakeMotor.move(-127);
	delay(300);
	intakeMotor.brake();
	FW.move_velocity(515);
	delay(1100);
	intakeMotor.move(-127);
	delay(300);
	intakeMotor.brake();
	FW.move_velocity(520);
	delay(1100);
	intakeMotor.move(-127);
	delay(300);
	//

//far roller side: shoot two discs and then go for the roller (hopefully we have enough time)
	// intakeMotor.move(127);
	// drivePID(200);
	// newTurn(130);

	// //shooting
	// intakeMotor.move(-127);
	// delay(300);
	// intakeMotor.brake();
	// FW.move_velocity(515);
	// delay(1100);
	// intakeMotor.move(-127);
	// delay(300);
	// intakeMotor.brake();
	// FW.move_velocity(520);
	// delay(1100);
	// intakeMotor.move(-127);
	// delay(300);
	// //

	// newTurn(50);
	// drivePID(450);
	// newTurn(40);
	// drivePID(50);
	// roller();
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
	//con.clear();
	imu.reset();
	while(imu.is_calibrating()){
		con.print(0, 0, "calibrating...");
		delay(5);
	}
	con.clear();
	delay(5);

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
	flywheelSlow();
	expansion();
	angler();
	intakeHeight();

	if(con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
		FW.move_velocity(525);
		drivePID(47);//45 47
		//delay(700);
		roller();
		delay(500);
		drivePID(-90);
		//delay(500);
		autonTurn(-11);
		//delay(500);
		drivePID(-160);
		delay(800);
		
		//shooting
		intakeMotor.move(-127);
		delay(300);
		intakeMotor.brake();
		FW.move_velocity(535);
		delay(1000);
		intakeMotor.move(-127);
		delay(500);
		//

		//intakeMotor.brake();
		newTurn(-115);
		intakeMotor.move(127);
		intakePistoon.set_value(LOW);
		FW.move_velocity(480);
		drivePID(350);
		delay(500);
		intakePistoon.set_value(HIGH);
		delay(1500);
		newTurn(99);
		drivePID(-160);

		//shooting
		intakeMotor.move(-127);
		delay(300);
		intakeMotor.brake();
		FW.move_velocity(485);
		delay(1100);
		intakeMotor.move(-127);
		delay(300);
		intakeMotor.brake();
		FW.move_velocity(490);
		delay(1100);
		intakeMotor.move(-127);
		delay(300);
		//


	

	}
	//testPID(); //button A for testing pid turns

	pros::delay(5);
	}
}
