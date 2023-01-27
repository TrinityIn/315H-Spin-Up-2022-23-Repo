#include "main.h"
#include "pros/misc.h"

bool state = false;
bool expandBtn = false;
bool startExpanderTask = true;

void release() {
    state = !state;
    leftExpander.set_value(state);
    puncherRelease.set_value(state);
    pros::delay(10);
    return;
}

void operateExpander(void*) {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !expandBtn) {
            expandBtn = true;
            release();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
            expandBtn = false;
        pros::delay(10);
    }
}

void runExpanderTask() {
    if (startExpanderTask) {
        pros::Task runExpander(operateExpander);
        startExpanderTask = false;
    }
}