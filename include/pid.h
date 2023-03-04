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

void chassis_stop(){
    RF.move(0);
    RM.move(0);
    RB.move(0);
    LF.move(0);
    LM.move(0);
    LB.move(0);
}

void drivePID(int target){ //1.03 rev = approx 927 encoder units = 1 tile
    float error = 0;
    float prevError = 0;
    float integral = 0;
    float derivative = 0;
    float kP;
    float kI;
    float kD;
    float power;
    int counter = 0;

    kP = 1; //started with 1
    kI = 0;
    kD = 0;

    resetEncoder();
    error = target;


    while(abs(error) > 8){ //change condition
    int currPos = (RF.get_position() + RB.get_position()) / 2;
    error = target - currPos;
    integral = integral + error;

    // if(error <= 0){ //set conditions later
    //     integral = 0;
    // }

    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    
    //int yes = 1;

    //drivePID(power);
    drive(power);

    /*if (error < 3){
        counter = counter + 1;
    }*/

    //con.print(0,0,yes);
    delay (10);
    con.print(0, 0, "error: %f", error);
    con.print(0, 0, "LM %d", target - LM.get_position());
    con.print(0, 5, "RM %d", target - RM.get_position());
    }
    chassis_stop();
}

void rollerDrive(int target){ //1.03 rev = approx 927 encoder units = 1 tile
    float error = 0;
    float prevError = 0;
    float integral = 0;
    float derivative = 0;
    float kP;
    float kI;
    float kD;
    float power;
    int counter = 0;

    kP = 1; //started with 1
    kI = 0;
    kD = 0;

    resetEncoder();
    error = target;


    while(counter < 1500){ //change condition
    int currPos = (RF.get_position() + RB.get_position()) / 2;
    error = target - currPos;
    integral = integral + error;

    // if(error <= 0){ //set conditions later
    //     integral = 0;
    // }

    derivative = error - prevError;
    prevError = error;
    power = error*kP + integral*kI + derivative*kD;
    
    //int yes = 1;

    //drivePID(power);
    drive(power);

    /*if (error < 3){
        counter = counter + 1;
    }*/

    //con.print(0,0,yes);
    delay (10);
    con.print(0, 0, "error: %f", error);
    con.print(0, 0, "LM %d", target - LM.get_position());
    con.print(0, 5, "RM %d", target - RM.get_position());
    counter += 10;
    }
    chassis_stop();
}

void newTurn(double degrees){
    int localTime = 0;
    bool negdeg;
   	if(degrees < 0)
   	{
   		imu.set_heading(359);
        degrees ++;
   	}
   	else    
   	{
   		imu.set_heading(0);//10
   	}

    float kP = 4.457; //1.78 1.85 2.7 3.5 *[4, heading: 90.174]* [3.95] [3.8] [3.78] [3.5] [sasan left off on .935]
    //[2.5] 2.58 2.68 4.25  *4.3* 4.45
   	float kI = 0.00;//
   	float kD = 0.26; //0.07 0.05 0.19 0.27 *0.25*
   	double target = imu.get_heading() + degrees;
   	double error = target - imu.get_heading(); // -90
   	double lastError = error;
   	int power = 0;
    int powerAdj;
   	double integral = 0.0;
   	double derivative = 0.0;
    int time = 0;
    int count = 0;
    int errMet = 0;


    while(count < 2000){//abs(error) > 0.5 && errMet < 5000
        error = target - imu.get_heading();
        integral += error / 200;
        /*
        if(abs(integral) >= 600){
        integral = 0;
        }
        */
        derivative = (error - lastError) * 200; //200
        power = error * kP + integral * kI + derivative *kD;
        lastError = error;
        LF.move(power); LM.move(power); LB.move(power); RF.move(-power); RM.move(-power); RB.move(-power);

        // if(count % 100 == 0){
        //     con.print(1, 0, "heading: %f", imu.get_heading());
        //     //con.print(1, 0, "power: %f", power);
        // }

        // else if (count % 50 == 0) {
        //     con.print(0, 0, "error: %f", error);
        // }


        count += 5;
        delay(5);
    }

    chassis_stop();
}

void autonTurn(double degrees){
    int localTime = 0;
    bool negdeg;
   	if(degrees < 0)
   	{
   		imu.set_heading(359);
        degrees ++;
   	}
   	else    
   	{
   		imu.set_heading(0);//10
   	}

    float kP = 4.457; //1.78 1.85 2.7 3.5 *[4, heading: 90.174]* [3.95] [3.8] [3.78] [3.5] [sasan left off on .935]
    //[2.5] 2.58 2.68 4.25  *4.3* 4.45
   	float kI = 0.00;//
   	float kD = 0.26; //0.07 0.05 0.19 0.27 *0.25*
   	double target = imu.get_heading() + degrees;
   	double error = target - imu.get_heading(); // -90
   	double lastError = error;
   	int power = 0;
    int powerAdj;
   	double integral = 0.0;
   	double derivative = 0.0;
    int time = 0;
    int count = 0;
    int errMet = 0;


    while(count < 1000){//abs(error) > 0.5 && errMet < 5000
        error = target - imu.get_heading();
        integral += error / 200;
        /*
        if(abs(integral) >= 600){
        integral = 0;
        }
        */
        derivative = (error - lastError) * 200; //200
        power = error * kP + integral * kI + derivative *kD;
        lastError = error;
        LF.move(power); LM.move(power); LB.move(power); RF.move(-power); RM.move(-power); RB.move(-power);

        // if(count % 100 == 0){
        //     con.print(1, 0, "heading: %f", imu.get_heading());
        //     //con.print(1, 0, "power: %f", power);
        // }

        // else if (count % 50 == 0) {
        //     con.print(0, 0, "error: %f", error);
        // }


        count += 5;
        delay(5);
    }

    chassis_stop();
}

#endif