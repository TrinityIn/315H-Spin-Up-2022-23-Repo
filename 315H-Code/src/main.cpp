#include "main.h"
#include "AutonPrograms.hpp"
#include "pros/llemu.hpp"

Drivebase drivebase(0.5, 35.16/*replace*/);
bool teleop;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//do NOT initialize LCD here, it will prevent GUI from displaying auton tabs
	//pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");
	init_sensors();
	initializeGUI();


	pros::lcd::register_btn1_cb(on_center_button);
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */ 
void autonomous() {
	//soloWinPointRed();
	
	//soloWinPointHalfBlue();
	//spinRollerRed();
	spinRollerBlue();
	//spinRollerBlue();

	//soloWinPointBlue();
	//farRollerBlue();
	
/*
  switch (autonSelected)
  {
    // red side autons
    case 1:
      soloWinPointRed();
      break;
    
    // blue side autons
    case 1+NUM_SELECTION:
      soloWinPointBlue();
      break;
    
    // other programs
    case 1+NUM_SELECTION*2:
      // the skills program
      soloWinPointRed();
      break;
    
    default:
      break;
  }*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	//pros::Motor left_mtr(1);
	//pros::Motor right_mtr(2);
	teleop = true;
	//run roller task
	runRollerTask();
	runExpanderTask();
	runCataTask();
	pros::lcd::initialize();
	prime(300); //remove once ratchet is attached

	while (true) {
		
		//move drivebase
		drivebase.calculatePower();
		// lPower = -1 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		// rPower = -1 * (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

		// leftDrive.move(lPower);
		// rightDrive.move(rPower);
		//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		

		pros::delay(10);
	}
}
