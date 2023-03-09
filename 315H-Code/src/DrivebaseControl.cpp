#include "main.h"
#include "pros/llemu.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

#define SLEW_RATE 900
#define MAX_VOLTAGE 12000
#define LEFT_Y pros::E_CONTROLLER_ANALOG_LEFT_Y
#define RIGHT_X pros::E_CONTROLLER_ANALOG_RIGHT_X

Drivebase::Drivebase(double gearRat, double degrees) {
    gearRatio = gearRat;
    encoderPerInch = degrees;
}

void Drivebase::resetEncoders() {
    leftDrive.tare_position();
    rightDrive.tare_position();
}

double Drivebase::getAverageEncoderValue() {
    double sum = 0;
    std::vector<double> leftVector = leftDrive.get_positions();
    std::vector<double> rightVector = rightDrive.get_positions();
    for (int i = 0; i < leftVector.size(); i++) {
        sum += leftVector.at(i) + rightVector.at(i);
    }

    return sum / (leftDrive.get_positions().size() * 2);
}

void Drivebase::driveDistance(bool forward, int distance, int degrees, int minSpeed){
    
    //constants
    double turnP = 0.4;
    
    double encoderDistance = distance * encoderPerInch/(gearRatio);
    double rotationalError = 0;
    
    resetEncoders();
    pros::lcd::clear();

    if (forward) {
    //forward only
        while(getAverageEncoderValue() < encoderDistance && !teleop) {
            pros::lcd::print(0, "Encoder values: %d", getAverageEncoderValue());
            rotationalError = imu.getValue() - (degrees * 10);
            leftDrive.move(fmax(minSpeed, minSpeed - rotationalError * turnP));
            rightDrive.move(fmax(minSpeed, minSpeed + rotationalError * turnP));
        }
    }
    else {
        while(getAverageEncoderValue() > (encoderDistance * -1) && !teleop) {
            pros::lcd::print(0, "Encoder values: %d", getAverageEncoderValue());
            rotationalError = imu.getValue() - (degrees * 10);
            leftDrive.move(fmin(-minSpeed, -minSpeed - rotationalError * turnP));
            rightDrive.move(fmin(-minSpeed, -minSpeed + rotationalError * turnP));
        }
    }
    leftDrive.move(0);
    rightDrive.move(0);

}

void Drivebase::driveToWall(bool forward, int distanceFromWall, int degrees, int minSpeed){
    
    //constants
    double turnP = 0.4;
    
    double distanceError = frontDistance.get() - distanceFromWall;
    double rotationalError = 0;
    
    resetEncoders();
    pros::lcd::clear();

    if (forward) {
        while(frontDistance.get() > distanceFromWall && !teleop) {
            pros::lcd::print(0, "Distance from wall: %d", frontDistance.get());
            rotationalError = imu.getValue() - (degrees * 10);
            leftDrive.move(fmax(minSpeed, minSpeed - rotationalError * turnP));
            rightDrive.move(fmax(minSpeed, minSpeed + rotationalError * turnP));
        }
    }
    else {
        while(backDistance.get() > distanceFromWall && !teleop) {
            pros::lcd::print(0, "Distance from wall (back): %d", backDistance.get());
            rotationalError = imu.getValue() - (degrees * 10);
            leftDrive.move(fmin(-minSpeed, -minSpeed - rotationalError * turnP));
            rightDrive.move(fmin(-minSpeed, -minSpeed + rotationalError * turnP));
        }
    }
    leftDrive.move(0);
    rightDrive.move(0);

}

void Drivebase::turnPID(int desiredTurnValue, int speed) {
    //imu.reset();
    imu.set0();
    //imu.tare_heading();
    
    // settings
    double kP = 0.4; //0.4
    double kI = 0.005; //0.0005;  
    double kD = 0.9; //0.85; 

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

    int maxTimer = pros::millis();
    do{
        //get positions of both motor group
        currentHeading = imu.getValue();
        //dugcount+=1;

        pros::lcd::clear();
        //pros::lcd::print(1,"%d", dugcount);
        

        //Proportional
        error = desiredTurnValue - currentHeading;

        //Derivative
        derivative = error - prevError;

        //Integral: only add to totalError if error is less than 10 degrees off desired value
        if (fabs(error) < 100) 
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

        if (fabs(error) < 7 && fabs(derivative) < 0.5) {
            timeTracker++;
        }
        else {
            timeTracker = 0;
        }

        // if (fabs(error) < 7 && timeTracker == 0) {
        //     time = pros::millis(); 
        //     timeTracker = 1;
        // }
        if(pros::millis() - maxTimer > 2000) {
            sentinel = 1;
            pros::lcd::print(6, "sentinel: max time exceeded (>2000)");
        }
        if(timeTracker == 30) {
            sentinel = 1;
            pros::lcd::print(6,"sentinel: %d", sentinel);
        }

        pros::lcd::print(3,"current heading: %.2f", currentHeading);
        pros::lcd::print(4,"imu value: %0.2f", imu.getValue());
        pros::lcd::print(5,"error/10%0.2f", error/10);
        pros::lcd::print(6,"sentinel: %d", sentinel);

    } while(sentinel == 0 && !teleop); //fabs(error) > 5

    leftDrive.move(0);
    rightDrive.move(0);
    return;
}

