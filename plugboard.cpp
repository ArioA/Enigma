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

Plugboard::Plugboard(char* filename)
{
  cout << "Constructing plugboard from file " << filename << "..." << endl;
  
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Error: Unable to open file: " << filename << ".\n";
      exit(11);
    }

  for(int k = 0; k < 26; k++)
    {
      config[k] = k; //Default set-up.
    }
  
  char digit; //character input from .pb file. 
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
      
      int number;
      /*
	- decimal counts what power of 10 the input char is.
	- number is the int equivalent of input characters.
      */

      if(isWhiteSpace(digit))  //Next character must be a digit, 
	{                          //otherwise incorrectly configured file.
	  cerr << "Impossible plugboard configuration in " << filename
	       << " - file is not well-formed." << endl;
	  exit(5);
	}

      number = readNumber(inflow, digit, filename);

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

      occurences[number]++;

      if(occurences[number] > 1) //Checks if number has already been read.
	{
	  cerr << "Error:" << endl
	       << "Invalid reflector mapping - Too many " << number 
	       << "s in file " 
	       << filename << ".\n";
	  exit(9);
	}

      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);
      
      count++;
    }
  
  if(count % 2 == 1) //Can't have odd number of integers in .pb file.
    {
      cerr << "Incorrect number of parameters in plugboard file:  " 
	   << filename << endl;
      exit(6);
    }
  
  
  if(validConfig(config)) //Final check.
    {
      cerr << "Impossible plugboard configuration:" << endl
	   << "Too many/few " << validConfig(config)
	   << "s on this board." << endl;
      exit(5);
    }

  inflow.close();
  
  cout << "Construction of plugboard complete." << endl << endl;
}

//Precondition: n is an integer between 0 and 25.
//Postcondition: Simulates the (n+1)th letter passing through the plugboard.
//Invalid input character error lives here since plugboard is always
//the first component which input passes through. 
void Plugboard::passThrough(int& n)
{
  if(n < 0 || n > 25)
    {
      cerr << "Invalid Input Character Error:" << endl
	   << "'" << int_to_letter(n) << "' is not a captial letter." << endl;
      exit(2);
    }
  
  n = config[n];
  return;
}
