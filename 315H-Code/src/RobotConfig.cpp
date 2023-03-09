#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

//motors
pros::Motor rightBack(5);
pros::Motor rightTop(9, true);
pros::Motor rightBottom(8);
pros::Motor_Group rightDrive({rightBack, rightTop, rightBottom});

pros::Motor leftBack(4, true);
pros::Motor leftTop(7);
pros::Motor leftBottom(6, true);
pros::Motor_Group leftDrive({leftBack, leftTop, leftBottom});


pros::Motor puncher(2, pros::E_MOTOR_GEARSET_36);
pros::Motor roller(10, pros::E_MOTOR_GEARSET_06);

//sensors
pros::Distance frontDistance(12);
pros::Distance backDistance(20);
pros::Gps gps(14);
InertialSensor imu(3, 91.00/90.0);
//pros::IMU imu(4);
//pros::ADIDigitalIn cataPrime('');

//pneumatics
pros::ADIDigitalOut puncherRelease('b');
pros::ADIDigitalOut leftExpander('h');


//controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

void init_sensors() {
    imu.reset();
    gps.set_offset(-0.0762, 0.1524);
    pros::delay(3000);
    leftDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    rightDrive.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    return;
}




