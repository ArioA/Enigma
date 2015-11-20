/*Plugboard part of enigma machine. Can insert plugs into pairs of sockets 
to swap values of input/output.*/

//Ario Aliabadi
//asa215@ic.ac.uk
//09/11/2015

#include<cstdlib>
#include<iostream>
#include<fstream>
#include"plugboard.h"
#include"helper.h"
#include"errors.h"

using namespace std;

//Constructor:

Plugboard::Plugboard(const char* filename, int& errnum)
{  
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Unable to open file " << filename << ".\n";
      errnum = 11;
      return;
    }

  for(int k = 0; k < 26; k++)
    {
      config[k] = k; //Default set-up.
    }
  
  char digit; //character input from .pb file. 
  int index(0), count(0) /*,inverse_mapping[26]*/;
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
    - occurences counts the number of times a number has been read.
  */

  /*for(int k = 0; k < 26; k++)
    inverse_mapping[k] = k;*/

  inflow.get(digit);
  
  while(!inflow.eof())
    {
      
      int number;
      /*
	- decimal counts what power of 10 the input char is.
	- number is the int equivalent of input characters.
      */

      number = readNumber(inflow, digit, filename);

      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character in plugboard file " << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input
      else if(number < 0 || number > 25) //number in .pb file. 
	{
	  cerr << number << " is an invalid index in file " 
	       << filename << endl;
	  errnum = 3;
	  return;
	}

      if(count % 2 == 0) //Puts read number into a buffer.
	{
	  if(inverseMapping(config, 26, number) != number && count > 0) 
	    //Check if index has been mapped.
	    {
	      cerr << "Impossible plugboard configuration of input " 
		   << number << " to some other output " 
		   << "(" << number << " is already mapped to from input "
		   << inverseMapping(config, 26, number) 
		   << ") in plugboard file: " << filename << endl;
	      errnum = 5;
	      return;
	    }

	  index = number;
	}
      else
	{ 
	  if(index == number)
	    {
	      cerr << "Impossible plugboard configuration of input " 
		   << index << " to output " << number 
		   << " (cannot map the same letter mapped to itself)"
		   << " in plugboard file: " << filename <<  endl;
	      errnum = 5;
	      return;
	    }

	  if(inverseMapping(config, 26, number) != number) 
	    //Check if index has been mapped.
	    {
	      cerr << "Invalid mapping of input " << index << " to output "
		   << number << " (output " << number 
		   << " is already mapped to from input "
		   << inverseMapping(config, 26, number) 
		   << ") in plugboard file: " << filename << endl;
	      errnum = 5;
	      return;
	    }

	  config[index] = number; //Implements plugboard 'switch'.
	  config[number] = index;
	  //inverse_mapping[number] = index;
	  //inverse_mapping[index] = number;
	}

      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);
      
      count++;

      if(count > 26)
	{
	  cerr << "Incorrect number of parameters in plugboard file "
	       << filename << endl;
	  errnum = 6;
	  return;
	}
    }
  
  if(count % 2 == 1) //Can't have odd number of integers in .pb file.
    {
      cerr << "Incorrect number of parameters in plugboard file " 
	   << filename << endl;
      errnum = 6;
      return;
    }
  
  
  if(validConfig(config)) //Final check.
    {
      cerr << "Impossible plugboard configuration in plugboard file "
	   << filename << ": too many/few " << validConfig(config)
	   << "s on this plugboard." << filename << endl;
      errnum = 5;
      return;
    }

  inflow.close();
}

//Precondition: n is an integer between 0 and 25.
//Postcondition: Simulates the (n+1)th letter passing through the plugboard.
//Invalid input character error lives here since plugboard is always
//the first component which input passes through. 
void Plugboard::passThrough(int& n)
{ 
  n = config[n];
  return;
}
