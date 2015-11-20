#ifndef HELPER_H
#define HELPER_H

#include"rotor.h"
#include"plugboard.h"
#include"reflector.h"

int digit_to_int(char digit);
char int_to_digit(int number);
char int_to_letter(int number);
int letter_to_int(char alpha);
bool isDigit(char digit);
bool isLetter(char character);
bool isWhiteSpace(char character);
int validConfig(int nums[26]);
int inverseMapping(int* array, int length, int output);
int readNumber(std::istream &inflow, char& digit, const char* filename);
void passThroughEnigma(Rotor** rotorList, int rotors,
		       Plugboard* pb, Reflector* rf, int& n);
void encrypt(Rotor** linkedRotors, int number_of_rotors, Plugboard* pbPtr,
	     Reflector* rfPtr, int& errnum);
void encrypt(Plugboard* pbPtr, Reflector* rfPtr, int& errnum);

#endif
