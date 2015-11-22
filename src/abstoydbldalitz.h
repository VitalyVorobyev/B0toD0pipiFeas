#ifndef ABSTOYDBLDALITZ_H
#define ABSTOYDBLDALITZ_H

#include "RooRealVar.h"
#include "RooResolutionModel.h"

class AbsToyDblDalitz{
public:
  AbsToyDblDalitz();

  int GetParams(std::string fname,double* C,double* S,double* K,double* Kb);

protected:
  double m_C[8],m_S[8],m_K[8],m_Kb[8];
  double m_Cap[8],m_Sig[8],m_Kap[8],m_Kapb[8];

  double m_dt_min;
  double m_dt_max;
  double m_tau;
  double m_dm;
  double m_wrtag;

  double m_res_mean;
  double m_res_sigma;

  double m_cos2phi1;
  double m_sin2phi1;

  void SetVars(void);

  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* dm;
  RooRealVar* wrtag;
  RooResolutionModel* res_model;

  RooRealVar* cos2phi1;
  RooRealVar* sin2phi1;

  RooRealVar* Cap;
  RooRealVar* Sig;
  RooRealVar* Kap;
  RooRealVar* Kapb;

  RooRealVar* res_mean;
  RooRealVar* res_sigma;
};

#endif // ABSTOYDBLDALITZ_H
