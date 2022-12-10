#include "main.h"
#include "pros/misc.h"

bool shootBtn = true;
bool startCataTask = true;
bool primed = true;
//bool down = cataPrime.get_value();

void prime(int delay) {
    catapult.move(-127);
    pros::delay(delay);

    while (!(cataPrime.get_value())) {
        catapult.move(-60);
        //down = cataPrime.get_value();
        pros::delay(10);
    }
    catapult.move(-60);
    pros::delay(100);
    catapult.move(0);
    return;
}

void fire() {
    catapult.tare_position();
    catapult.move(-30);
    pros::delay(100);
    catapult.move(0);
    //pros::lcd::print(0, "fire");    
    pros::delay(10);

}

void operateCatapult(void*) {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !shootBtn) {
            shootBtn = true;
            //checks if the catapult starts from a primed position
            if(cataPrime.get_value()) 
                primed = true;
            else 
                primed = false;
            
            fire();
            if (primed) prime(1500);
            else prime(300);
        }
        // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     catapult.move(20);
        // }
        // else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     catapult.move(-10);
        // }
        shootBtn = false;
        pros::delay(10);
    }
}

void runCataTask() {
    //shootBtn = false;
    if (startCataTask) {
        pros::Task runCatapult(operateCatapult);
        startCataTask = false;
    }
}