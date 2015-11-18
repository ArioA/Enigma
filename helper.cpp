#include<iostream>
#include<cmath>
#include"helper.h"

using namespace std;

//===========================Conversion Functions=======================

typedef Rotor* RotorPtr;
typedef Plugboard* PlugboardPtr;
typedef Reflector* ReflectorPtr;

//Precondition: digit is a digit (0, 1, ..., 9).
//Returns digit as an integer.
int digit_to_int(char digit)
{
  return (static_cast<int>(digit) - 48);
}

//Precondition: number is between 0 and 9.
//Returns number as a char.
char int_to_digit(int number)
{
  return (static_cast<int>(number + 48));
}


//Precondition: number is between 0 and 25.
//Returns alphabetic equivalent as capital letter.
char int_to_letter(int number)
{
  return (static_cast<char>(number + 65));
}

//Precondition: alpha is a capital letter.
//Returns integer representation of alpha.
int letter_to_int(char alpha)
{
  return (static_cast<int>(alpha) - 65);
}

//==================================================================
//=======================Checking Functions=========================


//Precondition: digit is any character.
//Returns true is digit is a digit, false otherwise.
bool isDigit(char digit)
{
  if(digit_to_int(digit) < 0 || digit_to_int(digit) > 9)
    {
      return false;
    }
  else
    return true;
}

//Precondition: character is an initialised char variable.
//Returns true if character is an alphabetic character. False otherwise.
bool isLetter(char character)
{
  if((character >= 'a' && character <= 'z') ||
     (character >= 'A' && character <= 'Z'))
     {
       return true;
     }

return false;
}

//Precondition: character is an initialised char variable.
//Returns true if character is a capital letter. False otherwise.
bool isCapital(char character)
{
  if(character >= 'A' && character <= 'Z')
     {
       return true;
     }

return false;
}


/*Precondition: character is an initialised char.
Postcondition: Returns true if character is either one of a space, tab, 
carriage-return or newline according to the ASCII standard.
*/
bool isWhiteSpace(char character)
{
  if(character == 32 || character == 10 || character == 9 ||
     character == 13)
    return true;

  return false;
}


//Precondition: nums[] is a filled array of integers.
//Returns true if nums[] is a valid configuration for a plugboard.
//That is, if each integer in nums is between 0 and 25, and each 
//integer occurs exactly once.
int validConfig(int nums[26])
{
  int occurences[26];

  for(int k = 0; k < 26; k++)
    {
      occurences[k] = 0;

      for(int j = 0; j < 26; j++)
	{
	  if(k == nums[j])
	    occurences[k]++;
	}
    }

  for(int k = 0; k < 26; k++)
    {
      if(occurences[k] - 1 != 0)
	return nums[k];
    }

  return 0;
}

//====================================================================

/*Precondition: _inflow is an opened istream and reads from _filename.
_filename either a .pb, .rot, .rf or .pos file. 
Postcondition: Returns the number which has been read in. If a non-numeric
character is contained in _filename, then the NON_NUMERIC_CHARACTER error will
been invoked and this will be caught by the object constructor.
*/

int readNumber(istream& _inflow, char& _digit, char* _filename)
{
  int decimal(0), number(0);

  /*
    - decimal counts what power of 10 the input char is.
    - number is the int equivalent of input characters.
  */

  while(_digit != ' ' && _digit != '\n')
    {
      
      if(!isDigit(_digit)) //Non-digit characters are not permited.
	{
	  return -1;
	}
      
      //Works out what number is - based on number of loop cycles.
      
      number *= pow(10,decimal);
      number += digit_to_int(_digit);
      
      _inflow.get(_digit);
      
      decimal++;      
    }

  return number;
}


/*Precondition: rotorList is a list of initialised Rotor pointers, where
rotorList[0] points to the rightmost rotor. 'rotors' in the number of rotors.
pb points to an initialised Plugboard. rf points to an initialised
reflector, and n is a letter index (0 to 25) to be passed through.
Postcondtition: n has been encrypted, all rotors have rotated as appropriate.
*/
void passThroughEnigma(Rotor** rotorList, int rotors,
  Plugboard* pb, Reflector* rf, int& n)
{
  
  rotorList[0]->rotate();

  for(int k = 0; k < rotors - 2 && rotorList[k]->get_notch(); k++)
  {
    rotorList[k+1]->rotate();
  }

  //  cout << "PB: " << n << " goes to ";
  pb->passThrough(n);
  //cout << n << endl;

  for(int k = 0; k < rotors; k++)
  {
    //cout << "Rot " << k << ": " << n;
    rotorList[k]->passThrough_R2L(n);
    //cout << " goes to " << n << endl;
  }

  //cout << "RF: " << n  << " goes to ";
  rf->passThrough(n);
  //cout << n << endl;

  for(int k = rotors-1; k >= 0; k--)
  {
    //cout << "Rot " << k << ": " << n;
    rotorList[k]->passThrough_L2R(n);
    //cout << " goes to " << n << endl;
  }

  //cout << "PB: " << n << " goes to ";
  pb->passThrough(n);
  //cout << n << endl;
}


/*Precondition: linkedRotors is an array of pointers to 'number_of_rotors'
rotors. pbPtr and rfPtr point to correctly configured plugboard and reflector
respectively.
Postcondition: Prompts user for a message ending in '.' to encrypt via the
standard input (keyboard). Sends encrypted message to the standard output
(monitor). INVALID_INPUT_CHARACTER error is picked up by passThroughEnigma().
 */
void encrypt(RotorPtr* linkedRotors, int number_of_rotors, PlugboardPtr pbPtr,
	     ReflectorPtr rfPtr, int& errnum)
{
  char input_output;
  int num_io;
  
  cout << "Enter in CAPITAL letters "
       << "what you would like to have encrytped." << endl
       << "Press Enter when you are done." << endl;
  
  cin.get(input_output);
  
  while(input_output != '\n')
    { 
      if(!isCapital(input_output))
	{
	  cerr << input_output << " is not a valid input character (input "
	       << "characters must be upper case letters" << endl
	       << "(A-Z)!" << endl;
	  errnum = 2;
	  return;
	}

      num_io = letter_to_int(input_output);
      
      passThroughEnigma(linkedRotors, number_of_rotors, pbPtr, rfPtr, num_io);
      
      cout << int_to_letter(num_io);
      
      cin.get(input_output);
    }
}

/*Precondition: similar to the above, pbPtr and rfPtr point to a plugboard and
rotor respectively.
Postcondition: Same as above. This is to be used when there are no rotors
present. INVALID_INPUT_CHARACTER error is picked up by passThrough().
*/
void encrypt(PlugboardPtr pbPtr, ReflectorPtr rfPtr, int& errnum)
{
  char input_output;
  int num_io;
  
  cin.get(input_output);
  
  while(input_output != '\n')
    { 
      if(!isCapital(input_output))
	{
	  cerr << input_output << " is not a valid input character (input "
	       << "characters must be upper case letters" << endl
	       << "(A-Z)!" << endl;
	  errnum = 2;
	  return;
	}

      num_io = letter_to_int(input_output);
      
      pbPtr->passThrough(num_io);
      rfPtr->passThrough(num_io);
      pbPtr->passThrough(num_io);
      
      cout << int_to_letter(num_io);
      
      cin.get(input_output);
    }
}
