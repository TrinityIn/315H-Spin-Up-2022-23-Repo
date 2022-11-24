#include "main.h"
#include "pros/motors.hpp"

#define SLEW_RATE 10

Drivebase::Drivebase(double gearRatio, double wheelDiameter) {
}

void Drivebase::calculatePower() {
    //init arrays
    //calculate desired power
    //max or min depending on whether greater or smaller
}

int Drivebase::slewControl(int targetPower, int currentPower, int slewRate) {
    int output = targetPower;
    if (output > currentPower + slewRate) {
        output = currentPower + slewRate;
    }
    else if (output < currentPower - slewRate) {
        output = currentPower - slewRate;
    }
    if (output > 127) output = 127;
    if (output < -127) output = -127;

    return output;
}

// void runDrivebaseTask() {

// }