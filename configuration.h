#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"

void readPositions(int* a, int length, char* filename);
void configurePosition(Rotor* rot_ptr, int position);
void passThroughEnigma(Rotor** rotorList, int rotors,
	Plugboard* pb, Reflector* rf, int& n);
#endif
