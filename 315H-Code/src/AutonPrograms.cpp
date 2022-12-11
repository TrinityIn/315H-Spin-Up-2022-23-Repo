#include "main.h"
#include "pros/llemu.hpp"

const int CUTOFF_TIME = 11200;    

//auton programs

/** ============================================
 * @brief 
 * Red side autons
 */
void soloWinPointHalfRed() {
    spinRollerRed();
    
    drivebase.driveDistance(true, 6, 0, 40);
    roller.move(-120);
    pros::delay(250);
    roller.move(0);
    prime(300);
    drivebase.turnPID(45, 90);
    drivebase.driveDistance(true, 56 /*tune*/, 45, 60);
    drivebase.turnPID(-90, 90);
    
    fire();
    prime(1500);
    //intake(500); intake for 500 ms
    roller.move(120);
    pros::delay(500);
    roller.move(0);
    fire();
}

void soloWinPointRed()
{
    spinRollerRed();
    pros::delay(1000);
    //drivebase.driveDistance(true, 3, 0, 40);
    roller.move(-120);
    pros::delay(250);
    roller.move(0);
    prime(300);
    drivebase.turnPID(44, 90);
    drivebase.driveDistance(true, 52 /*tune*/, 45, 60);
    drivebase.turnPID(-90, 90);
    drivebase.driveDistance(true, 3, -90, 60);
    fire();
    prime(1500);
    //intake(500); intake for 500 ms
    roller.move(120);
    pros::delay(1500);
    roller.move(0);
    prime(1500);
    fire();
    drivebase.turnPID(90, 90);
    drivebase.driveDistance(true, 56, 90, 40);
    drivebase.turnPID(-135, 90);
    drivebase.driveDistance(true, -7, -135, 40);
    spinRollerRed();

    return;

    /*
    
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void farRollerRed(){
    drivebase.driveDistance(true, 17, 0, 40);
    drivebase.turnPID(-90,90);
    spinRollerRed();

}

void spinRollerRed(){
    leftDrive.move(-40);
    rightDrive.move(-40);
    //intake(400);
    pros::delay(500);   
    spinRoller(1); //1 for want red
    
    drivebase.goForTime(50, 250);
    
}

/** ============================================
 * @brief 
 * Blue side autons
 */
void soloWinPointHalfBlue()
{
    spinRollerBlue();
    pros::delay(1000);
    drivebase.driveDistance(true, 3, 0, 40);
    roller.move(-120);
    pros::delay(250);
    roller.move(0);
    prime(300);
    drivebase.turnPID(46, 90);
    drivebase.driveDistance(true, 44 /*tune*/, 45, 60);
    drivebase.turnPID(-85, 90);
    drivebase.driveDistance(true, 3, -90, 60);
    fire();
    prime(1500);
    //intake(500); intake for 500 ms
    roller.move(120);
    pros::delay(1500);
    roller.move(0);
    prime(1500);
    fire();

    return;

    /*
    
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void soloWinPointBlue()
{
    pros::lcd::initialize();
    //drivebase.turnPID(45, 90);
    leftDrive.move(-50);
    rightDrive.move(-50);
    spinRoller(2); //1 for want red
    //intake(400);
    pros::delay(500);
    leftDrive.move(0);
    rightDrive.move(0);

    drivebase.driveDistance(true, 6, 0, 40);
    drivebase.turnPID(45, 90);
    drivebase.driveDistance(true, 67 /*tune*/, 45, 60);
    drivebase.turnPID(-90, 90);
    prime(1500);
    fire();
    //intake();
    fire();
    drivebase.turnPID(90, 90);
    drivebase.driveDistance(true, 67, 90, 40);
    drivebase.turnPID(45, 90);
    return;


    /*
    leftDrive.move(100);
    rightDrive.move(100);
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void farRollerBlue(){
    drivebase.driveDistance(true, 18, 0, 40);
    drivebase.turnPID(-90,90);
    leftDrive.move(-40);
    rightDrive.move(-40);
    spinRoller(2); //1 for want red
    //intake(400);
    pros::delay(500);
    drivebase.goForTime(40, 300);

}


void spinRollerBlue(){
    leftDrive.move(-40);
    rightDrive.move(-40);
    //intake(400);
    pros::delay(500);   
    spinRoller(2); //1 for want red
    
    drivebase.goForTime(50, 250);
}

void elimPrepBlue() {
    spinRollerBlue();
    prime(300);
    fire();

}