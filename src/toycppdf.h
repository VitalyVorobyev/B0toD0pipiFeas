#ifndef TOYCPPDF_H
#define TOYCPPDF_H

#include "RooBDecay.h"
#include "RooResolutionModel.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "RooArgList.h"

#include <string>

class ToyCPPdf{
public:
  ToyCPPdf(const std::string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_wrtag, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig, RooResolutionModel* _model);
  RooBDecay* GetPdf(void) {return pdf;}
  RooDataSet* Generate(const int Nev, const int flv, const int cp);
  RooDataSet* Generate(const int Nev, const int flv, const int cp,const double& C,const double& S, const double& K, const double& Kb);

private:
  RooBDecay* pdf;

  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* dm;
  RooRealVar* wrtag;

  RooRealVar* cos2phi1;
  RooRealVar* sin2phi1;

  RooRealVar* Cap;
  RooRealVar* Sig;
  RooRealVar* Kap;
  RooRealVar* Kapb;

  RooRealVar* flvr;
  RooRealVar* cpval;

  RooResolutionModel* model;

  RooRealVar* f0;
  RooRealVar* f1;
  RooRealVar* dgam;
  RooFormulaVar* f2;
  RooFormulaVar* f3;
};

#endif // TOYCPPDF_H
