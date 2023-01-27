#include "main.h"
#include "pros/misc.h"

bool shootBtn = true;
bool phaseBtn = false;
int phase = 0; //0 is nothing, 1 is near goal, 2 is outside barrier, 3 is halfcourt/max
bool startPunchTask = true;
bool primed = true;
//bool down = cataPrime.get_value();

void prime() {
    int target = 0;
    switch(phase) {
        case 1:
            target = 2500;
            break;
        case 2:
            target = 3500;
            break;
        case 3:         
            target = 7500;
            break;
    }

    while (puncher.get_position() < target) {
        puncher.move_voltage(12000);
        //down = cataPrime.get_value();
        pros::delay(10);
    }
    //catapult.move(-50);
    //pros::delay(50);
    puncher.move(3);
    return;
}

void fire() {
    puncher.tare_position();
    puncher.move(0);
    roller.move(0);
    puncherRelease.set_value(true);
    //catapult.move(30);
    pros::delay(300);
    puncherRelease.set_value(false);
    //pros::lcd::print(0, "fire");    
    pros::delay(10);

}

void operatePuncher(void*) {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !shootBtn) {
            shootBtn = true;
            //checks if the catapult starts from a primed position
            fire();
            puncher.tare_position();
            phase = 1;
            prime();
        }
        // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     puncher.move(127);
        // }
        else if (!shootBtn) {
            puncher.move(5);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !phaseBtn) {
            phaseBtn = true;
            phase = std::min(phase + 1, 3);
            prime();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            phaseBtn = false;
        }
        shootBtn = false;
        
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