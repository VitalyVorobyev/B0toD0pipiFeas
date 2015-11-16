#include "toyflvpdf.h"
using namespace std;
using namespace RooFit;

ToyFlvPdf::ToyFlvPdf(const string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_wrtag, RooResolutionModel* _model, const int _flv):
  dt(_dt),tau(_tau),dm(_dm),wrtag(_wrtag),model(_model),flv(_flv)
{
  RooConstVar* f0   = new RooConstVar("f0","f0",1);
  RooConstVar* f1   = new RooConstVar("f1","f1",0);
  RooConstVar* flvr = new RooConstVar("flv","flv",flv);
  RooFormulaVar* f2 = new RooFormulaVar("f2","f2","@1*(1-2.*@0)",RooArgList(*wrtag,*flvr));
  RooConstVar* f3   = new RooConstVar("f3","f3",0);
  RooConstVar* dgam = new RooConstVar("dgam","dgam",0);

  pdf = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
}
