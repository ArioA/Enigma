#include<iostream>

using namespace std;

//===========================Conversion Functions=======================


//Precondition: digit is a digit (0, 1, ..., 9).
//Returns digit as an integer.
int digit_to_int(char digit)
{
  return (static_cast<int>(digit) - 48);
}

//Precondition: number is between 0 and 9.
//Returns number as a char.
char int_to_digit(int number)
{
  return (static_cast<int>(number + 48));
}


//Precondition: number is between 0 and 25.
//Returns alphabetic equivalent as capital letter.
char int_to_letter(int number)
{
  return (static_cast<char>(number + 65));
}

//Precondition: alpha is a capital letter.
//Returns integer representation of alpha.
int letter_to_int(char alpha)
{
  return (static_cast<int>(alpha) - 65);
}

//==================================================================
//=======================Checking Functions=========================


//Precondition: digit is any character.
//Returns true is digit is a digit, false otherwise.
bool isDigit(char digit)
{
  if(digit_to_int(digit) < 0 || digit_to_int(digit) > 9)
    {
      return false;
    }
  else
    return true;
}

//Precondition: character is an initialised char variable.
//Returns true if character is an alphabetic character. False otherwise.
bool isLetter(char character)
{
  if((character >= 'a' && character <= 'z') ||
     (character >= 'A' && character <= 'Z'))
     {
       return true;
     }

return false;
}

bool isWhiteSpace(char character)
{
  if(character == 32 || character == 10 || character == 9 ||
     character == 13)
    return true;

  return false;
}


//Precondition: nums[] is a filled array of integers.
//Returns true if nums[] is a valid configuration for a plugboard.
//That is, if each integer in nums is between 0 and 25, and each 
//integer occurs exactly once.
int validConfig(int nums[26])
{
  int occurences[26];

  for(int k = 0; k < 26; k++)
    {
      occurences[k] = 0;

      for(int j = 0; j < 26; j++)
	{
	  if(k == nums[j])
	    occurences[k]++;
	}
    }

  for(int k = 0; k < 26; k++)
    {
      if(occurences[k] - 1 != 0)
	return nums[k];
    }

  return 0;
}

//====================================================================
