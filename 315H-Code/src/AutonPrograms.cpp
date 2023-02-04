#include "main.h"
#include "pros/llemu.hpp"

const int CUTOFF_TIME = 11200;    

//auton programs

/** ============================================
 * @brief 
 * Red side autons
 */
void nearSideRed9() {
    runRollerTask();
    runPunchTask();
    
    //spin roller
    farPrimeBtn = true;
    spinRollerRed();

    //fire preload discs
    drivebase.driveDistance(true, 3, 0, 45);
    shootBtn = true;
    pros::delay(500);
    farPrimeBtn = true;

    //intake three discs
    drivebase.turnPID(45, 90);
    roller.move(120);
    drivebase.driveDistance(true, 56, 45, 60);
    roller.move(0);
    
    //turn 90 degrees and shoot discs
    drivebase.turnPID(-90, 90);
    shootBtn = true;
    
    return;
}

void soloWinPointRed()
{
    runRollerTask();
    runPunchTask();
    /*
    spin roller

    shoot discs
    intake three discs
    shoot discs
    score end roller
    */

    //spin roller until color sensor detects blue
    spinRollerRed();
    farPrimeBtn = true;

    //fire preload discs
    drivebase.driveDistance(true, 3, 0, 45);
    shootBtn = true;
    farPrimeBtn = true;

    //intake three discs
    drivebase.turnPID(45, 90);
    roller.move(120);
    drivebase.driveDistance(true, 56, 45, 60);
    roller.move(0);
    
    //turn 90 degrees and shoot discs
    drivebase.turnPID(-90, 90);
    shootBtn = true;

    //score end roller
    drivebase.turnPID(-90, 90);
    drivebase.driveDistance(false, 56, 90, 40);
    drivebase.turnPID(45, 90);
    drivebase.driveDistance(false, 3, 45, 40);
    spinRollerRed();
    return;

    // spinRollerRed();
    // pros::delay(1000);
    // //drivebase.driveDistance(true, 3, 0, 40);
    // roller.move(-120);
    // pros::delay(250);
    // roller.move(0);
    // prime(300);
    // drivebase.turnPID(44, 90);
    // drivebase.driveDistance(true, 52 /*tune*/, 45, 60);
    // drivebase.turnPID(-90, 90);
    // drivebase.driveDistance(true, 3, -90, 60);
    // fire();
    // prime(1500);
    // //intake(500); intake for 500 ms
    // roller.move(120);
    // pros::delay(1500);
    // roller.move(0);
    // prime(1500);
    // fire();
    // drivebase.turnPID(90, 90);
    // drivebase.driveDistance(true, 56, 90, 40);
    // drivebase.turnPID(-135, 90);
    // drivebase.driveDistance(true, -7, -135, 40);
    // spinRollerRed();

    // return;

    /*
    
    pros::delay(250);
    leftDrive.move(0);
    rightDrive.move(0);*/
    
    //drivebase.turnPID(90);
}

void farSideRed5() {
    runRollerTask();
    runPunchTask();

    //score preload
    farPrimeBtn = true;
    drivebase.driveDistance(true, 12, 0, 60);
    drivebase.turnPID(10, 90);
    shootBtn = true;
    farPrimeBtn = true;

    //intake 3 discs (ram with outtake, then slowly intake)
    drivebase.driveDistance(false, 6, 10, 60);
    drivebase.turnPID(-55, 90);
    roller.move(-120);
    drivebase.driveDistance(true, 12, -100, 80);
    roller.move(0);
    pros::delay(400);
    roller.move(120);
    drivebase.driveDistance(true, 12, -100, 40);

    //turn and shoot
    drivebase.turnPID(90, 90);
    shootBtn = true;

    //score roller
    drivebase.driveDistance(false, 6, 90, 50);
    drivebase.turnPID(-90, 90);
    drivebase.driveDistance(false, 56, -90, 60);
    drivebase.turnPID(-45, 90);
    drivebase.driveDistance(false, 6, -45, 40);
    spinRollerRed();

    return;
    
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
    phase = 3;
    prime();
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