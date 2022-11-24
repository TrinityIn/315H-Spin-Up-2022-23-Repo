#include "main.h"
#include "pros/motors.h"

//motors
pros::Motor rightBack(10, true);
pros::Motor rightTop(8);
pros::Motor rightBottom(9, true);
pros::Motor_Group rightDrive({rightBack, rightTop, rightBottom});

pros::Motor leftBack(5);
pros::Motor leftTop(7, true);
pros::Motor leftBottom(6);
pros::Motor_Group leftDrive({leftBack, leftTop, leftBottom});


pros::Motor catapult(12, pros::E_MOTOR_GEARSET_36);
pros::Motor roller(3, pros::E_MOTOR_GEARSET_06);

//sensors
pros::Optical optRoller(12);
pros::IMU imu(4);
pros::ADIDigitalIn cataPrime('a');


//controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

void init_sensors() {

}




