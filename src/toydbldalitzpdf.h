#ifndef TOYDBLDALITZPDF_H
#define TOYDBLDALITZPDF_H

#include "RooBDecay.h"
#include "RooResolutionModel.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "RooArgList.h"

#include <string>

class ToyDblDalitzPdf{
public:
  ToyDblDalitzPdf(const std::string& label, RooRealVar *_dt, RooRealVar *_tau, RooRealVar* _dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_K, RooRealVar *_Kb, RooRealVar *_C, RooRealVar *_S, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig,RooResolutionModel* _model,const int _flv);
  RooBDecay* GetPdf(void) {return pdf;}

private:
  RooResolutionModel* model;
  int flv;

  RooBDecay* pdf;

  RooRealVar* wrtag;
  RooRealVar* tau;
  RooRealVar* dm;
  RooRealVar* cos2phi1;
  RooRealVar* sin2phi1;

  RooRealVar* K;
  RooRealVar* Kb;
  RooRealVar* C;
  RooRealVar* S;

  RooRealVar* Cap;
  RooRealVar* Sig;
  RooRealVar* Kap;
  RooRealVar* Kapb;

  RooRealVar* dt;
};

#endif // TOYDBLDALITZPDF_H
