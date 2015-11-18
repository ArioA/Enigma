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
void readPositions(int* a, int length, char* filename, int& errnum)
{
  ifstream inflow(filename);

  if(!inflow)
    {
      cerr << "Unable to open position file " << filename << ".\n";
      errnum = 11;
      return;
    }
  
  char digit;
  int count(0);

  inflow.get(digit);
  
  while(!inflow.eof())
    {
      int number(0);
      
      number = readNumber(inflow, digit, filename);

      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character in positions file " << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input 
      else if(number < 0 || number > 25) //number in .rot file.
	{
	  cerr << number << " is an invalid index in position file " 
	       << filename << endl;
	  errnum = 3;
	  return;
	}

      a[count] = number;
      count++;

      if(count > length)
	{
	  cerr << "Position file " << filename 
	       << " contains too many parameters."
	       << endl;
	  errnum = 8;
	  return;
	}

      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}
      
      inflow.get(digit);
    }


  if(count < length)
    {
      cerr << "No starting position for rotor " << count
	   << " in rotor position file: " << filename << endl;
      errnum = 8;
      return;
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
