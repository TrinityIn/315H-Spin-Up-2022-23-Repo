#include "main.h"
#include "pros/llemu.hpp"

const int CUTOFF_TIME = 11200;    

//auton programs

/** ============================================
 * @brief 
 * Red side autons
 */
void nearSide8() {
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
        //rightDrive.move(-40);
        pros::delay(100);
        outtakeBtn = true;
        pros::delay(800);
        stopRollerBtn = true;
        drivebase.driveDistance(true, 3, -8, 50); 

        //delay
        //pros::delay(5000);

        //shoot preloads
        pros::delay(400);
        shootBtn = true;
        pros::delay(400);
        //drivebase.offsetTurnPID(-10, 50);
        //momentumShot(30);

        //intake three discs
        targetPosition = 5900;
        drivebase.offsetTurnPID(45, 70);
        //drivebase.driveDistance(true, 12, 60, 70);
        outtakeBtn = true;
        drivebase.driveDistance(true, 23, 45, 70); //knocking discs down
        stopRollerBtn = true;
        pros::delay(250);
        intakeBtn = true;
        drivebase.driveDistance(true, 17, 45, 25); //intaking discs
        pros::delay(800);
        stopRollerBtn = true;
        //drivebase.driveDistance(true, 7, 45, 60);
        
        //turn 90 degrees and shoot discs
        drivebase.offsetTurnPID(-40, 70);
        //drivebase.driveDistance(false, 3, -90, 30);
        pros::delay(100);
        shootBtn = true;
        pros::delay(400);
        targetPosition = 6500;
        //momentumShot(40);

        //get second stack of discs
        intakeBtn = true;
        drivebase.offsetTurnPID(135, 70);
        drivebase.driveDistance(true, 8, 140, 25);
        drivebase.driveDistance(true, 20, 155, 20);
        pros::delay(800);
        drivebase.driveDistance(false, 20, 140, 60);
        stopRollerBtn = true;

        //shoot second stack of discs
        drivebase.offsetTurnPID(-37, 70);
        shootBtn = true;
        //momentumShot(90);
        return;       
    }   
}

void soloWinPoint() {
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
        //rightDrive.move(-40);
        pros::delay(100);
        outtakeBtn = true;
        pros::delay(800);
        stopRollerBtn = true;
        drivebase.driveDistance(true, 3, -9, 50); 

        //delay
        //pros::delay(5000);

        //shoot preloads
        pros::delay(400);
        shootBtn = true;
        pros::delay(400);
        //drivebase.offsetTurnPID(-10, 50);
        //momentumShot(30);

        //intake three discs
        targetPosition = 5800;
        drivebase.offsetTurnPID(45, 70);
        //drivebase.driveDistance(true, 12, 60, 70);
        outtakeBtn = true;
        drivebase.driveDistance(true, 23, 45, 70); //knocking discs down
        stopRollerBtn = true;
        pros::delay(250);
        intakeBtn = true;
        drivebase.driveDistance(true, 17, 45, 30); //intaking discs
        pros::delay(600);
        stopRollerBtn = true;
        //drivebase.driveDistance(true, 7, 45, 60);
        
        //turn 90 degrees and shoot discs
        drivebase.offsetTurnPID(-40, 70);
        //drivebase.driveDistance(false, 3, -90, 30);
        pros::delay(100);
        shootBtn = true;
        pros::delay(300);
        targetPosition = 6500;
        //momentumShot(40);

        //score end roller
        //drivebase.driveDistance(false, 3, -90, 50);
        drivebase.offsetTurnPID(45, 70);
        intakeBtn = true;
        drivebase.driveDistance(true, 44, 45, 65);
        drivebase.driveDistance(true, 16, 60, 80);
        drivebase.offsetTurnPID(-82, 70);
        stopRollerBtn = true; 
        pros::delay(300);
        shootBtn = true;
        pros::delay(200);
        //drivebase.driveDistance(false, 3, -135, 40);
        
        //spin roller
        drivebase.driveDistance(false, 3, -75, 70);
        staticSpinRoller(-60, 800);
        momentumShot(70);
        return;

    }
}

