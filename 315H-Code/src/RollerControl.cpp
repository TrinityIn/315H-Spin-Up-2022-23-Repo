#include "main.h"
#include "pros/misc.h"

const pros::controller_digital_e_t START_INTAKE = pros::E_CONTROLLER_DIGITAL_L1;
const pros::controller_digital_e_t START_OUTTAKE = pros::E_CONTROLLER_DIGITAL_UP;
const pros::controller_digital_e_t INTAKE_OVERRIDE = pros::E_CONTROLLER_DIGITAL_Y;
const pros::controller_digital_e_t SPIN_ROLLER = pros::E_CONTROLLER_DIGITAL_L2;

//runs intake for the given amount of time
void intake(int mseconds) {
    roller.move(127);
    pros::delay(mseconds);
    roller.move(0);
}


//spin until red or blue based on c
void spinRoller(int c) {
  int color = (int) optRoller.get_hue();

    //1: want red, 2: want blue
    if(c == 1) {
      while(color <= 20) {
        roller.move(90);
        pros::delay(10);
        color = (int) optRoller.get_hue();
        // if (!(color < 30 /*red*/ || (color > 170 && color < 250) /*blue*/)) {
        //   break;
        // }
      }
      roller.move(-75);
      pros::delay(25);
      roller.move(0);
    } else {
      while(color > 20) {
        roller.move(90);
        color = (int) optRoller.get_hue();
        // if (!(color < 30 /*red*/ || (color > 170 && color < 250) /*blue*/)) {
        //   break;
        // }
        pros::delay(10);
      }
      roller.move(-75);
      pros::delay(25);
      roller.move(0);
    } 
  
}

bool runRollerBtn = false;
bool stopRollerBtn = false;
bool isRollerRunning = false;
bool isRollerBtnPressed = false;

bool startRollerTask = true;

void operateRoller(void*) {

  while (true) {
    if (master.get_digital(START_INTAKE) && !isRollerBtnPressed) {
      isRollerBtnPressed = true;
      if (!isRollerRunning) {
        // intake
        roller.move(127);
        isRollerRunning = true;
      }
      else {
        // stop intake
        roller.move(0);
        isRollerRunning = false;
      }
    }
    else if (master.get_digital(INTAKE_OVERRIDE) && !isRollerBtnPressed) {
      isRollerBtnPressed = true;
      if (!isRollerRunning) {
        // intake
        roller.move(127);
        isRollerRunning = true;
      }
      else {
        // stop intake
        roller.move(0);
        isRollerRunning = false;
      }
    }
    else if (!(master.get_digital(START_INTAKE)) && !(master.get_digital(INTAKE_OVERRIDE)) && isRollerBtnPressed) {
      isRollerBtnPressed = false;
    }
    // start outtake
    else if (master.get_digital(SPIN_ROLLER)) {
      isRollerRunning = false;
      roller.move(-90);
    }
    else if (master.get_digital(START_OUTTAKE)) {
      isRollerRunning = false;
      roller.move_voltage(-12000);
    }
    // stop intake
    else if (!isRollerRunning) {
      roller.move(0);
    }

    //virtual buttons
    if (runRollerBtn) {
      roller.move(120);
      isRollerRunning = true;
      runRollerBtn = false;
    }
    if (stopRollerBtn) {
      roller.move(0);
      isRollerRunning = false;
      stopRollerBtn = false;
    }

    //pros::lcd::print(0, "roller");
    pros::delay(10);
  }
}

void runRollerTask() {
    //isRollerRunning = false;
    //runRollerBtn = false;
    if (startRollerTask) {
        pros::Task runRoller(operateRoller);
        startRollerTask = false;
    }
}
