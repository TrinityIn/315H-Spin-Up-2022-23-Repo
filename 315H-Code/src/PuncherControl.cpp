#include "main.h"
#include "pros/misc.h"

#define NUM_PHASE 3

//virtual buttons
bool shootBtn = false;
bool farPrimeBtn = false;
bool twoDiscBtn = false;

//setup variables
bool shootBtnPressed = false;
bool phaseBtn = false;
int phase = 0; //0 is nothing, 1 is near goal, 2 is outside barrier, 3 is halfcourt/max
bool startPunchTask = true;
bool primed = true;
//bool down = cataPrime.get_value();

void prime() {
    int target = 0;
    switch(phase) {
        case 1:
            target = 4000;
            break;
        case 2:
            target = 4300;
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
    puncher.move(3);
    return;
}
void prime(int desPhase) {
    if (desPhase > 0 && desPhase <= NUM_PHASE) 
        phase = desPhase;
    else 
        phase = 1;

    prime();
}

void fire() {
    puncher.move(0);
    roller.move(0);
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
            prime();
        }
        // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     puncher.move(127);
        // }
        else if (!shootBtnPressed) {
            puncher.move(5);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !phaseBtn) {
            phaseBtn = true;
            phase = std::min(phase + 1, NUM_PHASE);
            prime();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            phaseBtn = false;
        }
        shootBtnPressed = false;


        //virtual btns
        if (shootBtn) {
            fire();
            phase = 1;
            shootBtn = false;
            prime();
        }
        if (farPrimeBtn) {
            prime(NUM_PHASE);
            farPrimeBtn = false;
        }
        if (twoDiscBtn) {
            prime(2);
            twoDiscBtn = false;
        }
        
        pros::delay(10);
    }
}

void runPunchTask() {
    //shootBtn = false;
    if (startPunchTask) {
        pros::Task runPuncher(operatePuncher);
        startPunchTask = false;
    }
}