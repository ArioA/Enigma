#include <iostream>
#include <cstdlib>
#include <fstream>
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"
#include "helper.h"
#include "configuration.h"

using namespace std;

typedef Rotor* RotorPtr;

int main(int argc, char** argv)
{

  //Catches incorrect number of parameters.
  if(argc <= 2 || argc == 4)
    {
      cerr << "Insufficient Number of Parameters Error:" << endl
	   << "You cannot have " << argc;
      if(argc-1)
	cerr << " parameters." << endl;
      else
	cerr << " parameter." << endl;

      return 1;
    }
  
  //Create plugboard.
  Plugboard* pbPtr = new Plugboard(argv[1]);
  

  //Create reflector.
  Reflector* rfPtr = new Reflector(argv[2]);
  

  //Get number of rotors bassed on number of command line arguments.
  int number_of_rotors(argc - 4 > 0 ? argc - 4 : 0);
  


  if(!number_of_rotors) //If there are no rotors.
    {
      encrypt(pbPtr, rfPtr); //Different encrypt() function for no rotors.
    }
  else //If there is at least one rotor.
    {
      int* positions = new int[number_of_rotors];
      
      readPositions(positions, number_of_rotors, argv[argc -1]);
      
      //Create as many rotors as we have as arguments.
      RotorPtr* linkedRotors = new RotorPtr[number_of_rotors];
      
      for(int k = 0; k < number_of_rotors; k++)
	{
	  //Rotors are configured as they appear on command line.
	  linkedRotors[k] = new Rotor(argv[argc - 2 - k], 
				      positions[number_of_rotors - 1 - k]);
	}

      encrypt(linkedRotors, number_of_rotors, pbPtr, rfPtr);

      //Clean up all the dynamically allocated memory.

      for(int k = 0; k < number_of_rotors; k++)
	delete [] linkedRotors[k];

      delete [] linkedRotors;
      delete [] positions;
    }
  
  
  delete [] pbPtr;
  delete [] rfPtr;

  return 0;
}
