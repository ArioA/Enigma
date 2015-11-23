#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "rotor.h"

void readPositions(int* a, const int& length, const char* filename,
		   int& errnum);
void configurePosition(Rotor* rot_ptr, const int& position);

#endif
