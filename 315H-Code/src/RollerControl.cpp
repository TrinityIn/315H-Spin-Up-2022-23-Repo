#include "main.h"

const pros::controller_digital_e_t START_INTAKE = pros::E_CONTROLLER_DIGITAL_L1;
const pros::controller_digital_e_t START_OUTTAKE = pros::E_CONTROLLER_DIGITAL_L2;

void intake() {
    roller.move(127);
}

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
    while(color < 20) {
      roller.move(100);
      pros::delay(10);
      color = (int) optRoller.get_hue();
    }
    roller.move(-75);
    pros::delay(10);
    roller.move(0);
  } else {
    while(color < 20) {
      roller.move(100);
      color = (int) optRoller.get_hue();
      pros::delay(10);
    }
    roller.move(-75);
    pros::delay(10);
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
        intake();
        isRollerRunning = true;
      }
      else {
        // stop intake
        roller.move(0);
        isRollerRunning = false;
      }
    }
    else if (!(master.get_digital(START_INTAKE)) && isRollerBtnPressed) {
      isRollerBtnPressed = false;
    }
    // start outtake
    else if (master.get_digital(START_OUTTAKE)) {
      isRollerRunning = false;
      roller.move(-90);
    }
    // stop intake
    else if (!isRollerRunning) {
      roller.move(0);
    }

    // virtual buttons
    // if (runRollerBtn) {
    //   intake();
    //   isRollerRunning = true;
    //   runRollerBtn = false;
    // }
    // if (stopRollerBtn) {
    //   roller.move(0);
    //   isRollerRunning = false;
    //   stopRollerBtn = false;
    // }

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
