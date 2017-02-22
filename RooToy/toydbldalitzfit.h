#ifndef TOYDBLDALITZFIT_H
#define TOYDBLDALITZFIT_H

#include "toyflvpdf.h"
#include "toycppdf.h"
#include "toydbldalitzpdf.h"
#include "abstoydbldalitz.h"
#include "toycat.h"
#include "toysimpdf.h"

#include "RooSimultaneous.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooCategory.h"
#include "RooFitResult.h"
#include "RooDataSet.h"

class ToyDblDalitzFit : public ToySimPdf{
public:
  ToyDblDalitzFit();

  RooFitResult* FitFlv(RooDataSet* ds);
  RooFitResult* FitLifetime(RooDataSet* ds);
  RooFitResult* FitCP(RooDataSet* ds);
  RooFitResult* FitDblDlz(RooDataSet* ds);
  RooFitResult* FitSimul(RooDataSet* ds);

private:

};

#endif // TOYDBLDALITZFIT_H

