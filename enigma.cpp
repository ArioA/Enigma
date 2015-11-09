#include <iostream>
#include <cstdlib>
#include "plugboard.h"
#include "helper.h"

using namespace std;

int main(int argc, char** argv)
{
  char repeat;

  do
    {
      char letter;
      int num_input;

      Plugboard pb(argv[1]);

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

      cout << endl << "Start again? (y/n)" << endl;
      cin >> repeat;

    }
  while(repeat == 'y' || repeat == 'Y');


  cout << "End of testing." << endl;

  return 0;
}
