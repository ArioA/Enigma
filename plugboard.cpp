/*TO DO: test.*/

//Ario Aliabadi
//asa215@ic.ac.uk
//05/11/2015

#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cmath>
#include"plugboard.h"
#include"helper.h"
#include"errors.h"

using namespace std;

//Constructor:

Plugboard::Plugboard(char* filename)
  {
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

    ifstream inflow;
    inflow.open(filename);

    while(!inflow.eof())
      {
      
	int decimal(0), number(0);
	/*
	 - decimal counts what power of 10 the input char is.
	 - number is the int equivalent of input characters.
	*/
	
	inflow.get(digit);

	if(inflow.eof())
	  {
	    break;
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

	while(inflow.peek() == ' ') //Skips to next place if next one is 
	  {                         //a blank space.
	    inflow.get(digit);
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
	
	count++;
      }

    if(count % 2 == 1) //Can't have odd number of integers in .pb file.
      {
	cerr << "Incorrect number of parameters in plugboard file:  " 
	     << filename << endl;
	exit(6);
      }
   

    if(validConfig(config))
      {
	cerr << "Impossible plugboard configuration:" << endl
	     << "Too many/few " << validConfig(config)
	     << "s on this board." << endl;
	exit(5);
      }
  }


//Precondition: n is an integer between 0 and 25.
//Simulates the (n+1)th letter passing through the plugboard.
//Changes n's value according to plugboard configuration. 
void Plugboard::passThrough(int& n)
  {
    if(n < 0 || n > 25)
      {
	cerr << "Error: n must be between 0 and 25.\n";
	return;
      }
    
    n = config[n];
    return;
  }
