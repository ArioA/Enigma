#ifndef REFLECTOR_H
#define REFLECTOR_H


class Reflector
{
 private:
  int config[26];
  
 public:
  Reflector(char* filename);
  void passThrough(int& n);
};

#endif
