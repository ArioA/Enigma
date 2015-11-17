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
  /*
    Errors relating to argument numbers go here.
    
    if(argc == 1){ERROR...}
    
    if(argc == 3){ERROR...}
  */
  
  Plugboard* pbPtr = new Plugboard(argv[1]);
  
  Reflector* rfPtr = new Reflector(argv[2]);
  
  if(argc > 4)
    {  
      int no_rotors(argc - 4);
      
      int* positions = new int[no_rotors];
      
      readPositions(positions, no_rotors, argv[argc -1]);
      
      for(int k = 0; k < no_rotors; k++)
	cout << positions[k] << " ";
      
      RotorPtr* linkedRotors = new RotorPtr[no_rotors];
      
      for(int k = 0; k < no_rotors; k++)
	{
	  /*rotors are configured as they appear on command line(check).*/
	  linkedRotors[k] = new Rotor(argv[argc - 2 - k], 
				      positions[no_rotors - 1 - k]);
	}
      
      char input_output;
      int num_io;
      
      cout << "Enter in CAPITAL letters "
	   << "what you would like to have encrytped." << endl
	   << "Press '.' when you are done." << endl;
      
      cin >> input_output;

      while(input_output != '.')
	{
	  if(isWhiteSpace(input_output))
	    {
	      cout << input_output;
	      cin >> input_output;
	      continue;
	    }
	  
	  num_io = letter_to_int(input_output);

	  passThroughEnigma(linkedRotors, no_rotors, pbPtr, rfPtr, num_io);
	  
	  cout << int_to_letter(num_io);
	  
	  cin >> input_output;
	}
      
      for(int k = 0; k < no_rotors; k++)
	delete [] linkedRotors[k];
      
      delete [] linkedRotors;
      
    }
  
  delete [] pbPtr;
  delete [] rfPtr;
  
  cout << endl << "End of testing." << endl << endl;
  
  return 0;
}
