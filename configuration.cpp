#include <iostream>
#include <fstream>
#include <cstdlib>
#include "helper.h"
#include "configuration.h"
#include "errors.h"

using namespace std;

//Precondition: a[] is an array of length 'length'. 
//Postcondition: a[] is filled with numbers 
//from the .pos file filename.
void readPositions(int* a, int length, char* filename)
{
  ifstream inflow(filename);

  if(!inflow)
    {
      cerr << "Error: Unable to open file: " << filename << ".\n";
      exit(11);
    }
  
  char digit;
  int count(0);

  inflow.get(digit);
  
  if(inflow.eof())
    {
      cerr << "Error: No rotor starting position - " << endl
	   << filename << " is empty." << endl;
      exit(8);
    }
  
  while((!inflow.eof()) && (count <= length))
    {
      int number(0);
      
      number = readNumber(inflow, digit, filename);

      if(number == -1)
	{
	  cerr << "Invalid Character..." << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

      if(number < 0 || number > 25) //Checks valid input number in .rot file.
	{
	  cerr << number << " is an invalid index in file " 
	       << filename << endl;
	  exit(3);
	}

      a[count] = number;
      count++;

      inflow.get(digit);
    }

  if(count < length)
    {
      cerr << "Error: No rotor starting position - " << endl
	   << filename << " has an insuffcient number of parameters." 
	   << endl;
      exit(8);
    }
  
  while(isWhiteSpace(inflow.peek()))
    {
      inflow.get(digit);
    }

  inflow.get(digit);

  if(!inflow.eof())
    {
      cerr << "Error: No rotor starting position - " << endl
	   << filename << " contains too many parameters." 
	   << endl;
      exit(8);
    }

  inflow.close();
}


//Precondition: rot_ptr is a pointer to the rotor
//which is to be configured. Position is the position
//which the rotor in question is to be configured to.
//Postcondition: *rot_ptr is rotated position times. 
//So that the position indexed letter is aligned with
//the 'absolute A'.
void configurePosition(Rotor* rot_ptr, int position)
{
  for(int k = 0; k < position; k++)
    {
      rot_ptr->rotate();
    }
}
