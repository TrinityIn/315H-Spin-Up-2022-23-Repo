#include "main.h"
#include "pros/llemu.h"
#include "pros/llemu.hpp"

Drivebase drivebase(4.0/6, 35.16/*replace*/);
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
	//spinRollerBlue();
	//spinRollerBlue();

	//soloWinPointBlue();
	//farRollerBlue();
	pros::lcd::print(2, "Auton selected: %d", autonSelected);
  	/*switch (autonSelected)
  	{
		// red side autons
		case 1:
		soloWinPointRed();
		break;
		case 2:
		nearSideRed9();
		break;
		case 3:
		farSideRed5();
		break;
		case 4:
		spinRollerRed();
		break;
		case 5:
		farRollerRed();
		break;
		case 6:
		//getDoubleNeutralQualRedR(drivebase);
		break;
		case 7:
		//getNeutralRedR(drivebase);
		break;
		case 8:
		//swipeGoalRed(drivebase);
		break;
		case 9:
		//rushNeutralLeftRed(drivebase);
		break;
		case 10:
		//neutralLeftQualRed(drivebase);
		break;
		case 11:
		//hookGoalRedL(drivebase);
		break;
		// blue side autons
		case 1+NUM_SELECTION:
		soloWinPointBlue();
		break;
		case 2+NUM_SELECTION:
		nearSideBlue9();
		break;
		case 3+NUM_SELECTION:
		farSideBlue5();
		break;
		case 4+NUM_SELECTION:
		spinRollerBlue();
		break;
		case 5+NUM_SELECTION:
		farRollerBlue();
		break;
		case 6+NUM_SELECTION:
		//getDoubleNeutralQualBlueR(drivebase);
		break;
		case 7+NUM_SELECTION:
		//getNeutralBlueR(drivebase);
		break;
		case 8+NUM_SELECTION:
		//swipeGoalBlue(drivebase);
		break;
		case 9+NUM_SELECTION:
		//rushNeutralLeftBlue(drivebase);
		break;
		case 10+NUM_SELECTION:
		//neutralLeftQualBlue(drivebase);
		break;
		case 11+NUM_SELECTION:
		//hookGoalBlueL(drivebase);
		break;
		// other programs
		case 1+NUM_SELECTION*2:
		// the skills program
		autonSkills();
		break;
		case 2+NUM_SELECTION*2:
		// program for debuging turning
		//testTurn(drivebase);
		break;
		case 3+NUM_SELECTION*2:
		// program for debuging movement
		//testDistance(drivebase, 24);
		break;
		case 4+NUM_SELECTION*2:
		break;
		case 5+NUM_SELECTION*2:
		break;
		case 6+NUM_SELECTION*2:
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
	runPunchTask();
	pros::lcd::initialize();
	//prime(300); //remove once ratchet is attached

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
