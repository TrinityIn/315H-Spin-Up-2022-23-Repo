#ifndef PUNCHER_CONTROL_HPP
#define PUNCHER_CONTROL_HPP

extern int phase;
extern int targetPosition;
extern int tuningDistance;

void prime(int desPhase);
void prime();
void fire();
void runPunchTask();
void momentumShot(int speed);

extern bool shootBtn;
extern bool farPrimeBtn;
extern bool twoDiscBtn;

#endif