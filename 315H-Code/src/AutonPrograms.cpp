#include "PuncherControl.hpp"
#include "RollerControl.hpp"
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
    runPunchTask();
    runRollerTask();
    while (!teleop) {
        

        //fire preload discs
        //drivebase.driveDistance(true, 3, -2, 45);
        //farPrimeBtn = true;
        //pros::delay(200);
        //momentumShot(0); //change if necessary to targetPosition

        //spin roller
        targetPosition = 6500; 
        leftDrive.move(-80);
        rightDrive.move(-40);
        pros::delay(100);
        spinRollerBtn = true;
        pros::delay(800);
        stopRollerBtn = true;
        drivebase.driveDistance(true, 6, -10, 50); 

        //delay
        //pros::delay(5000);

        //shoot preloads
        drivebase.turnPID(-10, 50);
        momentumShot(30);

        //intake three discs
        drivebase.turnPID(51, 90);
        spinRollerBtn = true;
        drivebase.driveDistance(true, 20, 51, 40); //knocking discs down
        pros::delay(250);
        drivebase.driveDistance(true, 17, 51, 25); //intaking discs
        pros::delay(800);
        stopRollerBtn = true;
        //drivebase.driveDistance(true, 7, 45, 60);
        
        //turn 90 degrees and shoot discs
        drivebase.turnPID(-91, 90);
        //drivebase.driveDistance(false, 3, -90, 30);
        pros::delay(100);
        momentumShot(40);

        //get second stack of discs
        spinRollerBtn = true;
        drivebase.turnPID(150, 90);
        drivebase.driveDistance(true, 34, 180, 40);
        drivebase.driveDistance(false, 34, 195, 50);
        stopRollerBtn = true;

        //shoot second stack of discs
        drivebase.turnPID(180, 90);
        momentumShot(90);
        return;       
    }   
}

void soloWinPointRed()
{
    runRollerTask();
    runPunchTask();

    while (!teleop) {
    
        //fire preload discs
        momentumShot(50); //change if necessary to targetPosition

        //spin roller
        staticSpinRoller(60, 800);

        //intake three discs
        targetPosition = 6500;
        drivebase.turnPID(53, 90);
        spinRollerBtn = true;
        drivebase.driveDistance(true, 24, 53, 70); //knocking discs down
        pros::delay(500);
        drivebase.driveDistance(true, 14, 53, 25); //intaking discs
        pros::delay(500);
        stopRollerBtn = true;
        drivebase.driveDistance(true, 7, 45, 60);
        
        //turn 90 degrees and shoot discs
        drivebase.turnPID(-95, 90);
        //drivebase.driveDistance(false, 3, -90, 30);
        pros::delay(100);
        momentumShot(45);

        //score end roller
        //drivebase.driveDistance(false, 3, -90, 50);
        drivebase.turnPID(91, 90);
        spinRollerBtn = true;
        drivebase.driveDistance(true, 55, 91, 45);
        drivebase.turnPID(-135, 90);
        stopRollerBtn = true; 
        //drivebase.driveDistance(false, 3, -135, 40);
        
        //spin roller
        staticSpinRoller(60, 800);
        drivebase.turnPID(5, 90);
        momentumShot(70);
        return;

    }
}

void farSideRed5() {
    runRollerTask();
    runPunchTask();
    leftDrive.move(75);
    rightDrive.move(75);
    pros::delay(125);

    //score preload
    momentumShot(50);
    //farPrimeBtn = true;

    //intake 3 discs (ram with outtake, then slowly intake)
    
    targetPosition = 6500;
    drivebase.turnPID(-65, 80);
    intakeBtn = true;
    drivebase.driveDistance(true, 35, -65, 40);
    pros::delay(1500);
    stopRollerBtn = true;
    drivebase.turnPID(90, 60);
    momentumShot(45);

    // //turn and shoot
    // drivebase.turnPID(90, 90);
    // shootBtn = true;

    //score roller
    //drivebase.driveDistance(false, 6, 90, 50);
    drivebase.turnPID(-90, 80);
    drivebase.driveDistance(false, 47, -90, 60);
    //drivebase.turnPID(45, 90);
    //drivebase.driveDistance(false, 6, -45, 40);
    //spinRollerRed();
    rightDrive.move(-40);
    //rightDrive.move(-50);
    pros::delay(1000);
    spinRollerBtn = true;
    pros::delay(900);
    stopRollerBtn = true;
    drivebase.goForTime(40, 150); 

    return; 
}

