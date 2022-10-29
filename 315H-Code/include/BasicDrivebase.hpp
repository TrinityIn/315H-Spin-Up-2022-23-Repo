#ifndef _BASIC_DRIVEBASE_HPP_
#define _BASIC_DRIVEBASE_HPP_

#include "pros/motors.hpp"
class BasicDrivebase {
    public:
        BasicDrivebase(pros::Motor_Group leftDrive, pros::Motor_Group rightDrive);
        void calculatePower();
    private:
        int lPower;
        int rPower;

};

#endif