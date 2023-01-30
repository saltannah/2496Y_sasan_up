#ifndef PID_H
#define PID_H

#include "main.h"
#include "robot.h"
#include <cmath>
using namespace std;
using namespace pros;

//PID variables


void resetEncoder(){
    RF.set_zero_position(0);
    RB.set_zero_position(0);
    LF.set_zero_position(0);
    LB.set_zero_position(0);
}

#endif