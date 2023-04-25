#ifndef __AUTON__
#define __AUTON__

#include "main.h"
#include "global.h"
#include "pid.h"
#include "aut_func.h"
#include "lib/auton_obj.h"
#include <vector>
#include <string>

using namespace pros;
using namespace pid;
using namespace glb;
using namespace auf;


void none()
{
}

void test_shoot()
{
    fw_spin(990);//470, 690
    delay(8500);
    //pid_index();
    //shoot(1, -75);
    intake.move_velocity(600);
    delay(250);
    intake.move_velocity(0);
    delay(7000);
    intake.move_velocity(600);
    //shoot(1);
    //pid_index();
    //shoot(2);

    // fw_spin(-127);
	// delay(1000);
	// intake.move(110);
}

void turns()
{
    turn(5);
    turn_to(0);
    turn_to(90);
    turn_to(0);
    turn_to(180);
    turn_to(21);
}

void nml_half_awp()
{
    arc_turn(180, 300);
}

void ml_half_awp()
{
    drive_const(150, 80, 100);
    intake_dist(-300);
    delay(300);
    fw_spin(500);
    intake_dist(300);
    drive(-300, 1500);
    turn_to(-13, 1400);
    delay(300);
    shoot(2);
    turn_to(-130);
    intakeP.set(true);
    drive(900);
    fw_spin(450);
    intake_vel();
    intakeP.set(false);
    drive_const(200, 60, 1500);
    drive(400);
    turn_to(-29);
    drive(-350);
    index(3);
    arc_turn(180-24, 345, 1500);
    fw_spin(450);
    intakeP.set(true);
    drive(700);
    intakeP.set(false);
    intake_vel();
    delay(500);
    turn_to(-13.5);
    index(3);
}

void solo_awp()
{

}

void testing()
{
    fw_spin(500);
}

// AUTON LIST: CREATE AUTON OBJECTS WITH (NAME, FUNCTION) AS PARAMETERS TO BE USED IN AUTON SELECTOR
std::vector<Auton> autons
{
    Auton("none", none),
    Auton("testing", testing),
    Auton("test shoot", test_shoot),
    Auton("turns", turns),
    Auton("solo awp", solo_awp),
    Auton("ml half awp", ml_half_awp),
    Auton("nml half awp", nml_half_awp),
};


#endif