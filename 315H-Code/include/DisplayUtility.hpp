#ifndef _DISPLAYUTILITY_HPP_
#define _DISPLAYUTILITY_HPP_

#include "pros/apix.h"

const int NUM_SELECTION = 12;
extern int autonSelected;

void setStyle (lv_obj_t * btn, int styleType);
void initializeGUI();

#endif