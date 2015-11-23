#include<iostream>
#include<fstream>
#include"rotor.h"
#include"helper.h"

using namespace std;

//Constructor for Rotor.
Rotor::Rotor(const char* filename, const int& _msalgn, int& errnum):
  missalignment(_msalgn)
{
  ifstream inflow;
  inflow.open(filename);

  //Checks if file could be openned.
  if(!inflow)
    {
      cerr << "Unable to open rotor file: " << filename << ".\n";
      errnum = 11;
      return;
    }

  //Default 'empty' setup:
  for(int k = 0; k < 26; k++)
    {
      config[k] = -1;
      notch[k] = false;
    }

  //digit is the charater which is read in.
  //notchCount counts the number of notches in the rotor file.
  char digit;
  int notchCount(0);

  /*==================Begin reading in from rotor  file.=====================*/

  inflow.get(digit);

  for(int count = 0; count < 26; count++)//Compulsory 26 letter mappings.
    {
      //number is integer which is read in.
     int  number(0);

     //Checks if file contains too few rotor mappings.
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
      else if(number < 0 || number > 25) // in rotor file.
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
      
      //Complete mapping.
      config[count] = number;

      //Skips all white space characters.
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      //On to next non-white-space character.
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

      //Checks if too many notches are in rotor file.
      if(notchCount > 25)
	{
	  cerr << "Invalid rotor mapping in rotor file " << filename
	       << " too many inputs for notches." << endl;
	  errnum = 7;
	  return;
	}
      
      //Again, number is integer to be read in.
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
      else if(number < 0 || number > 25) //number in rotor file.
	{
	  cerr << "Invalid index in rotor file " << filename
	       << ": " << number << " is not a valid index." << endl;
	  errnum = 3;
	  return;
	}
      
      if(notch[number]) //Check if number hasn't already been read.
	{
	  cerr << "Invalid rotor mapping in rotor file " << filename
	       << " cannot add notch to same position twice."
	       << endl;
	  errnum = 7;
	  return;
	}
      else
	notch[number] = true; //Complete notch insertion.

      notchCount++;

      //Skip all white-space characters.
      while(isWhiteSpace(inflow.peek()))
	{
	  inflow.get(digit);
	}

      //On to next non-white-space character.
      inflow.get(digit);
    }

  //Finished reading.
  inflow.close();
}

//Preconditioin: n is an initiallised integer between 0 and 25.
//Postcondition: simulates input passing through rotor from right to left
//whilst taking into account any rotations via missalignment.
void Rotor::passThrough_R2L(int& n)
{
  n = ((config[(n + missalignment) % 26] - missalignment) % 26);

  if(n < 0)
    n += 26; 
}

//Preconditioin: Rotor object has been constructed and n is an initiallised
//integer between 0 and 25.
//Postcondition: simulates input passing through rotor from left to right
//whilst taking into account any rotations via missalignment.
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

//Precondition: Rotor object has been constructed.
//Postcondition: simulates rotation of Rotor object. 
void Rotor::rotate()
{
  missalignment = (missalignment + 1) % 26;
}

//Precondition: Rotor object has been constructed.
//Postcondition: returns value of notch at 'A' position.
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
