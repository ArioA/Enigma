#include<iostream>
#include<cstdlib>
#include<fstream>
#include"rotor.h"
#include"errors.h"
#include"helper.h"

using namespace std;

Rotor::Rotor(char* filename, int _msalgn) : missalignment(_msalgn)
{
  cout << "Constructing rotor from " << filename << "..." << endl;

  ifstream inflow;
  inflow.open(filename);

  if(!inflow)
    {
      cerr << "Error: Unable to open file: " << filename << ".\n";
      exit(11);
    }

  char digit;
  int occurences[26];

  for(int k = 0; k < 26; k++)
    {
      occurences[k] = 0;
      notch[k] = false;
    }

  inflow.get(digit);

  for(int k = 0; k < 26; k++)
    {
     int  number(0);

      if(inflow.eof())
	{
	  cerr << "Error:" << endl
	       << "Invalid Rotor Mapping in " << filename 
	       << " - file contains insufficient"
	       << "number of parameters." << endl;
	}

      number = readNumber(inflow, digit, filename);

      if(number == -1)
	{
	  cerr << "Invalid Character..." << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

      if(number < 0 || number > 25) //Checks valid input number in .rot file.
	{
	  cerr << number << " is an invalid index in file " 
	       << filename << endl;
	  exit(3);
	}

      config[k] = number;

      occurences[number]++;

      if(occurences[number] > 1) //Checks if number has already been read.
	{
	  cerr << "Error:" << endl
	       << "Invalid Rotor Mapping in " << filename 
	       << "- Too many " << number 
	       << "s in file " 
	       << filename << ".\n";
	  exit(7);
	}
      
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      inflow.get(digit);
    }

  if(validConfig(config)) //Final check.
    {
      cerr << "Impossible reflector configuration:" << endl
	   << "Too many/few " << validConfig(config)
	   << "s in this file." << endl;
      exit(7);
    }

/*========================= Begins to read in notches =====================*/
  
  while(!inflow.eof())
    {
      int number(0);
      
      number = readNumber(inflow, digit, filename);

      if(number == -1)
	{
	  cerr << "Invalid Character..." << endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
      
      if(number < 0 || number > 25) //Checks valid input number in .rot file.
	{
	  cerr << "Error: In " << filename << ": "
	       << number << " is an invalid index." 
	       << endl;
	  exit(3);
	}
      
      if(notch[number]) //Check if number hasn't already been read.
	{
	  cerr << "Error: Invalid rotor mapping in " << filename << ":" 
	       << endl 
	       << "cannot add notch to position " << number 
	       << "more than once." 
	       << endl;
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

  cout << "Rotor successfully constructed." << endl << endl;
}

void Rotor::passThrough_R2L(int& n)
{
  if(n < 0 || n > 25)
    {
      cerr << "Error: " << n << " is not between 0 and 25." << endl;
      exit(3);
    }

  n = ((config[(n + missalignment) % 26] - missalignment) % 26);

  if(n < 0)
    n += 26; 
}

void Rotor::passThrough_L2R(int& n)
{
 
 if(n < 0 || n > 25)
    {
      cerr << "Error: " << n << " is not between 0 and 25." << endl;
      exit(3);
    }

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
