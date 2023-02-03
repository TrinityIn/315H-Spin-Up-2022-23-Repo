#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

//motors
pros::Motor rightBack(15);
pros::Motor rightTop(4, true);
pros::Motor rightBottom(5);
pros::Motor_Group rightDrive({rightBack, rightTop, rightBottom});

pros::Motor leftBack(13, true);
pros::Motor leftTop(2);
pros::Motor leftBottom(3, true);
pros::Motor_Group leftDrive({leftBack, leftTop, leftBottom});


pros::Motor puncher(12, pros::E_MOTOR_GEARSET_36);
pros::Motor roller(16, pros::E_MOTOR_GEARSET_06);

//sensors
pros::Optical optRoller(21);
InertialSensor imu(14, 91.56/90.0);
//pros::IMU imu(4);
//pros::ADIDigitalIn cataPrime('');

//pneumatics
pros::ADIDigitalOut puncherRelease('b');
pros::ADIDigitalOut leftExpander('h');


//controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

void init_sensors() {
    pros::delay(3000);
    leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    return;
}




