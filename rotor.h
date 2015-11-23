#ifndef ROTOR_H
#define ROTOR_H

class Rotor
{
 private:
  int config[26];
  bool notch[26];
  int missalignment;

 public:
  //Constructor for Rotor.
  Rotor(const char* filename, const int& malign, int& errnum);

  //Preconditioin: n is an initiallised integer between 0 and 25.
  //Postcondition: simulates input passing through rotor from right to left
  //whilst taking into account any rotations via missalignment.
  void passThrough_R2L(int& n);

  //Preconditioin: Rotor object has been constructed and n is an initiallised
  //integer between 0 and 25.
  //Postcondition: simulates input passing through rotor from left to right
  //whilst taking into account any rotations via missalignment.
  void passThrough_L2R(int& n);

  //Precondition: Rotor object has been constructed.
  //Postcondition: simulates rotation of Rotor object. 
  void rotate();

  //Precondition: Rotor object has been constructed.
  //Postcondition: returns value of notch at 'A' position.
  bool get_notch();
};

#endif
