#ifndef REFLECTOR_H
#define REFLECTOR_H


class Reflector
{
 private:
  int config[26];
  
 public:
  //Constructor for Reflector class.
  Reflector(const char* filename, int& errnum);

  //Precondition: Reflector object has been successfully constructed. Also,
  //n is an initiallised integer between 0 and 25.
  //Postcondition: Simulates effect of reflecting (n+1)th letter in the
  //alphabet in reflector object.
  void passThrough(int& n);
};

#endif
