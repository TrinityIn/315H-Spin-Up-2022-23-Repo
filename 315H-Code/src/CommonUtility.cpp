#include "main.h"

/*------------------------ TIMER FUNCTIONS -----------------------------------*/
#define NUM_TIMERS 2
int timers[NUM_TIMERS];

/* Timer Usage:
0: Timing PID
1: Timing for launchers
*/
void resetTimer(int timer)
{
  if (timer > -1 && timer < NUM_TIMERS)
  {
    timers[timer] = pros::millis();
  }
}

int time(int timer)
{
  if (timer > -1 && timer < NUM_TIMERS)
  {
    return pros::millis() - timers[timer];
  }
  else
  {
    return 0;
  }
}

//returns time stored in timer
int getTime(int timer) {
  return timers[timer];
}

//set a beginning time and store it in Timer[timer]
void setTime(int timer)
{
  if (timer > -1 && timer < NUM_TIMERS)
  {
    timers[timer] = pros::millis();
  }
}

/*------------------------- IMU FUNCTIONS ------------------------------------*/

InertialSensor::InertialSensor (uint8_t p) : pros::Imu (p)
{
  port = p;
}
InertialSensor::InertialSensor (uint8_t p, double newScale) : pros::Imu (p)
{
  port = p;
  setScale(newScale);
}

double InertialSensor::getPitch()
{
  return get_roll() + 10.4;
}

int InertialSensor::getPort()
{
  return port;
}

double InertialSensor::getValue()
{
  return (get_rotation() - pos0) * scale;
}
void InertialSensor::setPosition(double pos)
{
  pos0 = get_rotation() - pos;
}
void InertialSensor::set0()
{
  pos0 = get_rotation();
}
void InertialSensor::setScale (double newScale)
{
  scale = 10*newScale;
}
void InertialSensor::addError(double error)
{
  pos0 += (error/scale);
}
void InertialSensor::addAngle(double angle)
{
  pos0 -= angle/scale*10;
}
bool InertialSensor::initialized()
{
  if (get_rotation() == PROS_ERR_F)
    return false;
  return true;
}

/*
Calculation/Numbers:
- motor_get_power gets Watts from the Motor
- motor_get_voltage gets Millivolts from the Motor
- One millivolt is 1/1000th of a volt.
The max voltage for the v5 motor is 12000 millivolts or 12 volts.
The max power for the v5 motor is 127 in power units.
12000/127 is 94.4881889764, or the Voltage Quotient.
Why it works:
-  watts is different from the actual unit of power. voltage solves this issue.
*/
// -----------------------------------------------------------------------------
// int slewControl (int targetPower, int currentPower, int accelCap)
// {
// 	// Returns the new motor value based on current power and the target power
//   int output = targetPower;
//   if (currentPower < targetPower)
//   {
//     if (targetPower - currentPower > accelCap) // If you're behind in "climbing up"
//     {
//       output = currentPower + accelCap;
//     }
//   }
//   else
//   {
//   	if (currentPower - targetPower > accelCap)  // If you're behind in "climbing down"
//     {
//       output = currentPower - accelCap;
//     }
//   }
//   if (output > 127)
//   {
//   	output =  127;
//   }
//   if (output < -127)
//   {
//   	output = -127;
//   }

//   return output;
// }

// int slewControl(pros::Motor *motor, int targetPower, int previousPower, int accelCap)
// {
//   int output = targetPower;

//   if (abs(targetPower-previousPower) > accelCap)
//   {
//     output = previousPower + (accelCap*sgn(targetPower-previousPower));
//   }

//   (*motor).move_voltage(output);

//   //pros::lcd::print(0, "Target: %d Current: %d",targetPower,previousPower);
//   return output;
// }

// int slewControl(pros::Motor *motor, int targetPower, int previousPower, double accelPercent)
// {
//   int output = targetPower;
//   int difference = targetPower-previousPower;
//   int cap = abs(previousPower) * accelPercent;
//   if (cap == 0)
//     cap = 1000;

//   if (abs(difference) > cap)
//   {
//     output = previousPower + (cap*sgn(difference));
//   }

//   (*motor).move_voltage(output);

//   //pros::lcd::print(0, "Target: %d Current: %d",targetPower,previousPower);
//   return output;
// }

//-------------------------------------------------------------------------------------------

int sgn (int value)
{
  return (0 < value) - (value < 0);
}

//-------------------------------------------------------------------------------------------

int convertVoltage (int currentVoltage)
{
  float voltageQuotient = 94.4881889764;
	return round(currentVoltage / voltageQuotient);
}

//-------------------------------------------------------------------------------------------

