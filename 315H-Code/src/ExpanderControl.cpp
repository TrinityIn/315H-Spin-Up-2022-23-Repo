#include "main.h"
#include "pros/misc.h"

bool expanderState = false;
bool expandBtnPressed = false;
bool startExpanderTask = true;
bool releaseBtn = false;

void release() {
    expanderState = !expanderState;
    leftExpander.set_value(expanderState);
    //puncherRelease.set_value(expanderState);
    pros::delay(10);
    return;
}

void operateExpander(void*) {
    int startTeleOp = pros::millis();
    while (true) {
        //timer set at start of tele-op to prevent early expansion
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !expandBtnPressed && (pros::millis() - startTeleOp > 95)) {
            expandBtnPressed = true;
            release();
        }
        //manual override: press A and Left Arrow to fire Expander whenever
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && 
            master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
            !expandBtnPressed) {
            expandBtnPressed = true;
            release();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
            expandBtnPressed = false;

        //virtual btns
        if (releaseBtn) {
            release();
            releaseBtn = false;
        }
        pros::delay(10);
    }
}

void runExpanderTask() {
    if (startExpanderTask) {
        pros::Task runExpander(operateExpander);
        startExpanderTask = false;
    }
}