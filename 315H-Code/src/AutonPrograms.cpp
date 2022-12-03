#include "main.h"

const int CUTOFF_TIME = 11200;    

//auton programs
void soloWinPointRed(Drivebase drivebase)
{
    intake(500);


    leftDrive.move(100);
    rightDrive.move(100);
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);
    
    //drivebase.turnPID(90);
}