Button::Button(uint8_t smtPort, uint8_t port)
{
  smartPort = smtPort;
  adiPort = port;
}
Button::Button(uint8_t port)
{
  smartPort = 0;
  adiPort = port;
}
int Button::getValue()
{
  if (smartPort == 0)
  {
    return pros::c::adi_digital_read(adiPort);
  }
  return pros::c::ext_adi_digital_read(smartPort, adiPort);
}

/*------------------------- VISION SENSOR FUNTIONS ---------------------------*/

VisionSensor::VisionSensor(uint8_t port): pros::Vision {port}
{
  set_zero_point(pros::E_VISION_ZERO_CENTER);
  xOffset = 0;
  yOffset = 0;
}
VisionSensor::VisionSensor(uint8_t port, bool rotated): pros::Vision {port}
{
  set_zero_point(pros::E_VISION_ZERO_CENTER);
  xOffset = 0;
  yOffset = 0;
  isRotated = rotated;
}
VisionObject VisionSensor::getLargest()
{
  pros::vision_object_s_t temp[1];
  read_by_size(0, 1, temp);

  return VisionObject(temp[0], xOffset, yOffset, isRotated);
}
VisionObject VisionSensor::getLargest(uint32_t id)
{
  return VisionObject(get_by_sig(0, id), xOffset, yOffset, isRotated);
}
VisionObject VisionSensor::getLargestCombined(uint32_t id)
{
  return VisionObject(VisionObject(get_by_sig(0, id), xOffset, yOffset), VisionObject(get_by_sig(1, id), xOffset, yOffset));
}
void VisionSensor::setSignature(int32_t id, int32_t uMin, int32_t uMax, int32_t uMean, int32_t vMin, int32_t vMax, int32_t vMean, float range, int32_t type)
{
  pros::vision_signature_s_t sig = signature_from_utility (id, uMin, uMax, uMean, vMin, vMax, vMean, range, type);
  set_signature(id, &sig);
}
void VisionSensor::setOffset(int offsetX, int offsetY)
{
  xOffset = offsetX;
  yOffset = offsetY;
}
bool VisionSensor::initialized()
{
  if (clear_led() == PROS_ERR)
    return false;
  return true;
}

//------------------------------------------------------------------------------

VisionObject::VisionObject(pros::vision_object_s_t obj, int xOffset, int yOffset)
{
  width = obj.width;
  height = obj.height;
  signature = obj.signature;
  xCoord = obj.x_middle_coord + xOffset;
  yCoord = obj.y_middle_coord + yOffset;
}

VisionObject::VisionObject(pros::vision_object_s_t obj, int xOffset, int yOffset, bool rotated)
{
  if (!rotated)
  {
    width = obj.width;
    height = obj.height;
    signature = obj.signature;
    xCoord = obj.x_middle_coord + xOffset;
    yCoord = obj.y_middle_coord + yOffset;
  }
  else
  {
    isRotated = true;
    width = obj.height;
    height = obj.width;
    signature = obj.signature;
    xCoord = -obj.y_middle_coord - xOffset;
    yCoord = obj.x_middle_coord - yOffset;
  }
}

// combines 2 VisionObject
// assumes they have the same signatures
VisionObject::VisionObject(VisionObject obj1, VisionObject obj2)
{
  signature = obj1.signature;

  width = abs(obj1.xCoord-obj2.xCoord)+(obj1.width/2.0)+(obj2.width/2.0);
  if (obj1.xCoord > obj2.xCoord)
    xCoord = obj2.xCoord + (width/2);
  else
    xCoord = obj1.xCoord + (width/2);

  height = abs(obj1.yCoord-obj2.yCoord)+(obj1.height/2.0)+(obj2.height/2.0);
  if (obj1.yCoord > obj2.yCoord)
    xCoord = obj2.yCoord + (height/2);
  else
    xCoord = obj1.yCoord + (height/2);
}

bool VisionObject::isObj()
{
  if ((isRotated && abs(xCoord) < 106 && abs(yCoord) < 158) || (!isRotated && abs(xCoord) < 158 && abs(yCoord) < 106))
    return signature <= 7 && signature > 0 && height > 15;
  return false;
}

/*--------------------ULTRASONIC SENSOR ITEMS---------------------------------*/
// Swap two variables
int temp;
#define swap(w, z) temp = w; w = z; z = temp;
#define sort(x, y) if(x > y) { swap(x, y); }

// Median calculation
int calculateMedian(int a, int b, int c, int d, int e){
  sort(a,b);
  sort(d,e);
  sort(a,c);
  sort(b,c);
  sort(a,d);
  sort(c,d);
  sort(b,e);
  sort(b,c);

 return c;
}

