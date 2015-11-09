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

Plugboard::Plugboard(char* filename)
  {
    for(int k = 0; k < 25; k++)
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

	    if(!isDigit(digit))
	      {
		cerr << filename << " contains a non-numeric character.\n";
		exit(4);
	      }
	    
	    number *= pow(10,decimal);
	    number += digit_to_int(digit);

	    inflow.get(digit);
	    
	    decimal++;
	    
	  }
	
	if(number < 0 || number > 25)
	  {
	    cerr << number << " is an invalid index in file " 
		 << filename << endl;
	    exit(3);
	  }

	if(count % 2 == 0)
	  {
	    index = number;
	  }
	else
	  {
	    config[index] = number;
	    config[number] = index;
	  }
	
	count++;
      }

    if(count % 2 == 1)
      {
	cerr << "Incorrect number of parameters in plugboard file:  " 
	     << filename << endl;
	exit(6);
      }

    if(validConfig(config))
      {
	cerr << "Impossible plugboard configuration:" << endl
	     << "at least one character has two plugs in it or"
	     << "does not feature on this board." << endl;
	exit(5);
      }
  }

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
