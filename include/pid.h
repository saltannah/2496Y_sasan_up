#ifndef PID_H
#define PID_H

#include "main.h"
#include "robot.h"
#include <cmath>
using namespace std;
using namespace pros;

//PID variables


void resetEncoder(){
    RF.tare_position();
    RM.tare_position();
    RB.tare_position();
    LF.tare_position();
    LM.tare_position();
    LB.tare_position();
}

void drive(int power){
    RF.move(power);
    RM.move(power);
    RB.move(power);
    LF.move(power);
    LM.move(power);
    LB.move(power);
}

#endif