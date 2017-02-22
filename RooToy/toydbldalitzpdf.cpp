#include "toydbldalitzpdf.h"
#include "toyresmodel.h"
#include "toyvars.h"

using namespace std;

ToyDblDalitzPdf::ToyDblDalitzPdf(const string& label, RooAbsReal *_K, RooAbsReal *_Kb, RooAbsReal *_C, RooAbsReal *_S, RooAbsReal *_Kap, RooAbsReal *_Kapb, RooAbsReal *_Cap, RooAbsReal *_Sig,const int flv):
  K(_K),Kb(_Kb), C(_C),S(_S),
  Kap(_Kap),Kapb(_Kapb),
  Cap(_Cap),Sig(_Sig)
{
  SetNames(label);
  f0   = new RooRealVar(f0name.c_str(),f0name.c_str(),1);     f0->setConstant(kTRUE);
  f1   = new RooRealVar(f1name.c_str(),f1name.c_str(),0);     f1->setConstant(kTRUE);
  flvr = new RooRealVar(flvname.c_str(),flvname.c_str(),flv); flvr->setConstant(kTRUE);
  f2   = new RooFormulaVar(f2name.c_str(),f2name.c_str(),"@3*(1-2.*@0)*(@1*@4-@2*@5)/(@1*@4+@2*@5)",RooArgList(*ToyVars::Get_wrtag(),*Kap,*Kapb,*flvr,*K,*Kb));
  RooArgList arglist;
  arglist.add(*ToyVars::Get_wrtag());// @0
  arglist.add(*Kap);                 // @1
  arglist.add(*Kapb);                // @2
  arglist.add(*Sig);                 // @3
  arglist.add(*Cap);                 // @4
  arglist.add(*ToyVars::Get_sin());  // @5
  arglist.add(*ToyVars::Get_cos());  // @6
  arglist.add(*flvr);                // @7
  arglist.add(*K);                   // @8
  arglist.add(*Kb);                  // @9
  arglist.add(*S);                   // @10
  arglist.add(*C);                   // @11
  f3 = new RooFormulaVar(f3name.c_str(),f3name.c_str(),"2.*@7*(1-2.*@0)*sqrt(@1*@2*@8*@9)/(@1*@8+@2*@9)*((@3*@11+@4*@10)*@6+(@4*@11-@3*@10)*@5)",arglist);
  dgam = new RooRealVar(dgamname.c_str(),dgamname.c_str(),0); dgam->setConstant(kTRUE);
  model = ToyResModel::GetModel();
  pdf = new RooBDecay(label.c_str(),label.c_str(),*ToyVars::Get_dt(),*ToyVars::Get_tau(),*dgam,*f0,*f1,*f2,*f3,*ToyVars::Get_dm(),*model,RooBDecay::DoubleSided);
  return;
}

RooDataSet* ToyDblDalitzPdf::Generate(const int Nev, const int flv){
  flvr->setVal(flv);
  return pdf->generate(*ToyVars::Get_dt(),Nev);
}

void ToyDblDalitzPdf::SetNames(const string& label){
  f0name   = string("f0")     + label;
  f1name   = string("f1")     + label;
  f2name   = string("f2")     + label;
  f3name   = string("f3")     + label;
  flvname  = string("flvvar") + label;
  dgamname = string("dgam")   + label;
}

