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
  ToyDblDalitzPdf(const std::string& label, RooAbsReal *_K, RooAbsReal *_Kb, RooAbsReal *_C, RooAbsReal *_S, RooAbsReal *_Kap, RooAbsReal *_Kapb, RooAbsReal *_Cap, RooAbsReal *_Sig, const int flv = 0);
  RooBDecay* GetPdf(void) {return pdf;}
  RooDataSet* Generate(const int Nev, const int flv);

private:
  void SetNames(const std::string& label);

  RooBDecay* pdf;
  RooRealVar* flvr;

  RooAbsReal* K;
  RooAbsReal* Kb;
  RooAbsReal* C;
  RooAbsReal* S;

  RooAbsReal* Kap;
  RooAbsReal* Kapb;
  RooAbsReal* Cap;
  RooAbsReal* Sig;

  RooRealVar* f0;
  RooRealVar* f1;
  RooRealVar* dgam;
  RooFormulaVar* f2;
  RooFormulaVar* f3;

  RooResolutionModel* model;
  std::string f0name,f1name,f2name,f3name,flvname,dgamname;
};

#endif // TOYDBLDALITZPDF_H
