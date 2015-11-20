#include<iostream>
#include<cstdlib>
#include<fstream>
#include"rotor.h"
#include"errors.h"
#include"helper.h"

using namespace std;

Rotor::Rotor(const char* filename, int _msalgn, int& errnum):
  missalignment(_msalgn)
{
  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Unable to open rotor file: " << filename << ".\n";
      errnum = 11;
      return;
    }

  //Default 'empty' setup:
  for(int k = 0; k < 26; k++)
    config[k] = -1;

  char digit;

  inflow.get(digit);

  for(int count = 0; count < 26; count++)
    {
     int  number(0);

      if(inflow.eof())
	{
	  cerr << "Not all inputs mapped in rotor file: " << filename << endl;
	  errnum = 7;
	  return;
	}

      number = readNumber(inflow, digit, filename);

      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character for mapping in rotor file " 
	       << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input number
      else if(number < 0 || number > 25) // in .rot file.
	{
	  cerr << "Invalid index in rotor file " << filename
	       << ": " << number << " is not a valid index." << endl;
	  errnum = 3;
	  return;
	}

      else if(inverseMapping(config, 26, number) != -1 && count > 0) 
	//Check if index has been mapped.
	{
	  cerr << "Invalid mapping of input " << count << " to output "
	       << number << " (output " << number 
	       << " is already mapped to from input "
	       << inverseMapping(config, 26, number) 
	       << ") in rotor file: " << filename << endl;
	  errnum = 7;
	  return;
	}
      
      config[count] = number;

      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);
    }

  if(validConfig(config)) //Final check.
    {
      cerr << "Invalid rotor mapping in rotor file " << filename
	   << ": too many/few " << validConfig(config)
	   << "s in this file." << endl;
      errnum = 7;
      return;
    }

/*========================= Begins to read in notches =====================*/
  
  while(!inflow.eof())
    {
      int number(0);
      
      number = readNumber(inflow, digit, filename);

      if(number == -1) //Catches readNumber() non-numeric character flag.
	{
	  cerr << "Non-numeric character for mapping in rotor file " 
	       << filename
	       << endl;
	  errnum = 4;
	  return;
	}                                //Checks valid input number
      else if(number < 0 || number > 25) //number in .rot file.
	{
	  cerr << "Invalid index in rotor file " << filename
	       << ": " << number << " is not a valid index." << endl;
	  errnum = 3;
	  return;
	}
      
      if(notch[number]) //Check if number hasn't already been read.
	{
	  cerr << "Invalid rotor mapping in rotor file " << filename
	       << "cannot add notch to same position twice."
	       << endl;
	  errnum = 7;
	  return;
	}
      else
	notch[number] = true;

      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);
    }

  inflow.close();
}

void Rotor::passThrough_R2L(int& n)
{
  n = ((config[(n + missalignment) % 26] - missalignment) % 26);

  if(n < 0)
    n += 26; 
}

void Rotor::passThrough_L2R(int& n)
{
  for(int k = 0; k < 26; k++)
    {
      if(n == ((config[(k + missalignment) % 26] - missalignment) % 26)
	 || n == ((config[(k + missalignment) % 26] - missalignment) % 26) + 26)
	{
	  n = k;
	  return;
	}
    }
}

void Rotor::rotate()
{
  missalignment = (missalignment + 1) % 26;
}

bool Rotor::get_notch()
{
  return notch[missalignment];
}

void Rotor::print_config()
{
  for(int k = 0; k <26; k++)
    cout << config[k] << " ";

  cout << endl;
}
