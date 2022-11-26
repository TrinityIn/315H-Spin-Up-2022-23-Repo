#include "main.h"
#include "pros/motors.hpp"

#define SLEW_RATE 900
#define MAX_VOLTAGE 12000
#define LEFT_Y pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_X pros::E_CONTROLLER_ANALOG_RIGHT_X

Drivebase::Drivebase(double gearRat, double degrees) {
    gearRatio = gearRat;
    encoderPerInch = degrees;
}

void Drivebase::turnPID(int degrees) {
    imu.reset();
    
    // settings
    double kP = 0.0;
    double kI = 0.0;
    double kD = 0.0;

    // set desired value to parameter 
    int desiredTurnValue = degrees;
    // value of the current heading
    int currentHeading;
    // contains PD output
    int turnMotorPower;

    int error; // sensorValue - desiredValue : positional value, dx
    int prevError = 0; // position 20ms ago
    int totalError = 0; // totalError = totalError + error
    int derivative; //error  - prevError : Speed

    while(error>1){
        //get positions of both motor group
        currentHeading = imu.get_heading();

        //Proportional
        error = currentHeading - desiredTurnValue;

        //Derivative
        derivative = error - prevError;

        //Integral
        //totalError += error;

        //PD controller
        turnMotorPower = (error * kP) + (derivative * kD);

        leftDrive.move(turnMotorPower);
        rightDrive.move(turnMotorPower);

        prevError = error;
        pros::delay(20);
    }
}

void Drivebase::calculatePower() {
    //get desired speed
    verticalPower = getVerticalPower(master.get_analog(LEFT_Y));
    turnPower = getTurnPower(master.get_analog(RIGHT_X));
    
    //calculate desired power
    lVoltage = verticalPower + turnPower;
    rVoltage = verticalPower - turnPower;

    int scaleFactor = fmax(abs(lVoltage), fmax(MAX_VOLTAGE, abs(rVoltage)));

    lVoltage *= MAX_VOLTAGE/scaleFactor;
    rVoltage *= MAX_VOLTAGE/scaleFactor;

    pros::lcd::clear();
    pros::lcd::print(0, "lVoltage: %d", lVoltage);
    pros::lcd::print(1, "rVoltage: %d", rVoltage);

    previousRPower = slewControl(motorArray[0], rVoltage, previousRPower, SLEW_RATE);
    previousLPower = slewControl(motorArray[1], lVoltage, previousLPower, SLEW_RATE);

    pros::lcd::print(2, "previousRPower: %d", previousRPower);
    pros::lcd::print(3, "previousLPower: %d", previousLPower);

}

int Drivebase::slewControl(pros::Motor_Group* motor, int targetPower, int currentPower, int slewRate) {
    int output = targetPower;
    if (output > currentPower + slewRate) {
        output = currentPower + slewRate;
    }
    else if (output < currentPower - slewRate) {
        output = currentPower - slewRate;
    }
    if (output > 12000) output = 12000;
    if (output < -12000) output = -12000;

    (*motor).move_voltage(output);
    return output;
}

int Drivebase::getVerticalPower(int verticalInput) {
    if (verticalInput < 0) {
        return -1 * speed[(int) fmin(127, -1 * verticalInput)];
    }
    else {
        return speed[(int) fmin(127, verticalInput)];
    }
}

int Drivebase::getTurnPower(int turnInput) {
    if (turnInput < 0) {
        return -1 * turn[(int) fmin(127, -1 * turnInput)];
    }
    else {
        return turn[(int) fmin(127, turnInput)];
    }
}

// void runDrivebaseTask() {

// }