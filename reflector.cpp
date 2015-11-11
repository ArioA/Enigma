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
  
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Error: Unable to open file: " << filename << ".\n";
      exit(11);
    }

  char digit; //character input from .rf file. 
  int index(0), count(0), occurences[26];
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
    - occurences counts the number of times a number has been read.
  */

  for(int k = 0; k < 26; k++)
    occurences[k] = 0;

  inflow.get(digit);
  
  while(!inflow.eof())
    {
      
      int decimal(0), number(0);
      /*
	- decimal counts what power of 10 the input char is.
	- number is the int equivalent of input characters.
      */
      
      if(isWhiteSpace(digit))  //Next character must be a digit, 
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
      
      if(number < 0 || number > 25) //Checks valid input number in .rf file.
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
	  config[index] = number; //Implements reflector mapping.
	  config[number] = index;
	}

      occurences[number]++;

      if(occurences[number] > 1) //Checks if number has already been read.
	{
	  cerr << "Error:" << endl
	       << "Invalid reflector mapping - Too many " << number 
	       << "s in file " 
	       << filename << ".\n";
	  exit(9);
	}
      
      inflow.get(digit);

      count++;

      if(count > 26) //Catches excessive number of parameter in .rf file.
	{
	  cerr << "Too many parameters in reflector file:  " 
	       << filename << endl;
	  exit(10);
	}
    }

  if(count < 26) //Checks if enough parameter after having read all numbers.
    {
      cerr << "Insufficient number of parameters in reflector file:  " 
	   << filename << endl;
      exit(10);
    }
  
  
  if(validConfig(config)) //Final check.
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
      cerr << "Error in reflector: n must be between 0 and 25.\n";
      return;
    }
  
  n = config[n];
  return;
}
