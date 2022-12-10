#ifndef ROLLER_CONTROL_HPP
#define ROLLER_CONTROL_HPP

void intake();
void intake(int mseconds);
void runRollerTask();
void spinRoller(int c);

extern bool runRollerBtn;
extern bool stopRollerBtn;
extern bool isRollerRunning;
extern bool isRollerButtonPressed;


#endif