void farSide6() {
    runRollerTask();
    runPunchTask();

    //intake first disc
    targetPosition = 6500;
    intakeBtn = true;
    drivebase.driveDistance(true, 17, 0, 55);
    pros::delay(700);

    //score preload
    stopRollerBtn = true;
    pros::delay(400);
    shootBtn = true;
    pros::delay(300);
    targetPosition = 5700;

    //intake 3 discs
    intakeBtn = true;
    drivebase.driveDistance(true, 3, 0, 55);
    drivebase.driveDistance(true, 3, 10, 40);
    pros::delay(900);
    drivebase.driveDistance(false, 9, 10, 60);
    drivebase.offsetTurnPID(-60, 70);
    drivebase.driveDistance(true, 28, -60, 45);
    drivebase.offsetTurnPID(25, 60);
    stopRollerBtn = true;
    pros::delay(400);
    shootBtn = true;
    pros::delay(400);

    //score roller
    //drivebase.driveDistance(false, 6, 90, 50);
    drivebase.offsetTurnPID(-70, 70);
    drivebase.driveDistance(false, 48, -70, 80);
    //drivebase.turnPID(45, 90);
    //drivebase.driveDistance(false, 6, -45, 40);
    //spinRollerRed();
    rightDrive.move(-80);
    //rightDrive.move(-50);
    pros::delay(800);
    outtakeBtn = true;
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
    soloWinPoint();
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

void farSide8() {
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

    runPunchTask();
    runRollerTask();

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
    // pros::delay(10000);
    // pros::lcd::clear_line(3);
    // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());

    //5: intake diagonal discs 
    targetPosition = 4500;
    intakeBtn = true;
    drivebase.offsetTurnPID(145, 60);
    drivebase.driveDistance(true, 20, 145, 70);
    
    pros::delay(500);
    // pros::lcd::clear_line(3);
    // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());
    // pros::delay(10000);
    drivebase.offsetTurnPID(45, 70);
    drivebase.driveDistance(true, 26, 45, 55);
    //print out gyro value on line 3
    // pros::lcd::clear_line(3);
    // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());
    //return;
    //stopRollerBtn = true;

    //6: turn and shoot
    //imu.reset();
    
    drivebase.offsetTurnPID(-47, 70);
    stopRollerBtn = true;
    pros::delay(300);
    shootBtn = true;
    pros::delay(500);

    //7: turn and intake 3 stacked discs
    targetPosition = 4500;
    drivebase.offsetTurnPID(45, 50);
    outtakeBtn = true;
    drivebase.driveDistance(true, 24, 45, 55);
    stopRollerBtn = true;
    pros::delay(300);
    intakeBtn = true;
    drivebase.driveDistance(true, 18, 45, 25);

    //8: score roller
    drivebase.driveDistance(true, 7, 45, 50);
    drivebase.offsetTurnPID(0, 70);
    spinRollerBtn = 60;
    drivebase.driveToWall(true, 150, 0, 50);
    rightDrive.move(80);
    pros::delay(800);
    stopRollerBtn = true;
    //drivebase.goForTime(-40, 200);
    drivebase.driveDistance(false, 4, 0, 50);
    drivebase.offsetTurnPID(45, 70);
    drivebase.driveDistance(false, 44, 45, 75);

    //print out gyro value on line 3
    pros::lcd::clear_line(3);
    pros::lcd::print(3, "Gyro: %f", imu.getValue());

    //9: turn and shoot
    stopRollerBtn = true;
    drivebase.offsetTurnPID(-55, 70);
    pros::delay(500);
    shootBtn = true;
    pros::delay(300);

    //10: align with barrier and intake 3 discs
    intakeBtn = true;
    drivebase.offsetTurnPID(-15, 70);
    drivebase.driveDistance(true, 24, -15, 25);

    //11: turn and shoot
    drivebase.driveToWall(true, 250, 0, 50);
    drivebase.offsetTurnPID(-105, 70);
    stopRollerBtn = true;
    pros::delay(400);
    shootBtn = true;
    pros::delay(300);

    //12: turn, drive to rollers, and intake 3 discs
    drivebase.offsetTurnPID(115, 70);
    drivebase.driveDistance(true, 30, 120, 90);
    outtakeBtn = true;
    drivebase.driveDistance(true, 13, 90, 65);
    stopRollerBtn = true;
    pros::delay(1000);
    intakeBtn = true;
    drivebase.driveToWall(true, 150, 90, 25);

    //13: score roller
    spinRollerBtn = 60;
    //drivebase.driveDistance(true, 4, 90, 50);
    leftDrive.move(80);
    pros::delay(800);
    stopRollerBtn = true;
    //drivebase.goForTime(-40, 200);
    drivebase.driveDistance(false, 8, 90, 50);



    // //14
    // drivebase.offsetTurnPID(180, 90);
    // //drivebase.gpsMoveToXY(-1.3, -1.3, 60, offset);
    // drivebase.driveToWall(true, 1600, 180, 80);
    // pros::delay(200);
    // shootBtn = true;
    // pros::delay(500);
    // // pros::delay(10000);
    // // pros::lcd::clear_line(3);
    // // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());

    // //5: intake diagonal discs 
    // targetPosition = 4600;
    // intakeBtn = true;
    // drivebase.offsetTurnPID(325, 60);
    // drivebase.driveDistance(true, 20, 325, 70);
    
    // pros::delay(500);
    // // pros::lcd::clear_line(3);
    // // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());
    // // pros::delay(10000);
    // drivebase.offsetTurnPID(225, 70);
    // drivebase.driveDistance(true, 26, 225, 55);
    // //print out gyro value on line 3
    // // pros::lcd::clear_line(3);
    // // pros::lcd::print(3, "Gyro: %f", imu.getValue());
    // // pros::lcd::print(4, "Uncorrected Gyro: %f", imu.get_rotation());
    // //return;
    // //stopRollerBtn = true;

    // //6: turn and shoot
    // //imu.reset();
    
    // drivebase.offsetTurnPID(135, 70);
    // stopRollerBtn = true;
    // pros::delay(300);
    // shootBtn = true;
    // pros::delay(500);

    // //7: turn and intake 3 stacked discs
    // targetPosition = 4600;
    // drivebase.offsetTurnPID(225, 50);
    // outtakeBtn = true;
    // drivebase.driveDistance(true, 24, 225, 55);
    // stopRollerBtn = true;
    // pros::delay(300);
    // intakeBtn = true;
    // drivebase.driveDistance(true, 18, 225, 25);
    
    // drivebase.driveDistance(false, 38, 225, 75);


    // //9: turn and shoot
    // stopRollerBtn = true;
    // drivebase.offsetTurnPID(130, 70);
    // pros::delay(500);
    // shootBtn = true;
    // pros::delay(300);

    // //10: align with barrier and intake 3 discs
    // intakeBtn = true;
    // drivebase.offsetTurnPID(170, 70);
    // drivebase.driveDistance(true, 24, 170, 25);

    // //11: turn and shoot
    // drivebase.driveToWall(true, 250, 180, 50);
    // drivebase.offsetTurnPID(75, 70);
    // stopRollerBtn = true;
    // pros::delay(400);
    // shootBtn = true;
    // pros::delay(300);

    // //14: drive to goal and shoot
    // //15: get low barrier discs (effectively a repeat of steps 5-10)
    // //16: shoot low goal discs
    // //17: back up, turn/arcs, and intake 3 discs
    // //18: turn and shoot
    // //19: turn and intake 3 discs
    // //20: turn and shoot
    // //21: back up and turn, fire expansion
    // drivebase.driveDistance(false, 36, 100, 80);
    drivebase.offsetTurnPID(225, 70);
    leftExpander.set_value(true);

    pros::delay(1000);

}