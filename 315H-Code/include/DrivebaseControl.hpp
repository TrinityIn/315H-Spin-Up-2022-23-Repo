#ifndef _DRIVEBASE_CONTROL_HPP_
#define _DRIVEBASE_CONTROL_HPP_

#include "pros/motors.hpp"

class Drivebase {
    public:
        Drivebase(double gearRat, double degrees);

        void resetEncoders();
        double getAverageEncoderValue();  
        
        void turnPID(int desiredTurnValue, int speed);
        void offsetTurnPID(int desiredTurnValue, int speed);
        void driveDistance(bool forward, int distance, int degrees, int minSpeed);
        void driveToWall(bool forward, int distanceFromWall, int degrees, int minSpeed);


        void gpsTurnToXY(double targetX, double targetY, bool offset);
        void gpsMoveToXY(double targetX, double targetY, int power, bool offset);
        void getPosition();

        pros::c::gps_status_s_t status;
        double rawx,rawy,tempX,switchx,switchy;
        double rawgpsHeading, offgpsHeading;

        void calculatePower();
        void goForTime(int speed, int msec);

        pros::Motor_Group *motorArray[2] = {&rightDrive, &leftDrive};
        int previousLPower = 0;
        int previousRPower = 0;

    private:
        
        //drive powers
        int lVoltage; //left drive output (mV)
        int rVoltage; //right drive output (mV)
        
        //input values
        int verticalPower; //controls forward/backward movement
        int turnPower; //controls turning
        
        double gearRatio;
        double encoderPerInch;

        int slewControl(pros::Motor_Group* motor, int targetPower, int currentPower, int slewRate);
        int getVerticalPower(int verticalInput);
        int getTurnPower(int turnInput);

        int speed[128] = {
            0,  
            0,      0,      0,      0,      0,      0,      0,      0,      0,      0,    //10
            2362,   2362,   2362,   2362,   2362,   2362,   2362,   2362,   2362,   2362, //20
            2362,   2362,   2362,   2362,   2362,   2457,   2551,   2646,   2740,   2835, //30
            2929,   3024,   3118,   3213,   3307,   3402,   3496,   3591,   3685,   3780, //40
            3874,   3969,   4063,   4158,   4252,   4347,   4441,   4535,   4630,   4724, //50
            4819,   4913,   5008,   5102,   5197,   5291,   5386,   5480,   5575,   5669, //60
            5764,   5858,   5953,   6047,   6142,   6236,   6331,   6425,   6520,   6614, //70
            6709,   6803,   6898,   6992,   7087,   7181,   7276,   7370,   7465,   7559, //80
            7654,   7748,   7843,   7937,   8032,   8126,   8221,   8315,   8409,   8504, //90
            8598,   8693,   8787,   8882,   8976,   9071,   9165,   9260,   9354,   9449, //100
            9543,   9638,   9732,   9827,   9921,  10016,  10110,  10205,  10299,  10394, //110
            10488,  10583,  10677,  10772,  10866,  10961,  11055,  11150,  11244,  11339, //120
            11433,  11528,  11622,  11717,  11811,  11906,  12000
           
        };

        int turn [128] = {
            0, //0
            0,      0,      0,      0,      0,      0,      0,      0,      0,      0, //10
            1500,   1500,   1500,   1500,   1500,   1500,   1500,   1500,   1500,   1500, //20
            1500,   1500,   1500,   1500,   1500,   1500,   1600,   1700,   1800,   1900, //30
            2000,   2200,   2457,   2646,   2835,   3024,   3213,   3402,   3591,   3780, //40
            3874,   3969,   4063,   4158,   4252,   4347,   4441,   4535,   4630,   4724, //50
            4819,   4913,   5008,   5102,   5197,   5291,   5386,   5480,   5575,   5575, //60
            5669,   5669,   5764,   5764,   5858,   5858,   5953,   5953,   6047,   6047, //70
            6142,   6142,   6236,   6236,   6331,   6331,   6425,   6425,   6520,   6520, //80
            6614,   6614,   6709,   6709,   6803,   6803,   6898,   6898,   6992,   6992, //90
            7087,   7087,   7181,   7181,   7276,   7276,   7370,   7370,   7465,   7465, //100
            7559,   7559,   7654,   7654,   7748,   7748,   7843,   7843,   7937,   7937, //110
            8032,   8032,   8126,   8126,   8221,   8221,   8315,   8315,   8409,   8500, //120
            8504,   9000,   9000,   9000,   9000,   9000,   9000, //127
        };
};

// void runDrivebaseTask();

#endif