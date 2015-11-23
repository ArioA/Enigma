#include<iostream>
#include<cmath>
#include"helper.h"

using namespace std;

//===========================Conversion Functions=======================

typedef Rotor* RotorPtr;
typedef Plugboard* PlugboardPtr;
typedef Reflector* ReflectorPtr;

int digit_to_int(const char& digit)
{
  return (static_cast<int>(digit) - 48);
}

char int_to_digit(const int& number)
{
  return (static_cast<int>(number + 48));
}

char int_to_letter(const int& number)
{
  return (static_cast<char>(number + 65));
}

int letter_to_int(const char& alpha)
{
  return (static_cast<int>(alpha) - 65);
}

bool isDigit(const char& digit)
{
  if(digit_to_int(digit) < 0 || digit_to_int(digit) > 9)
    {
      return false;
    }
  else
    return true;
}

bool isCapital(const char& character)
{
  if(character >= 'A' && character <= 'Z')
     {
       return true;
     }

return false;
}

bool isWhiteSpace(char character)
{
  if(character == 32 || character == 10 || character == 9 ||
     character == 13)
    return true;

  return false;
}

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

int inverseMapping(int* array, int length, int output)
{
  for(int k = 0; k < length; k++)
    {
      if(array[k] == output)
	return k;
    }

  return -1;
}

//========================Encryption Functions========================

void passThroughEnigma(Rotor** rotorList, int rotors,
  Plugboard* pb, Reflector* rf, int& n)
{
  
  rotorList[0]->rotate();//First rotor always rotates.

  //Simulates notch rotation mechanism.
  for(int k = 0; k < rotors - 1 && rotorList[k]->get_notch(); k++)
  {
    rotorList[k+1]->rotate();
  }

  //Begins pass through enigma machine.

  pb->passThrough(n);

  for(int k = 0; k < rotors; k++)
  {
    rotorList[k]->passThrough_R2L(n);
  }

  rf->passThrough(n);

  for(int k = rotors-1; k >= 0; k--)
  {
    rotorList[k]->passThrough_L2R(n);
  }

  pb->passThrough(n);
}

void encrypt(RotorPtr* linkedRotors, int number_of_rotors, PlugboardPtr pbPtr,
	     ReflectorPtr rfPtr, int& errnum)
{
  char input_output;//to be input from std input and then output to std output.
  int num_io; //numerical representation of input_output.
  
  cin.get(input_output);
  
  while(!cin.eof())
    { 
      while(isWhiteSpace(input_output))//Skips white space characters.
	{
	  cin.get(input_output);
	  
	  if(cin.eof())
	    return;
	}

      if(!isCapital(input_output))//Checks if invalid input has been entered.
	{
	  cerr << endl << input_output 
	       << " is not a valid input character (input "
	       << "characters must be upper case letters "
	       << "A-Z)!" << endl;
	  errnum = 2;
	  return;
	}

      num_io = letter_to_int(input_output);//reformat to pass through enigma.
      
      //initialises encryption.
      passThroughEnigma(linkedRotors, number_of_rotors, pbPtr, rfPtr, num_io);
      
      //outputs encrypted letter to standard output.
      cout << int_to_letter(num_io);
      
      cin.get(input_output);
    }
}

void encrypt(PlugboardPtr pbPtr, ReflectorPtr rfPtr, int& errnum)
{
  char input_output;//to be input from std input and then output to std output.
  int num_io; //numerical representation of input_output.
  
  cin.get(input_output);
  
  while(!cin.eof())
    { 
      while(isWhiteSpace(input_output))//Skips white space characters.
	{
	  cin.get(input_output);

	  if(cin.eof())
	    return;
	}

      if(!isCapital(input_output))//Checks if invalid input has been entered.
	{
	  cerr << endl << input_output 
	       << " is not a valid input character (input "
	       << "characters must be upper case letters "
	       << "A-Z)!" << endl;
	  errnum = 2;
	  return;
	}

      num_io = letter_to_int(input_output);//reformat to pass through enigma
      
      //Passes input through enigma.

      pbPtr->passThrough(num_io);
      rfPtr->passThrough(num_io);
      pbPtr->passThrough(num_io);
      
      //outputs encrypted letter to standard output.
      cout << int_to_letter(num_io);
      
      cin.get(input_output);
    }
}


//===========================Misc Functions================================

int readNumber(istream& _inflow, char& _digit, const char* _filename)
{
  int number(0); //integer value of value to be read in.

  while(_digit != ' ' && _digit != '\n')
    {
      
      if(!isDigit(_digit)) //Non-digit characters are not permited.
	{
	  return -1; //error flag.
	}
      
      number *= 10; //'shifts' number up one decimal place.
      number += digit_to_int(_digit); //digit is placed into number at
                                      //appropriate decimal position.
      _inflow.get(_digit);     
    }

  return number;
}

void deleteRotors(RotorPtr* rotorsList, int number_of_rotors, int* positions)
{
  for(int k = 0; k < number_of_rotors; k++) //delete each dynamic pointer.
    {
      delete rotorsList[k];
      rotorsList[k] = NULL;
    }
  
  delete [] rotorsList; //delete dynamic array.
  rotorsList = NULL;
  delete [] positions; //delete dynamic array.
  positions = NULL;
}

void deleteRotors(RotorPtr* rotorsList, int number_of_rotors)
{
  for(int k = 0; k < number_of_rotors; k++) //delete each dynamic pointer.
    {
      delete rotorsList[k];
      rotorsList[k] = NULL;
    }
  
  delete [] rotorsList; //delete dynamic array.
  rotorsList = NULL;
}
