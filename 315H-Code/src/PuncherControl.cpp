#include "main.h"
#include "pros/misc.h"

#define NUM_PHASE 3
#define HOLD_POWER 0

//global position indicator variables
int phase = 0; //0 is nothing, 1 is near goal, 2 is outside barrier, 3 is halfcourt/max
int targetPosition = -1;

//virtual buttons
bool shootBtn = false;
bool farPrimeBtn = false;
bool twoDiscBtn = false;

//setup variables
bool shootBtnPressed = false;
bool phaseBtn = false;
bool startPunchTask = true;
bool primed = true;
//bool down = cataPrime.get_value();

void phasePrime() {
    int target = 0;
    switch(phase) {
        case 1:
            target = 4050;
            break;
        case 2:
            target = 4200;
            break;
        case 3:         
            target = 6500;
            break;
    }
    double prevPosition = puncher.get_position();
    while (puncher.get_position() < target && !(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) && !shootBtn) {
        puncher.move_voltage(12000);
        //down = cataPrime.get_value();
        double prevPosition = puncher.get_position();
        pros::delay(10);
        //pros::lcd::print(0, "%.3f", fabs(puncher.get_position() - prevPosition));
        // if (fabs(puncher.get_position() - prevPosition) < 0.01) {
        //     break;
        // }
        
    }
    //catapult.move(-50);
    //pros::delay(50);
    puncher.move(HOLD_POWER);
    return;
}
void prime(int targetPosition) {
    double prevPosition = puncher.get_position();
    while (puncher.get_position() < targetPosition && !(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) && !shootBtn) {
        puncher.move_voltage(12000);
        //down = cataPrime.get_value();
        double prevPosition = puncher.get_position();
        pros::delay(10);
        //pros::lcd::print(0, "%.3f", fabs(puncher.get_position() - prevPosition));
        // if (fabs(puncher.get_position() - prevPosition) < 0.01) {
        //     break;
        // }
        
    }
    targetPosition = -1;
    //catapult.move(-50);
    //pros::delay(50);
    puncher.move(HOLD_POWER);
    return;
}

void fire() {
    puncher.move(0);
    //roller.move(0);
    puncherRelease.set_value(true);
    //catapult.move(30);
    pros::delay(250);
    puncherRelease.set_value(false);
    //pros::lcd::print(0, "fire");    
    pros::delay(10);

}

void operatePuncher(void*) {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !shootBtnPressed) {
            shootBtnPressed = true;
            //checks if the catapult starts from a primed position
            fire();
            puncher.tare_position();
            phase = 1;
            phasePrime();
        }
        // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     puncher.move(127);
        // }
        else if (!shootBtnPressed) {
            puncher.move(HOLD_POWER);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !phaseBtn) {
            phaseBtn = true;
            phase = std::min(phase + 1, NUM_PHASE);
            phasePrime();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            phaseBtn = false;
        }
        shootBtnPressed = false;


        //virtual btns
        if (shootBtn) {
            fire();
            phase = 1;
            puncher.tare_position();
            shootBtn = false;
            phasePrime();
        }
        if (farPrimeBtn) {
            phase = 3;
            phasePrime();
            farPrimeBtn = false;
        }
        if (twoDiscBtn) {
            phase = 2;
            phasePrime();
            twoDiscBtn = false;
        }
        if (targetPosition > 0) {
            prime(targetPosition);
            targetPosition = -1;
        }
        
        pros::delay(10);
    }
}

void momentumShot(int speed) {
    leftDrive.move(speed);
    rightDrive.move(speed);
    pros::delay(20);
    shootBtn = true;
    pros::delay(200);
    leftDrive.move(0);
    rightDrive.move(0);
}

void runPunchTask() {
    //shootBtn = false;
    if (startPunchTask) {
        pros::Task runPuncher(operatePuncher);
        startPunchTask = false;
    }
}