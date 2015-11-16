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
  ToyFlvPdf(const std::string &label, RooRealVar *_dt, RooRealVar *_tau, RooRealVar *_dm, RooRealVar *_wrtag, RooResolutionModel *_model,const int _flv);
  RooBDecay* GetPdf(void) {return pdf;}

private:
  RooBDecay* pdf;

  int flv;

  RooRealVar* dt;
  RooRealVar* tau;
  RooRealVar* dm;
  RooRealVar* wrtag;
  RooResolutionModel* model;
};

#endif // TOYFLVPDF_H
