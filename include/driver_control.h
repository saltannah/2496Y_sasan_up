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

void chassisFwd(){
	RF.move(con.get_analog(ANALOG_RIGHT_Y));
    RM.move(con.get_analog(ANALOG_RIGHT_Y));
    RB.move(con.get_analog(ANALOG_RIGHT_Y));

    LF.move(con.get_analog(ANALOG_LEFT_Y));
    LM.move(con.get_analog(ANALOG_LEFT_Y));
    LB.move(con.get_analog(ANALOG_LEFT_Y));
}

#endif