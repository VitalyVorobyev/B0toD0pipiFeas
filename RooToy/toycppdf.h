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
  ToyCPPdf(const std::string& label, RooAbsReal *_Kap, RooAbsReal *_Kapb, RooAbsReal *_Cap, RooAbsReal *_Sig, const int cp = 0, const int flv = 0);
  RooBDecay* GetPdf(void) {return pdf;}
  RooDataSet* Generate(const int Nev, const int flv, const int cp);

private:
  void SetNames(const int cp, const int flv,const std::string& label);
  RooBDecay* pdf;

  RooAbsReal* Cap;
  RooAbsReal* Sig;
  RooAbsReal* Kap;
  RooAbsReal* Kapb;

  RooRealVar* flvr;
  RooRealVar* cpval;
  RooRealVar* dgam;
  RooFormulaVar* f2;
  RooFormulaVar* f3;
//  RooRealVar* f3;

  RooRealVar* f0;
  RooRealVar* f1;
  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* wrtag;
  RooRealVar* dm;
  RooRealVar* sin2beta;
  RooRealVar* cos2beta;

  RooResolutionModel* model;
  std::string f0name,f1name,f2name,f3name,flvname,cpname,dgamname;
};

#endif // TOYCPPDF_H
