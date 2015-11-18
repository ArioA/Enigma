#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
 private:
  int config[26];
  bool notch[26];
  int missalignment;

 public:
  Rotor(char* filename, int malign, int& errnum);
  void passThrough_L2R(int& n);
  void passThrough_R2L(int& n);
  void rotate();
  bool get_notch();
  void print_config();
};

#endif
