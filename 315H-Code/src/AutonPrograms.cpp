#include "main.h"
#include "pros/llemu.hpp"

const int CUTOFF_TIME = 11200;    

//auton programs

/** ============================================
 * @brief 
 * Red side autons
 */
void nearSideRed9() {
    int testTimer = pros::millis();
    //shooting
    runPunchTask();
    //runRollerTask();
    puncher.tare_position();
    farPrimeBtn = true;
    pros::delay(2000);
    roller.move(120);
    pros::delay(1500);
    roller.move(0);
    shootBtn = true;
    pros::delay(500);

    //spin roller
    leftDrive.move(-40);
    rightDrive.move(-40);
    pros::delay(800);
    roller.move(50); //1 for want red
    //intake(400);
    pros::delay(500);
    roller.move(0);
    drivebase.goForTime(40, 200); 
    
    
    //pros::delay(5000); 
    //return;
    // runRollerTask();
    // runPunchTask();

    // roller.move(120);
    
    // //spin roller
    // farPrimeBtn = true;
    // optRoller.set_led_pwm(75);
    // spinRollerRed();
    // pros::delay(1000);
    // roller.move(0);

    // //fire preload discs
    // drivebase.driveDistance(true, 3, 0, 45);
    // shootBtn = true;
    // pros::delay(500);
    // farPrimeBtn = true;

    //intake three discs
    puncher.tare_position();
    twoDiscBtn = true;
    drivebase.turnPID(58, 90);
    roller.move(127);
    drivebase.driveDistance(true, 24, 58, 70);
    pros::delay(500);
    drivebase.driveDistance(true, 37, 58, 50);
    pros::delay(100);
    roller.move(0);
    
    //turn 90 degrees and shoot discs
    drivebase.turnPID(-103, 90);
    drivebase.driveDistance(false, 3, -103, 30);
    pros::delay(100);
    roller.move(0);
    shootBtn = true;
    pros::delay(500);
    pros::lcd::clear();
    pros::lcd::print(0, "%d", pros::millis() - testTimer);
    // return;
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
    //while (!teleop) {
        
        //spin roller
        farPrimeBtn = true;
        optRoller.set_led_pwm(75);
        spinRollerRed();
        roller.move(120);
        pros::delay(1000);
        roller.move(0);

        //fire preload discs
        drivebase.driveDistance(true, 3, -2, 45);
        shootBtn = true;
        pros::delay(200);
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
        drivebase.driveDistance(false, 56, -90, 40);
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
    //runRollerTask();
    runPunchTask();

    //score preload
    puncher.tare_position();
    farPrimeBtn = true;
    pros::delay(1200);
    shootBtn = true;
    pros::delay(1000);
    //farPrimeBtn = true;

    //intake 3 discs (ram with outtake, then slowly intake)
    // drivebase.driveDistance(false, 6, 10, 60);
    // drivebase.turnPID(-55, 90);
    // roller.move(-120);
    // drivebase.driveDistance(true, 12, -100, 80);
    // roller.move(0);
    // pros::delay(400);
    // roller.move(120);
    // drivebase.driveDistance(true, 12, -100, 40);

    // //turn and shoot
    // drivebase.turnPID(90, 90);
    // shootBtn = true;

    //score roller
    //drivebase.driveDistance(false, 6, 90, 50);
    drivebase.turnPID(-110, 80);
    drivebase.driveDistance(false, 18, -110, 60);
    drivebase.turnPID(90, 90);
    //drivebase.driveDistance(false, 6, -45, 40);
    //spinRollerRed();
    leftDrive.move(-40);
    rightDrive.move(-40);
    pros::delay(1000);
    roller.move(60); //1 for want red
    //intake(400);
    pros::delay(500);
    roller.move(0);
    drivebase.goForTime(40, 150); 

    return; 
}

