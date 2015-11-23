#ifndef PLUGBOARD_H
#define PLUGBOARD_H


class Plugboard
{
 private:
  int config[26]; //Represents where k plug maps to config[k] plug.
  
 public:
  //Constructor for Plugboard class.
  Plugboard(const char* filename, int& errnum);

  //Precondition: n is an integer between 0 and 25.
  //Postcondition: Simulates the (n+1)th letter passing through the plugboard.
  //Invalid input character error lives here since plugboard is always
  //the first component which input passes through. 
  void passThrough(int& n);
};

#endif
