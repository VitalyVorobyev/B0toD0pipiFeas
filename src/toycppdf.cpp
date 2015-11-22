#include "toycppdf.h"
#include "RooGaussian.h"
using namespace std;

ToyCPPdf::ToyCPPdf(const string& label, RooRealVar* _dt, RooRealVar* _tau, RooRealVar *_dm, RooRealVar *_sin2phi1, RooRealVar *_cos2phi1, RooRealVar *_wrtag, RooRealVar *_Kap, RooRealVar *_Kapb, RooRealVar *_Cap, RooRealVar *_Sig,RooResolutionModel* _model):
  dt(_dt),tau(_tau),dm(_dm),wrtag(_wrtag),
  cos2phi1(_sin2phi1),sin2phi1(_cos2phi1),
  Cap(_Cap),Sig(_Sig),Kap(_Kap),Kapb(_Kapb),
  model(_model)
{
//  std::cout << "ToyCPPdf constructor" << std::endl;
  f0    = new RooRealVar("f0","f0",1);
  f1    = new RooRealVar("f1","f1",0);
  dgam  = new RooRealVar("dgam","dgam",0);

  flvr  = new RooRealVar("flv","flv",1);
  cpval = new RooRealVar("cpval","cpval",1);
  f2    = new RooFormulaVar("f2","f2","@3*(1-2.*@0)*(@1-@2)/(@1+@2)",RooArgList(*wrtag,*Kap,*Kapb,*flvr));
  f3    = new RooFormulaVar("f3","f3","2.*@8*@7*(1-2.*@0)*sqrt(@1*@2)/(@1+@2)*(@3*@6+@4*@5)",RooArgList(*wrtag,*Kap,*Kapb,*Sig,*Cap,*sin2phi1,*cos2phi1,*flvr,*cpval));
  pdf   = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
}

RooDataSet* ToyCPPdf::Generate(const int Nev, const int flv, const int cp){
  flvr->setVal(flv);
  cpval->setVal(cp);
  return pdf->generate(*dt,Nev);
}

RooDataSet* ToyCPPdf::Generate(const int Nev, const int flv, const int cp,const double& C,const double& S, const double& K, const double& Kb){
  flvr->setVal(flv);
  cpval->setVal(cp);
  Cap->setVal(C);
  Sig->setVal(S);
  Kap->setVal(K);
  Kapb->setVal(Kb);

  return pdf->generate(*dt,Nev);
}
