#ifndef TOYFLVPDF_H
#define TOYFLVPDF_H

#include "RooBDecay.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"

#include <string>

class ToyFlvPdf{
public:
  ToyFlvPdf(const std::string &label, const int flv = 0);
  RooBDecay* GetPdf(void) {return pdf;}
  RooDataSet* Generate(const int Nev,const int flv);
private:
  void SetNames(const int flv, const std::string &label);
  // True parameters
  RooBDecay* pdf;
  RooFormulaVar* f2;
  RooRealVar* flvr;
  RooRealVar* dgam;

  // References to global vars
  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* f0;
  RooRealVar* f1;
  RooRealVar* f3;
  RooRealVar* wrtag;
  RooRealVar* dm;

  RooResolutionModel* model;

  std::string f0name,f1name,f2name,f3name,flvname,dgamname;
};

#endif // TOYFLVPDF_H
