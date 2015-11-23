/*Plugboard part of enigma machine. Can insert plugs into pairs of sockets 
to swap values of input/output.*/

//Ario Aliabadi
//asa215@ic.ac.uk
//09/11/2015

#include<iostream>
#include<fstream>
#include"helper.h" //plugboard.h found in here.

using namespace std;

Plugboard::Plugboard(const char* filename, int& errnum)
{  
  ifstream inflow;
  inflow.open(filename);

  //Check if able to open plugboard file.
  if(!inflow)
    {
      cerr << "Unable to open plugboard file " << filename << ".\n";
      errnum = 11;
      return;
    }

  for(int k = 0; k < 26; k++)
    {
      config[k] = k; //Default set-up.
    }
  
  char digit; //character input from .pb file. 
  int index(0), count(0);
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
  */

  /*================Begin reading in from plugboard file.===================*/
  inflow.get(digit);
  
  while(!inflow.eof())
    {   		
      if(count > 25) //Check if too many numbers have been read in.
	{
	  cerr << "Incorrect (too many) number of parameters"
	       <<" in plugboard file "
	       << filename << endl;
	  errnum = 6;
	  return;
	}
      
      //number is the integers read in from plugboard file, filename.
      int number;

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
	  cerr << number << " is an invalid index in plugboard file " 
	       << filename << endl;
	  errnum = 3;
	  return;
	}

      if(count % 2 == 0) //Puts read number into a buffer.
	{
	    //Check if index has been mapped.
	  if(inverseMapping(config, 26, number) != number && count > 0) 
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
	  if(index == number) //Checks if atempting to map a letter to itself.
	    {
	      cerr << "Impossible plugboard configuration of input " 
		   << index << " to output " << number 
		   << " (cannot map the same letter to itself)"
		   << " in plugboard file: " << filename <<  endl;
	      errnum = 5;
	      return;
	    }
	    //Check if number has been mapped.
	  if(inverseMapping(config, 26, number) != number) 
	    {
	      cerr << "Impossible plugboard configuration  of input " 
		   << index << " to output "
		   << number << " (output " << number 
		   << " is already mapped to from input "
		   << inverseMapping(config, 26, number) 
		   << ") in plugboard file: " << filename << endl;
	      errnum = 5;
	      return;
	    }

	  config[index] = number; //Implements plugboard 'switch'.
	  config[number] = index;
	}

      //Skips any whitespace characters in plugboard file.
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      //Reads next non-white-space character into digit.
      inflow.get(digit);
      
      count++;
    }
  
  if(count % 2 == 1) //Can't have odd number of integers in .pb file.
    {
      cerr << "Incorrect (odd) number of parameters in plugboard file " 
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

  //End of reading from plugboard file, filename.
  inflow.close();
}

void Plugboard::passThrough(int& n)
{ 
  n = config[n];
  return;
}
