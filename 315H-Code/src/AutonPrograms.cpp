#include "DrivebaseControl.hpp"
#include "main.h"
#include "pros/llemu.hpp"

const int CUTOFF_TIME = 11200;    

//auton programs
void soloWinPointRed()
{
    leftDrive.move(-50);
    rightDrive.move(-50);
    spinRoller(1); //1 for want red
    //intake(400);
    pros::delay(500);
    leftDrive.move(0);
    rightDrive.move(0);

    drivebase.driveDistance(true, 6, 0);
    drivebase.turnPID(45, 90);
    drivebase.driveDistance(true, 67 /*tune*/, 0);
    drivebase.turnPID(-90, 90);
    fire();
    intake();
    fire();
    drivebase.turnPID(90, 90);
    drivebase.driveDistance(true, 67, 0);
    drivebase.turnPID(45, 90);

    /*
    
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void soloWinPointBlue()
{
    pros::lcd::initialize();
    drivebase.turnPID(90, 90);


    /*
    leftDrive.move(100);
    rightDrive.move(100);
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}