void farRollerRed(){
    //optRoller.set_led_pwm(50);

    drivebase.driveDistance(false, 18, 0, 40);
    drivebase.turnPID(90,90);
    leftDrive.move(-40);
    rightDrive.move(-40);
    staticSpinRoller(60, 800);
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
    //spinRoller(1); //1 for want red
    
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

void soloWinPointBlue() {
    soloWinPointRed();
    // pros::lcd::initialize();
    // //drivebase.turnPID(45, 90);
    // leftDrive.move(-50);
    // rightDrive.move(-50);
    // spinRoller(2); //1 for want red
    // //intake(400);
    // pros::delay(500);
    // leftDrive.move(0);
    // rightDrive.move(0);

    // drivebase.driveDistance(true, 6, 0, 40);
    // drivebase.turnPID(45, 90);
    // drivebase.driveDistance(true, 67 /*tune*/, 45, 60);
    // drivebase.turnPID(-90, 90);
    // phase = 3;
    // //prime();
    // fire();
    // //intake();
    // fire();
    // drivebase.turnPID(90, 90);
    // drivebase.driveDistance(true, 67, 90, 40);
    // drivebase.turnPID(45, 90);
    // return;


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
    //spinRoller(2); //1 for want red
    
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

void autonSkills(bool offset) {
	pros::lcd::initialize();

    //runPunchTask();
    //runRollerTask();

    //1: spin roller, wind up puncher slightly
    spinRollerBtn = 127;
    leftDrive.move(-120);
    //rightDrive.move(-40);
    pros::delay(700);
    stopRollerBtn = true;
    drivebase.goForTime(40, 200);
    
    targetPosition = 275;

    //2: turn and intake disc
    intakeBtn = true;
    drivebase.offsetTurnPID(-45, 60);
    drivebase.driveDistance(true, 14, -45, 50);
    
    //3: score second roller
    drivebase.offsetTurnPID(-90, 50);
    spinRollerBtn = 60;
    drivebase.driveDistance(true, 4, -90, 50);
    rightDrive.move(80);
    pros::delay(800);
    stopRollerBtn = true;
    //drivebase.goForTime(-40, 200);
    drivebase.driveDistance(false, 4, -90, 50);

    //4: turn right and travel to goal, shoot
    //drivebase.gpsTurnToXY(-1.3, -1.3, offset);
    drivebase.offsetTurnPID(0, 90);
    //drivebase.gpsMoveToXY(-1.3, -1.3, 60, offset);
    drivebase.driveToWall(true, 1600, 0, 80);
    pros::delay(200);
    shootBtn = true;
    pros::delay(500);

    //5: intake diagonal discs 
    targetPosition = 4500;
    intakeBtn = true;
    drivebase.offsetTurnPID(145, 50);
    drivebase.driveDistance(true, 20, 145, 50);
    pros::delay(300);
    drivebase.offsetTurnPID(45, 50);
    drivebase.driveDistance(true, 26, 45, 55);

    //print out gyro value on line 3
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "Gyro: %f", imu.getValue());
    
    //stopRollerBtn = true;

    //6: turn and shoot
    //imu.reset();
    
    drivebase.offsetTurnPID(-45, 50);
    stopRollerBtn = true;
    pros::delay(300);
    shootBtn = true;
    pros::delay(500);

    //7: turn and intake 3 stacked discs
    targetPosition = 4400;
    drivebase.offsetTurnPID(45, 50);
    intakeBtn = true;
    drivebase.driveDistance(true, 22, 45, 55);
    pros::delay(300);
    drivebase.driveDistance(true, 18, 45, 25);

    //print out gyro value on line 3
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "Gyro: %f", imu.getValue());

    //8: score roller
    drivebase.driveDistance(true, 8, 45, 50);
    drivebase.offsetTurnPID(0, 70);
    spinRollerBtn = 60;
    drivebase.driveToWall(true, 150, 0, 50);
    rightDrive.move(80);
    pros::delay(800);
    stopRollerBtn = true;
    //drivebase.goForTime(-40, 200);
    drivebase.driveDistance(false, 4, 0, 50);
    drivebase.offsetTurnPID(45, 70);
    drivebase.driveDistance(false, 46, 45, 75);

    //print out gyro value on line 3
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "Gyro: %f", imu.getValue());

    //9: turn and shoot
    stopRollerBtn = true;
    drivebase.offsetTurnPID(-50, 70);
    pros::delay(500);
    shootBtn = true;
    pros::delay(300);

    //10: align with barrier and intake 3 discs
    intakeBtn = true;
    drivebase.offsetTurnPID(-10, 70);
    drivebase.driveDistance(true, 24, -10, 25);

    //11: turn and shoot
    drivebase.driveToWall(true, 250, 0, 50);
    drivebase.offsetTurnPID(-105, 70);
    stopRollerBtn = true;
    pros::delay(400);
    shootBtn = true;
    pros::delay(300);

    //12: turn, drive to rollers, and intake 3 discs
    drivebase.offsetTurnPID(95, 70);
    drivebase.driveDistance(true, 48, 95, 90);
    intakeBtn = true;
    drivebase.driveDistance(true, 5, 90, 65);
    pros::delay(1000);
    drivebase.driveToWall(true, 150, 90, 25);

    //13: score roller
    spinRollerBtn = 60;
    //drivebase.driveDistance(true, 4, 90, 50);
    leftDrive.move(80);
    pros::delay(800);
    stopRollerBtn = true;
    //drivebase.goForTime(-40, 200);
    drivebase.driveDistance(false, 4, 90, 50);
    //14: drive to goal and shoot
    //15: get low barrier discs (effectively a repeat of steps 5-10)
    //16: shoot low goal discs
    //17: back up, turn/arcs, and intake 3 discs
    //18: turn and shoot
    //19: turn and intake 3 discs
    //20: turn and shoot
    //21: back up and turn, fire expansion

    pros::delay(1000);

}