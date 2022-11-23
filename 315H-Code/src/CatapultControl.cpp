#include "main.h"

bool shootBtn = false;
bool startCataTask = true;

void prime() {
    while (cataPrime.get_value() > 1500/*arbitrary value*/) {
        //the encoder rotates -1984 to prime
        //total rotation is -2520
        //therefore 
        pros::lcd::print(0, "hello");
        catapult.move(127);
        pros::delay(10);
    }
    catapult.move(0);
    return;
}

void fire() {
    catapult.tare_position();
    catapult.move(60);
    pros::delay(100);
    catapult.move(0);
    pros::delay(1000);
}

void operateCatapult() {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !shootBtn) {
            shootBtn = true;
            fire();
            prime();
        }
        shootBtn = false;
    }
    pros::delay(10);
}

void runCataTask() {
    //shootBtn = false;
    if (startCataTask) {
        pros::Task runCatapult(operateCatapult);
        startCataTask = false;
    }
}