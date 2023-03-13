#ifndef ROLLER_CONTROL_HPP
#define ROLLER_CONTROL_HPP

//void intake();
#include "AutonPrograms.hpp"
void intake(int mseconds);
void runRollerTask();

void staticSpinRoller(int rollerSpeed, int delayTime);
void spinRoller(int c);

extern bool intakeBtn;
extern bool stopRollerBtn;
extern int spinRollerBtn;
extern bool outtakeBtn;

extern bool isRollerRunning;
extern bool isRollerBtnPressed;


#endif