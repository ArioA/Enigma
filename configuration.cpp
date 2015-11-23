#include <iostream>
#include <fstream>
#include "helper.h"
#include "configuration.h"

using namespace std;

void readPositions(int* a, const int& length, const char* filename, 
		   int& errnum)
{
  ifstream inflow(filename);

  //Check if filestream was successfully opened.
  if(!inflow)
    {
      cerr << "Unable to open position file " << filename << ".\n";
      errnum = 11;
      return;
    }
  
  char digit; //Character which is read in by inflow.
  int count(0); //Counts the number of integers which have been read in.


  //Begins reading in from position file filename.
  inflow.get(digit);
  
  while(!inflow.eof())
    {

      //Checks if filename contains more integers than there are elements of
      //a[] to be filled.
      if(count > length-1)
	{
	  cerr << "Position file " << filename 
	       << " contains too many parameters."
	       << endl;
	  errnum = 8;
	  return;
	}

      int number(0); //integer to be read in from the position file.
      
      number = readNumber(inflow, digit, filename);

      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character in rotor positions file " << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input 
      else if(number < 0 || number > 25) //number in .rot file.
	{
	  cerr << number << " is an invalid index in rotor positions file " 
	       << filename << endl;
	  errnum = 3;
	  return;
	}

      a[count] = number;
      count++;

      //Skips all white space characters.
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}
      
      //Reads next non-white-space character into digit.
      inflow.get(digit);
    }

  //Checks if a[] has been filled or not.
  if(count < length)
    {
      cerr << "No starting position for rotor " << count
	   << " in rotor position file: " << filename << endl;
      errnum = 8;
      return;
    }

  inflow.close();
}

void configurePosition(Rotor* rot_ptr, const int& position)
{
  for(int k = 0; k < position; k++)
    {
      rot_ptr->rotate();
    }
}
