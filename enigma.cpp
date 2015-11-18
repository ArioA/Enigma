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
      cerr << "usage: enigma plugboard-file reflector-file "
	   << "(<rotor-file>* rotor-positions)?" << endl;

      return 1;
    }

  int errnum(0);
  
  //Create plugboard.
  Plugboard pb(argv[1], errnum);

  switch(errnum)
    {
    case 0: break;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 11: return 11;
    default:
      cerr << "Something went wrong with error tracker." << endl;
      return 12;
    }

  Plugboard* pbPtr = &pb;
  

  //Create reflector.
  Reflector rf(argv[2], errnum);

  switch(errnum)
    {
    case 0: break;
    case 3: return 3;
    case 4: return 4;
    case 9: return 9;
    case 10: return 10;
    case 11: return 11;
    default:
      cerr << "Something went wrong with error tracker." << endl;
      return 12;
    }

  Reflector* rfPtr = &rf;
  

  //Get number of rotors bassed on number of command line arguments.
  int number_of_rotors(argc - 4 > 0 ? argc - 4 : 0);
  


  if(!number_of_rotors) //If there are no rotors.
    {
      encrypt(pbPtr, rfPtr, errnum); //Different encrypt() function 
                                     //for no rotors.

      switch(errnum)
	{
	case 0: break;
	case 2: return 2;
	default: 
	  cerr << "Something went wrong with error tracker." << endl;
	  return 12;
	}
    }
  else //If there is at least one rotor.
    {      
      //Create as many rotors as we have as arguments.
      RotorPtr* linkedRotors = new RotorPtr[number_of_rotors];
      
      for(int k = 0; k < number_of_rotors; k++)
	{
	  //Rotors are configured as they appear on command line.
	  linkedRotors[k] = new Rotor(argv[argc - 2 - k], 
				      0,
				      errnum);
	  
	  switch(errnum)
	    {
	    case 0: break;
	    case 3: return 3;
	    case 4: return 4;
	    case 7: return 7;
	    case 8: return 8;
	    case 11: return 11;
	    default:
	      cerr << "Something went wrong with error tracker." << endl;
	      return 12;
	    }
	}
      
      int* positions = new int[number_of_rotors];
      
      readPositions(positions, number_of_rotors, argv[argc -1], errnum);

      switch(errnum)
	{
	case 0: break;
	case 1: return 1;
	case 3: return 3;
	case 4: return 4;
	case 8: return 8;
	case 11: return 11;
	default:
	  cerr << "Something went wrong with error tracker." << endl;
	  return 12;
	}

      for(int k = 0; k < number_of_rotors; k++)
	{
	  configurePosition(linkedRotors[k],
			    positions[number_of_rotors - 1 -k]);
	}

      encrypt(linkedRotors, number_of_rotors, pbPtr, rfPtr, errnum);

      switch(errnum)
	{
	case 0: break;
	case 2: return 2;
	default: 
	  cerr << "Something went wrong with error tracker." << endl;
	  return 12;
	}

      //Clean up all the dynamically allocated memory.

      for(int k = 0; k < number_of_rotors; k++)
	delete [] linkedRotors[k];

      delete [] linkedRotors;
      delete [] positions;
    }
 
  return 0;
}
