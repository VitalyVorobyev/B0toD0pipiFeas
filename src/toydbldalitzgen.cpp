#include "toydbldalitzgen.h"
#include <fstream>
using namespace std;

ToyDblDalitzGen::ToyDblDalitzGen(){
  GetParams("kspipi_eq_phase_params.txt",C,S,K,Kb);
  GetParams("d0pipi_eq_phase_params.txt",Cap,Sig,Kap,Kapb);
}

int ToyDblDalitzGen::GetParams(std::string fname,double* C,double* S,double* K,double* Kb){
  ifstream ifile(fname.c_str(),ifstream::in);
  if(!ifile.is_open()) return -1;
  string line;
  int bin;
  double c,s,k,kb,q;
  int flag;
  for(int i=0; i<8; i++){
    getline(ifile,line);
    flag = sscanf(line.c_str(),"%d: C = %lf, S = %lf, K = %lf, Kb = %lf, Q = %lf",&bin,&c,&s,&k,&kb,&q);
    if(i != (bin-1) || flag != 6) return -2;
    C[i]  = c; S[i]  = s; K[i]  = k; Kb[i] = kb;
  }
  return 0;
}
