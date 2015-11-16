#ifndef TOYDBLDALITZGEN_H
#define TOYDBLDALITZGEN_H

#include <string>

class ToyDblDalitzGen{
public:
  ToyDblDalitzGen();

private:
  int GetParams(std::string fname,double* C,double* S,double* K,double* Kb);
  double C[8],S[8],K[8],Kb[8];
  double Cap[8],Sig[8],Kap[8],Kapb[8];
};

#endif // TOYDBLDALITZGEN_H