void farRollerRed(){
    //optRoller.set_led_pwm(50);

    drivebase.driveDistance(false, 18, 0, 40);
    drivebase.turnPID(90,90);
    leftDrive.move(-40);
    rightDrive.move(-40);
    spinRoller(1);
    roller.move(50); //1 for want red
    //intake(400);
    pros::delay(500);
    drivebase.goForTime(40, 300);

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
    //optRoller.set_led_pwm(50);
    drivebase.driveDistance(false, 18, 0, 40);
    drivebase.turnPID(90,90);
    leftDrive.move(-40);
    rightDrive.move(-40);
    pros::delay(800);
    roller.move(50); //1 for want red
    //intake(400);
    pros::delay(500);
    roller.move(0);
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

void nearSideBlue9() {
    runPunchTask();
    puncher.tare_position();
    farPrimeBtn = true;
    pros::delay(3000);
    roller.move(120);
    pros::delay(1500);
    roller.move(0);
    shootBtn = true;

    
    leftDrive.move(-40);
    rightDrive.move(-40);
    pros::delay(400);
    roller.move(50); //2 for want blue
    //intake(400);
    pros::delay(500);
    roller.move(0);
    drivebase.goForTime(40, 300);   
}

void farSideBlue5() {
    runRollerTask();
    runPunchTask();

    //score preload
    puncher.tare_position();
    farPrimeBtn = true;
    pros::delay(2000);
    roller.move(120);
    pros::delay(2000);
    roller.move(0);
    pros::delay(100);
    //drivebase.driveDistance(true, 12, 0, 60);
    //drivebase.turnPID(3, 90);
    shootBtn = true;
    pros::delay(1000);
    farPrimeBtn = true;

    //intake 3 discs (ram with outtake, then slowly intake)
    // drivebase.driveDistance(false, 6, 10, 60);
    // drivebase.turnPID(-55, 90);
    // roller.move(-120);
    // drivebase.driveDistance(true, 12, -100, 80);
    // roller.move(0);
    // pros::delay(400);
    // roller.move(120);
    // drivebase.driveDistance(true, 12, -100, 40);

    // //turn and shoot
    // drivebase.turnPID(90, 90);
    // shootBtn = true;

    //score roller
    //drivebase.driveDistance(false, 6, 90, 50);
    drivebase.turnPID(-92, 90);
    drivebase.driveDistance(false, 18, -92, 60);
    drivebase.turnPID(90, 90);
    //drivebase.driveDistance(false, 6, -45, 40);
    //spinRollerRed();
    leftDrive.move(-40);
    rightDrive.move(-40);
    pros::delay(400);
    roller.move(50); //1 for want red
    //intake(400);
    pros::delay(500);
    roller.move(0);
    drivebase.goForTime(40, 300); 

    return;
    
    // runRollerTask();
    // runPunchTask();

    // //score preload
    // farPrimeBtn = true;
    // drivebase.driveDistance(true, 12, 0, 60);
    // drivebase.turnPID(10, 90);
    // shootBtn = true;
    // farPrimeBtn = true;

    // //intake 3 discs (ram with outtake, then slowly intake)
    // drivebase.driveDistance(false, 6, 10, 60);
    // drivebase.turnPID(-55, 90);
    // roller.move(-120);
    // drivebase.driveDistance(true, 12, -100, 80);
    // roller.move(0);
    // pros::delay(400);
    // roller.move(120);
    // drivebase.driveDistance(true, 12, -100, 40);

    // //turn and shoot
    // drivebase.turnPID(90, 90);
    // shootBtn = true;

    // //score roller
    // drivebase.driveDistance(false, 6, 90, 50);
    // drivebase.turnPID(-90, 90);
    // drivebase.driveDistance(false, 56, -90, 60);
    // drivebase.turnPID(-45, 90);
    // //drivebase.driveDistance(false, 6, -45, 40);
    // //spinRollerRed();
    // leftDrive.move(-40);
    // rightDrive.move(-40);
    // spinRoller(1);
    // leftDrive.move(40);
    // rightDrive.move(40);

    // return;
}

void elimPrepBlue() {
    spinRollerBlue();
    prime(300);
    fire();

}

void autonSkills() {
    //nothing here yet
}