#include <iostream>
#include <cstdlib>
#include <fstream>
#include "rotor.h"
#include "plugboard.h"
#include "reflector.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv)
{
  //  char repeat;

  //  do
  //  {
      // char letter;
      // int num_input;

      Plugboard pb(argv[1]);
      Reflector rf(argv[2]);
      Rotor rot1(argv[3]);

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

	  /*
	  for(int k = 0; k < 26; k++)
	{
	  int buff = k;

	  pb.passThrough(buff);
	  rot1.passThrough_R2L(buff);
	  rf.passThrough(buff);
	  rot1.passThrough_L2R(buff);
	  pb.passThrough(buff);

	  pb.passThrough(buff);
	  rot1.passThrough_R2L(buff);
	  rf.passThrough(buff);
	  rot1.passThrough_L2R(buff);
	  pb.passThrough(buff);	  

	  cout << int_to_letter(buff);
	}

      cout << endl;
	  */

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







      /*
      cout << "What letter would you like to pass through the plugboard?"
	   << endl;

      cin >> letter;

      num_input = letter_to_int(letter);

      cout << num_input << endl;

      cout << "After passing the letter " << letter
	   << " through the plugboard, the result is: ";

      pb.passThrough(num_input);

      letter = int_to_letter(num_input);

      cout << letter << endl;

      */

      //      cout << endl << endl << "Start again? (y/n)" << endl;
      //      cin >> repeat;

      //    }
      //  while(repeat == 'y' || repeat == 'Y');


      cout << endl << endl << "End of testing." << endl;

  return 0;
}
