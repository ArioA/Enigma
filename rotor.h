#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
 private:
  int config[26];
  bool notch[26];

 public:
  Rotor(char* filename);
  void passThrough_L2R(int& n);
  void passThrough_R2L(int& n);
  void rotate();
  bool get_notch(int index);
  void print_config();
};

#endif
