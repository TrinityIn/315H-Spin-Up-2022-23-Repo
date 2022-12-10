#include "main.h"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

#define SLEW_RATE 2000
#define MAX_VOLTAGE 12000
#define LEFT_Y pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_X pros::E_CONTROLLER_ANALOG_RIGHT_X

Drivebase::Drivebase(double gearRat, double degrees) {
    gearRatio = gearRat;
    encoderPerInch = degrees;
}

/*
void Drivebase::driveDistance(int distance, int degrees){
    while(distance ) {
        leftDrive.move(0);
        rightDrive.move(0);
    }
}*/

/*
void Drivebase::autoTurnPID(double degrees, int maxSpeed)
{
  float degreesX10 = 10 * degrees;
  int direction = sgn(degreesX10-imu.getValue());
  float margin = fabs(degreesX10 - imu.getValue()) / 4.0;

  // PID variables
  float kP = 0.4;
  float kD = 0.75; // .75
  int counter = 0;

  // acceleration
  int setSpeed = minSpeed;
  while (setSpeed < maxSpeed/2)
  {
    //autoTurnCalibrate(setSpeed * direction);
    setSpeed += progAccelCap;

    pros::delay(10);
  }

  // use PID for the rest
  double currentDegrees = imu.getValue();
  double error = degreesX10 - currentDegrees;
  double previousError = degreesX10 - currentDegrees;
  double derivative = 0;
  int output;

  while (counter < turningCounter)
  {
    // Final Output
    output = kP * error + kD * derivative;
    if (abs(output) > maxSpeed) {
      output = maxSpeed * sgn(output);
    }


    pros::delay(10);

    currentDegrees = imu.getValue();
    error = degreesX10 - currentDegrees;
    derivative = error - previousError;
    previousError = error;

    // checks if derivative is small enough to increase the counter
    if (fabs(derivative) < turningDerivativeRange && fabs(error) < margin)
    //if (fabs(error) < margin && isMoving(1))
      counter++;
    // if turnCanUseError then if error is small enough then exit the loop
    else if (turnCanUseError && fabs(error) < 10)
      break;
    else
      counter = 0;
  }

  setWheelSpeed(0);
} */

void Drivebase::turnPID(int desiredTurnValue, int speed) {
    //imu.reset();
    imu.set0();
    imu.tare_heading();
    
    // settings
    double kP = 0.4;
    double kI = 0.00005;  
    double kD = 0.75;

    // set desired value to parameter 
    desiredTurnValue *= 10;
    
    // value of the current heading
    double currentHeading;
    // contains PD output
    double turnMotorPower;

    double error; // sensorValue - desiredValue : positional value, dx
    double prevError = 0; // position 20ms ago
    double totalError = 0; // totalError = totalError + error
    double derivative; //error  - prevError : Speed
    pros::lcd::print(2,"%0.2f", imu.getValue());

    //int dugcount=0;
    int sentinel = 0;
    int time = 0;// timer for 300 ms
    int timeTracker = 0;

    do{
        //get positions of both motor group
        currentHeading = imu.getValue() + 10;
        //dugcount+=1;

        pros::lcd::clear();
        //pros::lcd::print(1,"%d", dugcount);
        pros::lcd::print(3,"current heading: %.2f", currentHeading);
        pros::lcd::print(4,"imu value: %0.2f", imu.getValue());
        pros::lcd::print(5,"error/10%0.2f", error/10);
        pros::lcd::print(6,"sentinel: %d", sentinel);

        //Proportional
        error = desiredTurnValue - currentHeading;

        //Derivative
        derivative = error - prevError;

        //Integral
        totalError += error;

        //PD controller
        turnMotorPower = fmin(abs((int) ((error * kP) + (derivative * kD) + (totalError * kI))), speed);
        /*if(error < 0) {
            turnMotorPower *= -1;
        }*/
        //pros::lcd::print(3, "Motor Power: %d", turnMotorPower);

        leftDrive.move(sgn(error) * turnMotorPower);
        rightDrive.move(-sgn(error) * turnMotorPower);

        prevError = error;
        pros::delay(10);

        if (fabs(error) < 7 && timeTracker == 0) {
            time = pros::millis(); 
            timeTracker = 1;
        }
        if(pros::millis() - time >= 3000) {
            sentinel = 1;
            pros::lcd::print(6,"sentinel: %d", sentinel);
        }

    } while(sentinel == 0); //fabs(error) > 5

    leftDrive.move(0);
    rightDrive.move(0);
}

void Drivebase::calculatePower() {
    //get desired speed
    verticalPower = getVerticalPower(master.get_analog(LEFT_Y));
    turnPower = getTurnPower(master.get_analog(RIGHT_X));
    
    //calculate desired power
    lVoltage = verticalPower + turnPower;
    rVoltage = verticalPower - turnPower;

    int scaleFactor = fmax(abs(lVoltage), fmax(MAX_VOLTAGE, abs(rVoltage)));

    //multiplying by (MAX_VOLTAGE/scaleFactor) rounds down to 0 when scaleFactor > MAX_VOLTAGE
    lVoltage = (lVoltage * MAX_VOLTAGE)/scaleFactor; 
    rVoltage = (rVoltage * MAX_VOLTAGE)/scaleFactor;

    pros::lcd::clear();
    pros::lcd::print(0, "lVoltage: %d", lVoltage);
    pros::lcd::print(1, "rVoltage: %d", rVoltage);
    pros::lcd::print(5, "optical: %0.2f", optRoller.get_hue());

    previousRPower = slewControl(motorArray[0], rVoltage, previousRPower, SLEW_RATE);
    previousLPower = slewControl(motorArray[1], lVoltage, previousLPower, SLEW_RATE);

    pros::lcd::print(2, "verticalPower: %d", verticalPower);
    pros::lcd::print(3, "turnPower: %d", turnPower);
    pros::lcd::print(4, "state: %d", state);

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