void Drivebase::offsetTurnPID(int desiredTurnValue, int speed) {
    
    // settings
    double kP = 0.4; //0.4
    double kI = 0.005; //0.0005;  
    double kD = 0.8; //0.85; 

    // set desired value to parameter 
    desiredTurnValue *= 10;
    double margin = fabs((desiredTurnValue - imu.getValue())/4);
    //desiredTurnValue -= imu.getValue();
    
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

    int maxTimer = pros::millis();
    do{
        //get positions of both motor group
        currentHeading = imu.getValue();
        //dugcount+=1;

        pros::lcd::clear();
        //pros::lcd::print(1,"%d", dugcount);
        

        //Proportional
        error = desiredTurnValue - currentHeading;

        //Derivative
        derivative = error - prevError;

        //Integral: only add to totalError if error is less than 10 degrees off desired value
        if (fabs(error) < 100) 
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

        if (fabs(error) < margin && fabs(derivative) < 0.5) {
            timeTracker++;
        }
        else {
            timeTracker = 0;
        }

        // if (fabs(error) < 7 && timeTracker == 0) {
        //     time = pros::millis(); 
        //     timeTracker = 1;
        // }
        if(pros::millis() - maxTimer > 2000) {
            sentinel = 1;
            pros::lcd::print(6, "sentinel: max time exceeded (>2000)");
        }
        if(timeTracker == 30) {
            sentinel = 1;
            pros::lcd::print(6,"sentinel: %d", sentinel);
        }

        pros::lcd::print(3,"current heading: %.2f", currentHeading);
        pros::lcd::print(4,"imu value: %0.2f", imu.getValue());
        pros::lcd::print(5,"error/10%0.2f", error/10);
        pros::lcd::print(6,"sentinel: %d", sentinel);

    } while(sentinel == 0 && !teleop); //fabs(error) > 5

    leftDrive.move(0);
    rightDrive.move(0);
    return;
}


void Drivebase::gpsTurnToXY(double targetX, double targetY, bool offset)
{
  double targetHeading, turnC, turnCC;
  getPosition();
  //Offset Calculations based on if offset or not
  if(offset)
  {
    targetHeading = atan2(targetX - switchx, targetY - switchy) * 180 / M_PI;
    if(targetHeading < 0)
    {
      targetHeading = 360 - fabs(targetHeading);
    }
    turnC = targetHeading - offgpsHeading;
    turnCC = turnC-360;
  }
  //Non-offset calculations
  else
  {
    targetHeading = atan2(targetX - rawx, targetY - rawy) * 180 / M_PI;
    targetHeading = 360 - fabs(targetHeading);
    turnC = targetHeading - rawgpsHeading;
    turnCC = turnC-360;
  }
  //Stuff outside of condition - non dependent on offset
  if(fabs(turnC) >= fabs(turnCC))
  {
    turnPID(turnC - 360, 90);
  }
  else
  {
    turnPID(turnC, 90);
  }
}

void Drivebase::gpsMoveToXY(double targetX, double targetY, int power, bool offset)
{
  double errorDistance;
  getPosition();
  gpsTurnToXY(targetX, targetY, offset);
  getPosition();
  if(offset)
  {
    errorDistance = sqrt(pow(targetX - switchx, 2) + pow(switchy - rawy, 2));
  }
  else
  {
    errorDistance = sqrt(pow(targetX - rawx, 2) + pow(targetY - rawy, 2));
  }
  double targetHeading = atan2(targetX - switchx, targetY - switchy) * 180 / M_PI;
  //Convert from centimeters back into inches
  errorDistance /= 2.54;
  driveDistance(true, errorDistance, targetHeading, power);
}

void Drivebase::getPosition()
{
  // will get GPS reading, and stored in struct.
  //status.X and status.Y will report out coordiante in (x,y), unit is meter.
  // the range is [-1.8, 1.8]
  // raw x and y values are in centimeters not inches
  rawgpsHeading = gps.get_heading();
  offgpsHeading = rawgpsHeading + 90.00;
  offgpsHeading = fmod(offgpsHeading, 360.00);
  status = gps.get_status();
  rawx = status.x * 100;
  rawy = status.y * 100;
  switchx = -rawx;
  tempX = switchx;
  switchx = rawy;
  switchy = tempX;
  pros::lcd::print(3, "Offset X Position: %f", switchx);
  pros::lcd::print(4, "Offset Y Position: %f", switchy);
  pros::lcd::print(1, "Raw X Position: %f", rawx);
  pros::lcd::print(2, "Raw Y Position: %f", rawy);
  pros::lcd::print(6, "Raw Gps Heading: %f", rawgpsHeading);
  pros::lcd::print(5, "Offset Gps Heading: %f", offgpsHeading);
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
    pros::lcd::print(5, "rollerPos: %0.2f", roller.get_position());

    previousRPower = slewControl(motorArray[0], rVoltage, previousRPower, SLEW_RATE);
    previousLPower = slewControl(motorArray[1], lVoltage, previousLPower, SLEW_RATE);

    pros::lcd::print(2, "verticalPower: %d", verticalPower);
    pros::lcd::print(3, "turnPower: %d", turnPower);
    pros::lcd::print(4, "state: %d", expanderState);

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

void Drivebase::goForTime(int speed, int msec) {
    leftDrive.move(speed);
    rightDrive.move(speed);
    pros::delay(msec);
    leftDrive.move(0);
    rightDrive.move(0);
}
// void runDrivebaseTask() {

// }