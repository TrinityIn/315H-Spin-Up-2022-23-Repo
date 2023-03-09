#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"

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

void staticSpinRoller(int rollerSpeed, int delayTime) {
  //spin roller
  leftDrive.move(-40);
  rightDrive.move(-40);
  pros::delay(500);
  spinRollerBtn = rollerSpeed;
  pros::delay(delayTime);
  stopRollerBtn = true;
  drivebase.goForTime(40, 200);
}

//spin until red or blue based on c
// void spinRoller(int c) {
//   int color = (int) optRoller.get_hue();

//     //1: want red, 2: want blue
//     if(c == 1) {
//       while(color <= 35) {
//         roller.move(120);
//         pros::delay(10);
//         color = (int) optRoller.get_hue();
//         // if (!(color < 30 /*red*/ || (color > 170 && color < 250) /*blue*/)) {
//         //   break;
//         // }
//       }
//       roller.move(-75);
//       pros::delay(25);
//       roller.move(0);
//     } else {
//       while(color > 35) {
//         roller.move(90);
//         color = (int) optRoller.get_hue();
//         // if (!(color < 30 /*red*/ || (color > 170 && color < 250) /*blue*/)) {
//         //   break;
//         // }
//         pros::delay(10);
//       }
//       roller.move(-75);
//       pros::delay(25);
//       roller.move(0);
//     } 
  
// }

//virtual buttons
bool intakeBtn = false;
bool stopRollerBtn = false;
int spinRollerBtn = -1;

bool isRollerRunning = false;
bool isRollerBtnPressed = false;
bool outtaking = false;

bool startRollerTask = true;

void operateRoller(void*) {
  //roller.tare_position();
  roller.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  while (true) {

    //intake functions
    if (master.get_digital(START_INTAKE) && !isRollerBtnPressed) {
      isRollerBtnPressed = true;
      if (!isRollerRunning) {
        // intake
        roller.move(127);
        isRollerRunning = true;
      }
      else {
        // stop intake
        // roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        // while((int)roller.get_position() % 360 < 300) {
        //   roller.move(90);
        //   pros::delay(10);
        // }
        
        roller.move(0);
        roller.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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
      outtaking = true;
      roller.move(-90);
    }
    else if (master.get_digital(START_OUTTAKE)) {
      isRollerRunning = false;
      outtaking = true;
      roller.move_voltage(-12000);
    }
    // stop intake
    else if (!isRollerRunning) {
      outtaking = false;
      roller.move(0);
    }

    //virtual buttons
    if (intakeBtn) {
      roller.move(120);
      isRollerRunning = true;
      intakeBtn = false;
    }
    if (stopRollerBtn) {
      roller.move(0);
      isRollerRunning = false;
      stopRollerBtn = false;
    }
    if (spinRollerBtn >= 0) {
      roller.move(spinRollerBtn);    
      isRollerRunning = true;
      spinRollerBtn = -1;
    }

    if (!isRollerRunning && !outtaking) {
      int error = (int)roller.get_position() % 360;
      if (error > 180) {
        error -= 360;
      }
      double kp = 1.8;

      roller.move(-error * kp);
    }

    //pros::lcd::print(0, "roller");
    pros::delay(10);
  }
}

void runRollerTask() {
    //isRollerRunning = false;
    //intakeBtn = false;
    if (startRollerTask) {
        roller.tare_position();
        pros::Task runRoller(operateRoller);
        startRollerTask = false;
    }
}
