#ifndef _COMMONUTIL_H_
#define _COMMONUTIL_H_

#define ACCELCAPNORMAL 17 // 17 = 20 ms * 0.83333 steps per ms rounded
#define NORMALREADINGRATE 20
#define ACCELCAPSPECIAL 4 // 4 = 5 ms * 0.83333 steps per ms rounded
#define SPECIALREADINGRATE 5
#define V5READINGRATE 10

//------------------------------------------------------------------------------

int slewControl (int targetPower, int currentPower, int accelCap);
int slewControl(pros::Motor *motor, int targetPower, int previousPower, int accelCap);
int slewControl(pros::Motor *motor, int targetPower, int previousPower, double accelPercent);

int sgn (int value);
int convertVoltage(int currentVoltage);

void resetTimer(int timer);
int time(int timer);
void setTime(int timer, int time);

class InertialSensor : public pros::Imu
{
  public:
    InertialSensor (uint8_t p);
    InertialSensor (uint8_t p, double newScale);

    void set0();
    void setPosition(double pos);
    double getValue();

    void setScale (double newScale);
    void addError(double error);
    void addAngle(double angle);
    bool initialized();
    int getPort();

    double getPitch();

  private:
    double scale = 10;
    double pos0 = 0;
    int port;
};

int calculateMedian(int a, int b, int c, int d, int e);

class UltrasonicSensor : private pros::ADIUltrasonic
{
  public:
    UltrasonicSensor(uint8_t ping, uint8_t echo);
    UltrasonicSensor(pros::ext_adi_port_tuple_t port);

    void calculateValue();
    double getValue();
    void setRange(int newRange);
    bool initialized();

  private:
    int array[5];
    int currentValue;
    int spikeValue = -100;
    int range = 100;
};

class DistanceSensor : private pros::Distance
{
  public:
    DistanceSensor(uint8_t port);

    void calculateValue();
    double getValue();
    void setRange(int newRange);
    bool initialized();
    int getPort();

  private:
    int array[5];
    int currentValue;
    int spikeValue = -100;
    int range = 100;
};

class Button
{
  public:
    Button(uint8_t smtPort, uint8_t port);
    Button(uint8_t port);

    int getValue();
    bool initialized();
  private:
    std::uint8_t smartPort;
    std::uint8_t adiPort;
};

class VisionObject
{
  public:
    VisionObject(pros::vision_object_s_t obj, int xOffset, int yOffset);
    VisionObject(pros::vision_object_s_t obj, int xOffset, int yOffset, bool rotated);
    VisionObject(VisionObject obj1, VisionObject obj2);

    bool isObj ();

    int xCoord;
    int yCoord;
    int width;
    int height;
    int signature;
  private:
    bool isRotated = false;
};

class VisionSensor : public pros::Vision
{
  public:
    VisionSensor(uint8_t port);
    VisionSensor(uint8_t port, bool rotated);

    VisionObject getLargest();
    VisionObject getLargest(uint32_t id);
    VisionObject getLargestCombined(uint32_t id);
    void setSignature(int32_t id, int32_t u_min, int32_t u_max, int32_t u_mean, int32_t v_min, int32_t v_max, int32_t v_mean, float range, int32_t type);
    void setOffset(int offsetX, int offsetY);
    bool initialized();

  private:
    int xOffset;
    int yOffset;
    bool isRotated = false;
};

class ColorRange
{
  public:
    ColorRange(double small, double large);
    double getMin();
    double getMax();

  private:
    double min;
    double max;
};

class OpticalSensor : public pros::Optical
{
  public:
    OpticalSensor(uint8_t port);
    bool seeColor(ColorRange color);
    double getHue();
    bool initialized();
};

class Pneumatic : protected pros::ADIDigitalOut
{
  public:
    Pneumatic(uint8_t port, bool isReversed);
    Pneumatic(uint8_t port);

    bool isExtended();
    void setState(bool newState);
    void toggleState();
    bool getState();
  protected:
    bool state;
    bool reversed;
};
//------------------------------------------------------------------------------

#endif