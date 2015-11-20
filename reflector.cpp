//Ario Aliabadi
//asa215@ic.ac.uk
//10/11/2015

/*TO DO:
- .rf file should contain 26 numbers -> if(count != 26)...
- INVALID_INDEX
- NON-NUMERIC_CHAR
*/

#include<fstream>
#include<cstdlib>
#include<iostream>
#include"reflector.h"
#include"errors.h"
#include"helper.h"

using namespace std;

Reflector::Reflector(const char* filename, int& errnum)
{  
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Unable to open reflector file: " << filename << ".\n";
      errnum = 11;
      return;
    }

  for(int k = 0; k < 26; k++)
    config[k] = -1;

  char digit; //character input from .rf file. 
  int index(0), count(0);
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
    - occurences counts the number of times a number has been read.
  */

  inflow.get(digit);
  
  while(!inflow.eof())
    {
      
      int number(0);
      /*
	- decimal counts what power of 10 the input char is.
	- number is the int equivalent of input characters.
      */
      
      number = readNumber(inflow, digit, filename);


      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character in reflector file " << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input 
      else if(number < 0 || number > 25) //number in .rf file.
	{
	  cerr << "Invalid index in reflector file " << filename
	       << ": " << number << " is not a valid index." << endl;
	  errnum = 3;
	  return;
	}

      if(count % 2 == 0) //Puts read number into a buffer.
	{
	  if(inverseMapping(config, 26, number) != -1 && count > 0) 
	    //Check if index has been mapped.
	    {
	      cerr << "Invalid mapping of input " 
		   << number << " to some other output " 
		   << "(" << number << " is already mapped to from input "
		   << inverseMapping(config, 26, number) 
		   << ") in reflector file: " << filename << endl;
	      errnum = 9;
	      return;
	    }
	  
	      index = number;
	}
      else
	{
	  if(index == number)
	    {
	      cerr << "Invalid mapping of input " << index << " to output "
		   << number << " (cannot map the same letter to itself)"
		   << " in reflector file: " << filename <<  endl;
	      errnum = 9;
	      return;
	    }
	  else if(inverseMapping(config, 26, number) != -1) 
	    //Check if index has been mapped.
	    {
	      cerr << "Invalid mapping of input " << index << " to output "
		   << number << " (output " << number 
		   << " is already mapped to from input "
		   << inverseMapping(config, 26, number) 
		   << ") in reflector file: " << filename << endl;
	      errnum = 9;
	      return;
	    }

	  config[index] = number; //Implements reflector mapping.
	  config[number] = index;
	}
      
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);

      count++;

      if(count > 26) //Catches excessive number of parameter in .rf file.
	{
	  cerr << "Too many parameters in reflector file:  " 
	       << filename << endl;
	  errnum = 10;
	  return;
	}
    }

  if(count < 26) //Checks if enough parameter after having read all numbers.
    {

      if(count % 2 == 0)
      {
	cerr << "Insufficient number of mappings in reflector file: " 
	     << filename << endl;
	errnum = 10;
	  return;
      }
      else
      {
	cerr << "Incorrect (odd) number of parameters in reflector file " 
	     << filename << endl;
	errnum = 10;
	  return;
      }
    }
  
  
  if(validConfig(config)) //Final check.
    {
      cerr << "Impossible reflector configuration:" << endl
	   << "Too many/few " << validConfig(config)
	   << "s in this file." << endl;
      exit(9);
    }

  inflow.close();
}


void Reflector::passThrough(int& n)
{ 
  n = config[n];
  return;
}
