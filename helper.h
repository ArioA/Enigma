#ifndef HELPER_H
#define HELPER_H

#include"rotor.h"
#include"plugboard.h"
#include"reflector.h"

//===========================Conversion Functions=======================

//Precondition: digit is a digit (0, 1, ..., 9).
//Returns digit as an integer.
int digit_to_int(const char& digit);

//Precondition: number is between 0 and 9.
//Returns number as a char.
char int_to_digit(const int& number);

//Precondition: number is between 0 and 25.
//Returns alphabetic equivalent as capital letter.
char int_to_letter(const int& number);

//Precondition: alpha is a capital letter.
//Returns integer representation of alpha.
int letter_to_int(const char& alpha);

//=======================Checking Functions=========================

//Precondition: digit is any character.
//Returns true is digit is a digit, false otherwise.
bool isDigit(const char& digit);

//Precondition: character is an initialised char variable.
//Returns true if character is a capital letter. False otherwise.
bool isCapital(const char& character);

/*Precondition: character is an initialised char.
Postcondition: Returns true if character is either one of a space, tab, 
carriage-return or newline according to the ASCII standard. */
bool isWhiteSpace(char character);

//Precondition: nums[] is a filled array of integers.
//Returns true if nums[] is a valid configuration for a plugboard.
//That is, if each integer in nums is between 0 and 25, and each 
//integer occurs exactly once.
int validConfig(int nums[26]);

/*Precondition: array is an array of size length which has been initiallised,
output is an initiallised integer.
Postcondition: if output is not in array, returns -1. Otherwise, returns the
index of array which output appears in. */
int inverseMapping(int* array, int length, int output);

//========================Encryption Functions========================

/*Precondition: rotorList is a list of initialised Rotor pointers, where
rotorList[0] points to the rightmost rotor. 'rotors' in the number of rotors.
pb points to an initialised Plugboard. rf points to an initialised
reflector, and n is a letter index (0 to 25) to be passed through.
Postcondtition: n has been encrypted, all rotors have rotated as appropriate.
*/
void passThroughEnigma(Rotor** rotorList, int rotors,
		       Plugboard* pb, Reflector* rf, int& n);

/*Precondition: linkedRotors is an array of pointers to 'number_of_rotors'
rotors. pbPtr and rfPtr point to correctly configured plugboard and reflector
respectively.
Postcondition: Prompts user for a message to encrypt via the standard input 
stream (keyboard). Sends encrypted message to the standard output stream
(monitor). Ignores white space character. INVALID_INPUT_CHARACTER error is 
picked up and passed to main() via errnum.*/		       
void encrypt(Rotor** linkedRotors, int number_of_rotors, Plugboard* pbPtr,
	     Reflector* rfPtr, int& errnum);

/*Precondition: similar to the above, pbPtr and rfPtr point to a plugboard and
reflector respectively.
Postcondition: Same as above. This is to be used when there are no rotors
present. INVALID_INPUT_CHARACTER is picked up and pass to main() via errnum.*/
void encrypt(Plugboard* pbPtr, Reflector* rfPtr, int& errnum);

//================Misc Functions======================================

/*Precondition: _inflow is an opened istream and reads from _filename.
_filename either a .pb, .rot, .rf or .pos file. 
Postcondition: Returns the number which has been read in. If a non-numeric
character is contained in _filename, then the NON_NUMERIC_CHARACTER error will
been invoked and this will be caught by the object constructor. */
int readNumber(std::istream &inflow, char& digit, const char* filename);

//Precondition: rotorList is a dynamically created array of number_of_rotors 
//dynamic pointers to constructed rotors. positions is an initialised dynamic
//array also of size number_of_rotors.
//Postcondition: All dynamic memory allocation mentioned above is freed and
//resulting dangling pointers set to NULL.
void deleteRotors(Rotor** rotorsList, int number_of_rotors, int* positions);

//Precondition: rotorList is a dynamically created array of number_of_rotors 
//dynamic pointers to constructed rotors.
//Postcondition: All dynamic memory allocation mentioned above is freed and
//resulting dangling pointers set to NULL.
void deleteRotors(Rotor** rotorsList, int number_of_rotors);

#endif