#define CM_TO_IN 2.54
UltrasonicSensor::UltrasonicSensor(uint8_t ping, uint8_t echo): pros::ADIUltrasonic {ping, echo}
{
  for (int i = 0; i < 5; i++)
  {
    array[i] = get_value();
  }
  currentValue = get_value();
}

UltrasonicSensor::UltrasonicSensor(pros::ext_adi_port_tuple_t port): pros::ADIUltrasonic {port}
{
  for (int i = 0; i < 5; i++)
  {
    array[i] = get_value();
  }
  currentValue = get_value();
}

double UltrasonicSensor::getValue()
{
  if (currentValue == -1 || currentValue == 0)
  {
    return -1;
  }
  return currentValue/25.4;
}

void UltrasonicSensor::calculateValue()
{
  currentValue = get_value();

  if (currentValue > array[0] + range || currentValue < array[0] - range) {
    if (currentValue < spikeValue + range && currentValue > spikeValue - range) {
      for (int i = 0; i < 5; i++)
      {
        array[i] = spikeValue;
      }
      spikeValue = -100;
    }
    else {
      spikeValue = currentValue;
      currentValue = calculateMedian(array[0], array[1], array[2], array[3], array[4]);
    }
  }

  for (int i = 4; i > 0; i--) {
    array[i] = array[i-1];
  }
  array[0] = currentValue;
}

void UltrasonicSensor::setRange(int newRange)
{
  range = newRange;
}
bool UltrasonicSensor::initialized()
{
  if (get_value() == PROS_ERR)
    return false;
  return true;
}

DistanceSensor::DistanceSensor(uint8_t port) : pros::Distance {port}
{
  for (int i = 0; i < 5; i++)
  {
    array[i] = get();
  }
  currentValue = get();
}

int DistanceSensor::getPort()
{
  return get_port();
}

double DistanceSensor::getValue()
{
  if (currentValue <= 0)
  {
    return -1;
  }
  return currentValue/25.4;
}

void DistanceSensor::calculateValue()
{
  currentValue = get();

  // if it is a spike value
  if (currentValue > array[0] + range || currentValue < array[0] - range)
  {
    // value is within range of last spike
    if (currentValue < spikeValue + range && currentValue > spikeValue - range)
    {
      for (int i = 0; i < 5; i++)
      {
        array[i] = currentValue;
      }
      spikeValue = -10-range;
    }
    // not in range of spike, keep track of the value
    else
    {
      spikeValue = currentValue;
      currentValue = calculateMedian(array[0], array[1], array[2], array[3], array[4]);
    }
  }
  // otherwise clear spikeValue
  else
    spikeValue = -10-range;

  // shift array and assign value
  for (int i = 4; i > 0; i--) {
    array[i] = array[i-1];
  }
  array[0] = currentValue;
}

void DistanceSensor::setRange(int newRange)
{
  range = newRange;
}
bool DistanceSensor::initialized()
{
  if (get() == PROS_ERR)
    return false;
  return true;
}

//------------------------------------------------------------------------------

ColorRange::ColorRange(double small, double large)
{
  min = small;
  max = large;
}
double ColorRange::getMin()
{
  return min;
}
double ColorRange::getMax()
{
  return max;
}

//------------------------------------------------------------------------------

OpticalSensor::OpticalSensor(uint8_t port): pros::Optical{port} {}

bool OpticalSensor::seeColor(ColorRange color)
{
  double max = color.getMax();
  double min = color.getMin();
  double hue = getHue();
  if (min < max)
  {
    if (hue <= max && hue >= min)
    {
      return true;
    }
    return false;
  }
  else
  {
    if ((hue >= min || hue <= max) && hue != -1)
    {
      return true;
    }
    return false;
  }
}

double OpticalSensor::getHue()
{
  double hue = get_hue();
  if (hue == 0)
  {
    return -1;
  }
  return hue;
}
bool OpticalSensor::initialized()
{
  if (get_hue() == PROS_ERR)
    return false;
  return true;
}

//------------------------------------------------------------------------------

Pneumatic::Pneumatic(uint8_t port, bool isReversed): pros::ADIDigitalOut{port}
{
  state = isReversed;
  reversed = isReversed;
}
Pneumatic::Pneumatic(uint8_t port) : pros::ADIDigitalOut{port, false}
{
  state = false;
  reversed = false;
}

bool Pneumatic::isExtended()
{
  if (reversed)
    return !state;
  return state;
}

void Pneumatic::setState(bool newState)
{
  if (reversed)
    state = !newState;
  else
    state = newState;
  set_value(state);
}

void Pneumatic::toggleState()
{
  if (reversed)
    setState(state);
  else
    setState(!state);
}

bool Pneumatic::getState()
{
  return isExtended();
}