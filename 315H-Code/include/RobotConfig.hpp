#ifndef _ROBOTCONFIG_HPP_
#define _ROBOTCONFIG_HPP_

//motors
#include "CommonUtility.hpp"
extern pros::Motor rightBack;
extern pros::Motor rightTop;
extern pros::Motor rightBottom;
extern pros::Motor_Group rightDrive;

extern pros::Motor leftBack;
extern pros::Motor leftTop;
extern pros::Motor leftBottom;
extern pros::Motor_Group leftDrive;

extern pros::Motor catapult;
extern pros::Motor roller;

//sensors
extern pros::Optical optRoller;
extern InertialSensor imu;
extern InertialSensor imu;
extern VisionSensor liftVision;
extern DistanceSensor liftDistance;
extern VisionSensor tilterVision;
extern DistanceSensor tilterDistance;
extern DistanceSensor distanceBack;
extern DistanceSensor distanceFront;

extern pros::ADIDigitalIn cataPrime;

//controllers
extern pros::Controller master;


void init_sensors();
void filterIMUNoise(void*);

#endif
