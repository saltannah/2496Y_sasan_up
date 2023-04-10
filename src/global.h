#ifndef __GLOBAL__
#define __GLOBAL__

#include "main.h"
#include "lib/piston.h"
#include "lib/chassis.h"
#include "lib/auton_obj.h"


namespace glb
{
    // ports ===============================
    #define P_BL 13
    #define P_ML 12
    #define P_FL 11
    #define P_BR 9
    #define P_MR 17
    #define P_FR 8

    #define P_FLY 10
    #define P_INTAKE 14

    #define P_INTAKE_P 'D'
    #define P_ANGLE_P 'C'
    #define P_EXPANSION_P 'G'
    #define P_IMU 21

    // objects =============================
    pros::Controller con(pros::E_CONTROLLER_MASTER);
    pros::Motor flywheel(P_FLY, pros::E_MOTOR_GEARSET_06, true);
    pros::Motor intake(P_INTAKE, pros::E_MOTOR_GEARSET_06, true);
    pros::Imu imu(P_IMU);

    Piston intakeP(P_INTAKE_P);
    Piston angleP(P_ANGLE_P, false, true);
    Piston expansionP(P_EXPANSION_P);
    Chassis chas({P_FL, -P_ML, P_BL}, {P_FR, -P_MR, P_BR}, pros::E_MOTOR_GEARSET_18, false);
    Auton *auton;
}

#endif