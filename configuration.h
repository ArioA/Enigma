#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "rotor.h"

//Precondition: a[] is an array of size length. errnum is the error tracker.
//Postcondition: a[] is filled with numbers 
//from the position file filename.
void readPositions(int* a, const int& length, const char* filename,
		   int& errnum);

//Precondition: rot_ptr is a pointer to the rotor which is to be configured.
//Position is the position which the rotor in question is to be configured to.
//Postcondition: *rot_ptr is rotated position times. So that the position
//indexed letter is aligned with the 'absolute A'.
void configurePosition(Rotor* rot_ptr, const int& position);

#endif
