#ifndef _BASIC_DRIVEBASE_HPP_
#define _BASIC_DRIVEBASE_HPP_

class BasicDrivebase {
    public:
        virtual void calculatePower();
    private:
        int lPower;
        int rPower;

};

#endif