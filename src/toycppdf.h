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
  ToyCPPdf(const std::string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_wrtag, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig, RooResolutionModel* _model, const int _flv, const int _cp);
  RooBDecay* GetPdf(void) {return pdf;}

private:
  RooBDecay* pdf;
  int flv;
  int cp;

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

  RooResolutionModel* model;
};

#endif // TOYCPPDF_H
