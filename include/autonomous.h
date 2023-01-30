#ifndef AUTONOMOUS
#define AUTONOMOUS

//#include "autonomous.h"
#include "driver_control.h"
#include "main.h"
#include "pros/misc.h"
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

#endif