#ifndef ROLLER_CONTROL_HPP
#define ROLLER_CONTROL_HPP

void intake();
void runRollerTask();
void spinRoller();

extern bool runRollerBtn;
extern bool stopRollerBtn;
extern bool isRollerRunning;
extern bool isRollerButtonPressed;


#endif