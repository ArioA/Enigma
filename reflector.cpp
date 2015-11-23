//Ario Aliabadi
//asa215@ic.ac.uk
//10/11/2015

#include<fstream>
#include<iostream>
#include"helper.h" //reflector.h found in here.

using namespace std;

Reflector::Reflector(const char* filename, int& errnum)
{  
  ifstream inflow;
  inflow.open(filename);

  //Checks if file reflector file could be opened.
  if(!inflow)
    {
      cerr << "Unable to open reflector file: " << filename << ".\n";
      errnum = 11;
      return;
    }

  //Default 'empty' setup:
  for(int k = 0; k < 26; k++)
    config[k] = -1;

  char digit; //character input from reflector file. 
  int index(0), count(0);
  
  /*
    - index is the buffer in between swapping values.
    - count counts the number of int inputs.
  */

  /*================Begin reading in from reflector file.===================*/

  inflow.get(digit);
  
  while(!inflow.eof())
    {

      if(count > 25) //Catches excessive number of parameter in .rf file.
	{
	  cerr << "Incorrect (too many) number of parameters parameters "
	       << "in reflector file:  " 
	       << filename << endl;
	  errnum = 10;
	  return;
	}
      
      int number(0);//integers to be read in from reflector file.
      
      number = readNumber(inflow, digit, filename);


      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character in reflector file " << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input 
      else if(number < 0 || number > 25) //number in reflector file.
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
	  if(index == number)//Checks if atempted to map a letter to itself.
	    {
	      cerr << "Invalid mapping of input " << index << " to output "
		   << number << " (cannot map the same letter to itself)"
		   << " in reflector file: " << filename <<  endl;
	      errnum = 9;
	      return;
	    }
	  else if(inverseMapping(config, 26, number) != -1) 
	    //Check if number has been mapped.
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
      
      //Skip any white spaces.
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      //Read next non-white-space character into digit.
      inflow.get(digit);

      count++;
    }

  if(count < 26) //Checks if enough parameter after having read all numbers.
    {
      cerr << "Insufficient ";
      cerr << (count%2 == 0 ? "(even)" : "(odd)");
      cerr <<" number of mappings in reflector file: " 
	   << filename << endl;
      errnum = 10;
      return;
    }
  
  
  if(validConfig(config)) //Final check.
    {
      cerr << "Invalid reflector mapping:" << endl
	   << "Too many/few " << validConfig(config)
	   << "s in this file." << endl;
      errnum = 9;
      return;
    }

  //Finished reading from reflector file.
  inflow.close();
}

void Reflector::passThrough(int& n)
{ 
  n = config[n];
  return;
}
