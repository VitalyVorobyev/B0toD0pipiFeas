#include "toycppdf.h"
using namespace std;

ToyCPPdf::ToyCPPdf(const string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_wrtag, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig,RooResolutionModel* _model,const int _flv,const int _cp):
  dt(_dt),tau(_tau),dm(_dm),wrtag(_wrtag),model(_model),
  Kap(_Kap),Kapb(_Kapb),Cap(_Cap),Sig(_Sig),
  sin2phi1(_sin2phi1),cos2phi1(_cos2phi1),
  flv(_flv),cp(_cp)
{
  RooConstVar* f0    = new RooConstVar("f0","f0",1);
  RooConstVar* f1    = new RooConstVar("f1","f1",0);
  RooConstVar* flvr  = new RooConstVar("flv","flv",flv);
  RooFormulaVar* f2  = new RooFormulaVar("f2","f2","@3*(1-2.*@0)*(@1-@2)/(@1+@2)",RooArgList(*wrtag,*Kap,*Kapb,*flvr));
  RooConstVar* cpval = new RooConstVar("cp","cp",cp);
  RooFormulaVar* f3  = new RooFormulaVar("f3","f3","2.*@6*@7*(1-2.*@0)*sqrt(@1*@2)/(@1+@2)*(@3*@6+@4*@5)",RooArgList(*wrtag,*Kap,*Kapb,*Sig,*Cap,*sin2phi1,*cos2phi1,*flvr,*cpval));
  RooConstVar* dgam  = new RooConstVar("dgam","dgam",0);

  pdf = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
}
