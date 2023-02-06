#ifndef PUNCHER_CONTROL_HPP
#define PUNCHER_CONTROL_HPP

extern int phase;
void prime(int desPhase);
void prime();
void fire();
void runPunchTask();

extern bool shootBtn;
extern bool farPrimeBtn;
extern bool twoDiscBtn;

#endif