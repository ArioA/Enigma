#include <iostream>
#include <cstdlib>
#include <fstream>
#include "configuration.h"
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv)
{
  /*
    Errors relating to argument numbers go here.
    
if(argc == 1){ERROR...}

if(argc == 3){ERROR...}
  */



  if(argc > 4)
    {  
      int no_rotors(argc - 4);

      int* positions = new int[no_rotors];
     
      readPositoins(positions, no_rotors, argv[argc -1]);
     
      Rotor** linkedRotors = new Rotor*[no_rotors];

      for(int k = 0; k < no_rotors; k++)
	{
	  /*rotors are configured as they appear on command line(check).*/
	  linkedRotors[k](argv[argc - 1 - k]);
	  configurePosition(linkedRotors[k], positions[k]);
	  //check spec: not sure if this is right.
	}

      
    }

  /* For testing readPosition().

      Plugboard pb(argv[1]);
      Reflector rf(argv[2]);
      Rotor rot1(argv[3]);
  */

  int* a = new int[3]; 

  readPositions(a, 3, argv[1]);

  for(int k = 0; k< 3; k++)
    cout << a[k] << " ";

  cout << endl;

  

  /*
 
      //Prints alphabet.

      for(int k = 0; k < 26; k++)
	{
	  cout << int_to_letter(k);
	}

      cout << endl;

      //Prints plugboard's effect.

      for(int k = 0; k < 26; k++)
	{
	  int buff = k;

	  pb.passThrough(buff);
	  
	  cout << int_to_letter(buff);
	}

      cout << endl;


      //Writes a full pass through the enigma of each letter 
      //in the alphabet to the output.igm file.

      ofstream write("output.igm");

      for(int k = 0; k < 26; k++)
	{
	  int buff = k;

	  //rot1.print_config();
	  //cout << endl;

	  rot1.rotate();
	  
	  pb.passThrough(buff);
	  rot1.passThrough_R2L(buff);
	  rf.passThrough(buff);
	  rot1.passThrough_L2R(buff);
	  pb.passThrough(buff);
	  
	  write << int_to_letter(buff);
	  
	}

      write << '\n';

      write.close();

      ifstream in("output.igm");

      char toprint;
      int numprint;

      in.get(toprint);

      //Reads the output.igm file and decrypts it.
      //Note: this works because we write to output.igm 26 times,
      //and so the rotor is back in it's original position.

      while(!in.eof() && toprint != '\n')
	{
	  numprint = letter_to_int(toprint);

	  rot1.rotate();

	  pb.passThrough(numprint);
	  rot1.passThrough_R2L(numprint);
	  rf.passThrough(numprint);
	  rot1.passThrough_L2R(numprint);
	  pb.passThrough(numprint);

	  cout << int_to_letter(numprint);

	  in.get(toprint);
	}

  */

      cout << endl << endl << "End of testing." << endl;

  return 0;
}
