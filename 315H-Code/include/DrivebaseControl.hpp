#ifndef _DRIVEBASE_CONTROL_HPP_
#define _DRIVEBASE_CONTROL_HPP_

class Drivebase {
    public:
        Drivebase(double gearRatio, double wheelDiameter);
        void calculatePower();
    private:
        int lPower;
        int rPower;
        
        double gearRatio;
        double wheelDiameter;
};

// void runDrivebaseTask();

#endif