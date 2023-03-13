#include "RollerControl.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"

#define NUM_PHASE 3
#define HOLD_POWER 0

//global position indicator variables
int phase = 0; //0 is nothing, 1 is near goal, 2 is outside barrier, 3 is halfcourt/max
int targetPosition = -1;
int tuningDistance = 0;

int pitch = 0;
int roll = 0;
int yaw = 0;
int rotation = 0;

//virtual buttons
bool shootBtn = false;
bool farPrimeBtn = false;
bool twoDiscBtn = false;

//setup variables
bool shootBtnPressed = false;
bool phaseBtn = false;
bool startPunchTask = true;
bool tuningUpBtnPressed = false;
bool tuningDownBtnPressed = false;
bool primed = true;
//bool down = cataPrime.get_value();

void phasePrime() {
    int target = 0;
    switch(phase) {
        case 1:
            target = 4050 + tuningDistance;
            break;
        case 2:
            target = 4500 + tuningDistance;
            break;
        case 3:         
            target = 6500;
            break;
    }
    double prevPosition = puncher.get_position();
    while (puncher.get_position() < target && !(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) && !shootBtn) {
        puncher.move_voltage(12000);
        //down = cataPrime.get_value();
        double prevPosition = puncher.get_position();
        pros::delay(10);
        //pros::lcd::print(0, "%.3f", fabs(puncher.get_position() - prevPosition));
        // if (fabs(puncher.get_position() - prevPosition) < 0.01) {
        //     break;
        // }
        
    }
    //catapult.move(-50);
    //pros::delay(50);
    puncher.move(HOLD_POWER);
    return;
}
void prime(int targetPosition) {
    double prevPosition = puncher.get_position();
    while (puncher.get_position() < targetPosition && !(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) && !shootBtn) {
        puncher.move_voltage(12000);
        //down = cataPrime.get_value();
        double prevPosition = puncher.get_position();
        pros::delay(10);
        //pros::lcd::print(0, "%.3f", fabs(puncher.get_position() - prevPosition));
        // if (fabs(puncher.get_position() - prevPosition) < 0.01) {
        //     break;
        // }
        
    }
    targetPosition = -1;
    //catapult.move(-50);
    //pros::delay(50);
    puncher.move(HOLD_POWER);
    return;
}

void fire() {
    puncher.move(0);
    stopRollerBtn = true;
    pros::delay(25);
    
    //"freezing" imu values
    pitch = imu.get_pitch();
    roll = imu.get_roll();
    yaw = imu.get_yaw();
    rotation = imu.get_rotation();


    pros::delay(25);
    puncherRelease.set_value(true);
    pros::delay(200);
    puncherRelease.set_value(false);
    //pros::lcd::print(0, "fire");    
    pros::delay(10);

    //resetting imu values to before the shooting
    imu.set_pitch(pitch);
    imu.set_roll(roll);
    imu.set_yaw(yaw);
    imu.set_rotation(rotation);

}

void operatePuncher(void*) {
    while (true) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !shootBtnPressed) {
            shootBtnPressed = true;
            //checks if the catapult starts from a primed position
            fire();
            puncher.tare_position();
            phase = 1;
            phasePrime();
        }
        // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     puncher.move(127);
        // }
        else if (!shootBtnPressed) {
            puncher.move(HOLD_POWER);
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !phaseBtn) {
            phaseBtn = true;
            phase = std::min(phase + 1, NUM_PHASE);
            phasePrime();
        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            phaseBtn = false;
        }

        //manual tuning functions
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !tuningUpBtnPressed) {
            tuningUpBtnPressed = true;
            tuningDistance += 50;

        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            tuningUpBtnPressed = false;

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && !tuningDownBtnPressed) {
            tuningDownBtnPressed = true;
            tuningDistance -= 50;

        }
        else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
            tuningDownBtnPressed = false;

        shootBtnPressed = false;


        //virtual btns
        if (shootBtn) {
            fire();
            phase = 1;
            puncher.tare_position();
            shootBtn = false;
            phasePrime();
        }
        if (farPrimeBtn) {
            phase = 3;
            phasePrime();
            farPrimeBtn = false;
        }
        if (twoDiscBtn) {
            phase = 2;
            phasePrime();
            twoDiscBtn = false;
        }
        if (targetPosition > 0) {
            prime(targetPosition);
            targetPosition = -1;
        }
        
        pros::delay(10);
    }
}

void momentumShot(int speed) {
    leftDrive.move(speed);
    rightDrive.move(speed);
    pros::delay(100);
    shootBtn = true;
    pros::delay(200);
    leftDrive.move(0);
    rightDrive.move(0);
}

void runPunchTask() {
    //shootBtn = false;
    if (startPunchTask) {
        puncher.tare_position();
        pros::Task runPuncher(operatePuncher);
        startPunchTask = false;
    }
}