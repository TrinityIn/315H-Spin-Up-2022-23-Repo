#include "main.h"

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

    
    /*
    
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void soloWinPointBlue()
{
    intake(500);

    /*
    leftDrive.move(100);
    rightDrive.move(100);
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}