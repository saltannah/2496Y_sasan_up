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


    while(true){ //change condition
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
    con.print(0, 0, "LM %d", target - LM.get_position());
    con.print(0, 5, "RM %d", target - RM.get_position());
    }
}

void newTurn(double degrees){
    int localTime = 0;
   	if(degrees < 0)
   	{
   		imu.set_heading(350);
   	}
   	else    
   	{
   		imu.set_heading(0);//10
   	}

    float kP = 2.9; //1.78
   	float kI = 0.0;//
   	float kD = 0.0; 
   	double target = imu.get_heading() + degrees;
   	double error = target - imu.get_heading(); // -90
   	double lastError = error;
   	int power = 0;
    int powerAdj;
   	double integral = 0.0;
   	double derivative = 0.0;
    int time = 0;
    int count = 0;
    int count2 = 0;


    while(abs(error) > 0.5){
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
        
        con.print(0, 0, "error: %f", error);

        // delay(50);
        // con.print(0, 0, "power: %d", power);
        // delay(50);
        // con.print(1, 1, "error: %f", error);
        // delay(50);
        // con.print(2, 2, "heading: %f", imu.get_heading());

        delay(10);
        //delay(150);
    }

    //chassis_stop();
    //con.print(1, 1, "heading: %f", imu.get_heading());
}

void imuTurn(double degrees) //left needs more power
   {
   	int localTime = 0;
   	if(degrees < 0)
   	{
   		imu.set_heading(350);
   	}
   	else    
   	{
   		imu.set_heading(10);
   	}

   	float kP = 6.0; //
   	float kI = 0.0;//
   	float kD = 0.0; 
   	double target = imu.get_heading() + degrees;
   	double error = target - imu.get_heading(); // -90
   	double lastError = error;
   	int power = 0;
    int powerAdj;
   	double integral = 0.0;
   	double derivative = 0.0;
    int time = 0;
    int count = 0;
    con.print(0, 0, "error %f", error);

   	while(abs(error) > 0.5){//abs(error) > 0.5 && time <= 6000){ //initially 0.5 & 2000 wait time   bs(error) > 0.08 || time <= 4000     3000 7:19
        //powerAdj = power * 0.1405; //10/21/22: 0.1405 (turns a very tiny amount in only one direction (lined up straight just a little back farher than it should be))        0.141 <= seems good 10/19 <= 0.140(shifts much less but still a small bit in both directions)     10/18 values tested: .149, .142, .13, .127, .125, .11, .1, .05, .03 (all value changes to the right) (still shifts a little in both axis)
   		powerAdj = 0;
        con.print(0, 0, "error %f", error);
        if(count%50 == 0) {
            con.print(0, 0, "currHeading: %d", imu.get_heading());
        }
        error = target - imu.get_heading();
        /*
        if (error > 0.03){
            count++
        }
        */
   		//if(abs(error) < 15) 
        integral += error / 200;
   		derivative = (error - lastError) * 200;
   		power = error * kP + integral * kI + derivative * kD;
   		lastError = error;
   		LF.move(power); LM.move(power), LB.move(power); RF.move(- (power + powerAdj)); RM.move(-(power + powerAdj)), RB.move(- (power + powerAdj));
   		count++;
        delay(10);//5
        //con.print(0, 0, "err: %lf", error);
        //con.print(0, 0, "err: %d", time);
        //time += 5;
    }
   	chassis_stop();
   }


#endif