#ifndef TOYFLVPDF_H
#define TOYFLVPDF_H

#include "RooBDecay.h"
#include "RooResolutionModel.h"
#include "RooConstVar.h"
#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "RooArgList.h"

#include <string>

class ToyFlvPdf{
public:
  ToyFlvPdf(const std::string &label, RooRealVar *_dt, RooRealVar *_tau, RooRealVar *_dm, RooRealVar *_wrtag, RooResolutionModel *_model);
  RooBDecay* GetPdf(void) {return pdf;}

  RooDataSet* Generate(const int Nev,const int flv);

  static const int B0  = 1;
  static const int B0B =-1;

private:
  RooBDecay* pdf;

  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* dm;
  RooRealVar* wrtag;
  RooResolutionModel* model;

  RooRealVar* flvr;
};

#endif // TOYFLVPDF_H
