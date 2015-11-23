#include <iostream>
#include <fstream>
#include "helper.h" //rotor.h, reflector.h and plugboard.h are all in here.
#include "configuration.h"
#include "errors.h"

using namespace std;

typedef Rotor* RotorPtr;

int main(int argc, char** argv)
{
  //Catches incorrect number of parameters.
  if(argc <= 2 || argc == 4)
    {
      cerr << "usage: enigma plugboard-file reflector-file "
	   << "(<rotor-file>* rotor-positions)?" << endl;

      return INSUFFICIENT_NUMBER_OF_PARAMETERS;
    }

  int errnum(0);
  
  //Create plugboard.
  Plugboard pb(argv[1], errnum);

  //Checks if plugboard was configured correctly.
  switch(errnum)
    {
    case 0: break;
    case 3: return INVALID_INDEX;
    case 4: return NON_NUMERIC_CHARACTER;
    case 5: return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    case 6: return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    case 11: return ERROR_OPENING_CONFIGURATION_FILE;
    default:
      cerr << "Something went wrong with error tracker." << endl;
      return 12;
    }

  Plugboard* pbPtr = &pb;
  

  //Create reflector.
  Reflector rf(argv[2], errnum);

  //Checks if reflector was configured correctly.
  switch(errnum)
    {
    case 0: break;
    case 3: return INVALID_INDEX;
    case 4: return NON_NUMERIC_CHARACTER;
    case 9: return INVALID_REFLECTOR_MAPPING;
    case 10: return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    case 11: return ERROR_OPENING_CONFIGURATION_FILE;
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

      //Checks if standard input stream input was valid.
      switch(errnum)
	{
	case 0: break;
	case 2: return INVALID_INPUT_CHARACTER;
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
	  
	  //Checks if linkedRotors[k] was successfully constructed,
	  //and delete as many rotors as have been created if not.
	  switch(errnum)
	    {
	    case 0: break;
	    case 3: 
	      deleteRotors(linkedRotors, k+1);
	      return INVALID_INDEX;
	    case 4: 
	      deleteRotors(linkedRotors, k+1);
	      return NON_NUMERIC_CHARACTER;
	    case 7: 
	      deleteRotors(linkedRotors, k+1);
	      return INVALID_ROTOR_MAPPING;
	    case 8: 
	      deleteRotors(linkedRotors, k+1);
	      return NO_ROTOR_STARTING_POSITION;
	    case 11: 
	      deleteRotors(linkedRotors, k+1);
	      return ERROR_OPENING_CONFIGURATION_FILE;
	    default:
	      cerr << "Something went wrong with error tracker." << endl;
	      deleteRotors(linkedRotors, k+1);
	      return 12;
	    }
	}
      //Create an array in which to store rotor positions.
      int* positions = new int[number_of_rotors];
      
      readPositions(positions, number_of_rotors, argv[argc -1], errnum);

      //Checks if positions were read and entered correctly.
      switch(errnum)
	{
	case 0: break;
	case 1: 
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	case 3:
	  deleteRotors(linkedRotors, number_of_rotors, positions); 
	  return INVALID_INDEX;
	case 4: 
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return NON_NUMERIC_CHARACTER;
	case 8:
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return NO_ROTOR_STARTING_POSITION;
	case 11:
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return ERROR_OPENING_CONFIGURATION_FILE;
	default:
	  cerr << "Something went wrong with error tracker." << endl;
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return 12;
	}

	//Implement read-in starting positions of rotors.
      for(int k = 0; k < number_of_rotors; k++)
	{
	  configurePosition(linkedRotors[k],
			    positions[number_of_rotors - 1 -k]);
	}

	//Begins 
      encrypt(linkedRotors, number_of_rotors, pbPtr, rfPtr, errnum);

      switch(errnum)
	{
	case 0: break;
	case 2:
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return INVALID_INPUT_CHARACTER;
	default: 
	  cerr << "Something went wrong with error tracker." << endl;
	  deleteRotors(linkedRotors, number_of_rotors, positions);
	  return 12;
	}

      //Clean up all the dynamically allocated memory.

      deleteRotors(linkedRotors, number_of_rotors, positions);
    }
 
  return NO_ERROR;
}
