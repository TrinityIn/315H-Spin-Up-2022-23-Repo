#include "main.h"
#include "pros/motors.h"

//motors
pros::Motor leftFront(10, true);
pros::Motor leftTop(8);
pros::Motor leftBottom(9, true);
pros::Motor_Group leftDrive({leftFront, leftTop, leftBottom});

pros::Motor rightFront(5);
pros::Motor rightTop(7, true);
pros::Motor rightBottom(6);
pros::Motor_Group rightDrive({rightFront, rightTop, rightBottom});


pros::Motor catapult(12, pros::E_MOTOR_GEARSET_36);
pros::Motor roller(3, pros::E_MOTOR_GEARSET_06);

//sensors
pros::Optical optRoller(12);
pros::ADIAnalogIn cataPrime('e');


//controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

void init_sensors() {

}




