#include "toydbldalitzpdf.h"
using namespace std;

ToyDblDalitzPdf::ToyDblDalitzPdf(const std::string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_K, RooRealVar *_Kb, RooRealVar *_C, RooRealVar *_S, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig, RooResolutionModel *_model,const int _flv):
  dt(_dt),tau(_tau),dm(_dm),K(_K),Kb(_Kb),C(_C),S(_S),Kap(_Kap),Kapb(_Kapb),Cap(_Cap),Sig(_Sig),sin2phi1(_sin2phi1),cos2phi1(_cos2phi1),model(_model),flv(_flv)
{
  RooConstVar* f0   = new RooConstVar("f0flv","f0flv",1);
  RooConstVar* f1   = new RooConstVar("f1flv","f1flv",0);
  RooConstVar* flvr = new RooConstVar("flv","flv",flv);
  RooFormulaVar* f2 = new RooFormulaVar("f2","f2","@3*(1-2.*@0)*(@1*@4-@2*@5)/(@1*@4+@2*@5)",RooArgList(*wrtag,*Kap,*Kapb,*flvr,*K,*Kb));
  RooArgList arglist;
  arglist.add(*wrtag);
  arglist.add(*Kap);
  arglist.add(*Kapb);
  arglist.add(*Sig);
  arglist.add(*Cap);
  arglist.add(*sin2phi1);
  arglist.add(*cos2phi1);
  arglist.add(*flvr);
  arglist.add(*K);
  arglist.add(*Kb);
  arglist.add(*S);
  arglist.add(*C);
  RooFormulaVar* f3 = new RooFormulaVar("f3","f3","2.*@6*(1-2.*@0)*sqrt(@1*@2*@7*@8)/(@1*@7+@2*@8)*((@3*@10+@4*@9)*@6+(@4*@10-@3*@9)*@5)",arglist);
  RooConstVar* dgam = new RooConstVar("dgam","dgam",0);

  pdf = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
  return;
}
