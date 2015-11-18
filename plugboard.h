#ifndef PLUGBOARD_H
#define PLUGBOARD_H


class Plugboard
{
 private:
  int config[26]; //Represents where k plug maps to config[k] plug.
  
 public:
  Plugboard(char* filename, int& errnum);
  void passThrough(int& n);
};

#endif
