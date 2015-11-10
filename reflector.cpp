//Ario Aliabadi
//asa215@ic.ac.uk
//10/11/2015

/*TO DO:
- .rf file should contain 26 numbers -> if(count != 26)...
- INVALID_INDEX
- NON-NUMERIC_CHAR
*/

#include<cmath>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include"reflector.h"
#include"errors.h"
#include"helper.h"

using namespace std;

Reflector::Reflector(char* filename)
{
  cout << "Constructing Reflector from " << filename << "..." << endl;
  
  char digit; //character input from .rf file. 
  int index(0), count(0);
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
  */
  
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Error: Unable to open file: " << filename << ".\n";
      exit(11);
    }

  inflow.get(digit);
  
  while(!inflow.eof())
    {
      
      int decimal(0), number(0);
      /*
	- decimal counts what power of 10 the input char is.
	- number is the int equivalent of input characters.
      */
      
      if(!isDigit(digit))  //Next character must be a digit, 
	{                          //otherwise incorrectly configured file.
	  cerr << "Impossible reflector configuration in " << filename
	       << " - file is not well-formed." << endl;
	  exit(5);
	}
      
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
      
      if(number < 0 || number > 25) //Checks valid input number in .pb file.
	{
	  cerr << number << " is an invalid index in file " 
	       << filename << endl;
	  exit(3);
	}
      
      if(count % 2 == 0) //Puts read number into a buffer.
	{
	  index = number;
	}
      else
	{
	  config[index] = number; //Implements plugboard 'switch'.
	  config[number] = index;
	}
      
      inflow.get(digit);

      count++;
    }
  
  if(count != 26) //Must have 26 numbers in .rf file.
    {
      cerr << "Incorrect number of parameters in reflector file:  " 
	   << filename << endl;
      exit(10);
    }
  
  
  if(validConfig(config))
    {
      cerr << "Impossible reflector configuration:" << endl
	   << "Too many/few " << validConfig(config)
	   << "s in this file." << endl;
      exit(9);
    }

  cout << "Reflector successfully constructed." << endl << endl;
}


void Reflector::passThrough(int& n)
{
  if(n < 0 || n > 25)
    {
      cerr << "Error: n must be between 0 and 25.\n";
      return;
    }
  
  n = config[n];
  return;
}
