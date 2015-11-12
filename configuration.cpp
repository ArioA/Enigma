#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "helper.h"
#include "configuration.h"
#include "errors.h"

using namespace std;

//Precondition: a[] is an array of length 'lenght'. 
//Postcondition: a[] is filled with numbers 
//from the .pos file filename.
void readPositions(int* a, int length, char* filename)
{
  cout << "Reading in positions...." << endl;

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
      int decimal(0), number(0);
      
      while(digit != ' ' && digit != '\n')
	{
	  
	  if(!isDigit(digit)) //Non-digit characters are not permited.
	    {
	      cerr << filename << " contains a non-numeric character.\n";
	      exit(4);
	    }
	  
	  //Works out what number is - based on number of loop cycles.
	  
	  number *= pow(10,decimal);
	  number += digit_to_int(digit);
	  
	  inflow.get(digit);
	  
	  decimal++;
	  
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

  if(!inflow.eof())
    {
      cerr << "Error: No rotor starting position - " << endl
	   << filename << " contains too many parameters." 
	   << endl;
      exit(8);
    }

  cout << "Extraction complete." << endl;
  
}
