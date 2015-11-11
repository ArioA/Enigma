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

      for(int k = 0; k < 26; k++)
	{
	  cout << int_to_letter(k);
	}

      cout << endl;

      for(int k = 0; k < 26; k++)
	{
	  int buff = k;

	  pb.passThrough(buff);
	  
	  cout << int_to_letter(buff);
	}

      cout << endl;

      for(int k = 0; k < 26; k++)
	{
	  int buff = k;

	  pb.passThrough(buff);
	  rot1.passThrough_R2L(buff);
	  rf.passThrough(buff);
	  rot1.passThrough_L2R(buff);
	  pb.passThrough(buff);
	  
	  cout << int_to_letter(buff);
	}

      cout << endl;

      rot1.print_config();

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

      ofstream write("output.igm");

      for(int k = 0; k < 26; k++)
	{
	  int buff = 0;

	  rot1.print_config();

	  cout << endl;

	  rot1.rotate();
	  /*
	  pb.passThrough(buff);
	  rot1.passThrough_R2L(buff);
	  rf.passThrough(buff);
	  rot1.passThrough_L2R(buff);
	  pb.passThrough(buff);
	  
	  write << int_to_letter(buff);
	  */
	}

      write << '\n';

      write.close();

      ifstream in("output.igm");

      char toprint;
      int numprint;

      in.get(toprint);

      while(!in.eof() && toprint != '\n')
	{
	  numprint = letter_to_int(toprint);

	  cout << toprint << " " << numprint << " ";

	  rot1.passThrough_R2L(numprint);
	  
	  cout << numprint << endl;

	  in.get(toprint);
	}

      int param;

      rot1.print_config();

      for(int k = 0; k < 26; k++)
	{
	  param = 16;

	  rot1.passThrough_R2L(param);

	  cout << param << endl;
	}

      cout << endl;


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
