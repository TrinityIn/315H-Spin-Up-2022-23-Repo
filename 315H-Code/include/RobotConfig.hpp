#ifndef _ROBOTCONFIG_HPP_
#define _ROBOTCONFIG_HPP_

//motors
#include "pros/distance.hpp"
extern pros::Motor rightBack;
extern pros::Motor rightTop;
extern pros::Motor rightBottom;
extern pros::Motor_Group rightDrive;

extern pros::Motor leftBack;
extern pros::Motor leftTop;
extern pros::Motor leftBottom;
extern pros::Motor_Group leftDrive;

extern pros::Motor puncher;
extern pros::Motor roller;

//sensors
extern pros::Optical optRoller;
extern InertialSensor imu;
extern pros::Distance frontDistance;
extern pros::Distance backDistance;
extern pros::Gps gps;

extern pros::ADIDigitalIn cataPrime;

//pneumatics
extern pros::ADIDigitalOut puncherRelease;
extern pros::ADIDigitalOut leftExpander;

//controllers
extern pros::Controller master;


void init_sensors();
void filterIMUNoise(void*);

#endif
