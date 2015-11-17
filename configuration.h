#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "rotor.h"

void readPositions(int* a, int length, char* filename);
void configurePosition(Rotor* rot_ptr, int position);

#endif
