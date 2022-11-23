#ifndef _ROBOTCONFIG_HPP_
#define _ROBOTCONFIG_HPP_

//motors
extern pros::Motor leftFront;
extern pros::Motor leftTop;
extern pros::Motor leftBottom;
extern pros::Motor_Group leftDrive;

extern pros::Motor rightFront;
extern pros::Motor rightTop;
extern pros::Motor rightBottom;
extern pros::Motor_Group rightDrive;

extern pros::Motor catapult;
extern pros::Motor roller;

//sensors
extern pros::Optical optRoller;
extern pros::IMU imu;
extern pros::ADIDigitalIn cataPrime;

//controllers
extern pros::Controller master;


void init_sensors();

#endif
