#include "toycppdf.h"
#include "toyresmodel.h"
#include "toyvars.h"

using namespace std;

ToyCPPdf::ToyCPPdf(const string& label, RooAbsReal *_Kap, RooAbsReal *_Kapb, RooAbsReal *_Cap, RooAbsReal *_Sig, const int cp, const int flv):
  Cap(_Cap),Sig(_Sig),Kap(_Kap),Kapb(_Kapb)
{
  if(!cp || !flv) cout << "ToyCPPdf: Warning in initialization: cp " << cp << ", flv " << flv << endl;
  SetNames(cp,flv,label);
  dt       = ToyVars::Get_dt();
  tau      = ToyVars::Get_tau();
  f0       = new RooRealVar(f0name.c_str(),f0name.c_str(),1);
  f1       = new RooRealVar(f1name.c_str(),f1name.c_str(),0);
  dgam     = new RooRealVar(dgamname.c_str(),dgamname.c_str(),0); dgam->setConstant(kTRUE);
  flvr     = new RooRealVar(flvname.c_str(),flvname.c_str(),flv); flvr->setConstant(kTRUE);
  cpval    = new RooRealVar(cpname.c_str(),cpname.c_str(),cp);    cpval->setConstant(kTRUE);
  wrtag    = ToyVars::Get_wrtag();
  dm       = ToyVars::Get_dm();
  sin2beta = ToyVars::Get_sin();
  cos2beta = ToyVars::Get_cos();
  f2       = new RooFormulaVar(f2name.c_str(),f2name.c_str(),"@3*(1-2.*@0)*(@1-@2)/(@1+@2)",RooArgList(*wrtag,*Kap,*Kapb,*flvr));
  f3       = new RooFormulaVar(f3name.c_str(),f3name.c_str(),"2.*@8*@7*(1-2.*@0)*sqrt(@1*@2)/(@1+@2)*(@3*@6+@4*@5)",RooArgList(*wrtag,*Kap,*Kapb,*Sig,*Cap,*sin2beta,*cos2beta,*flvr,*cpval));
  model    = ToyResModel::GetModel();
  pdf      = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
}

RooDataSet* ToyCPPdf::Generate(const int Nev, const int flv, const int cp){
  flvr->setVal(flv);
  cpval->setVal(cp);
  return pdf->generate(*ToyVars::Get_dt(),Nev);
}

void ToyCPPdf::SetNames(const int cp,const int flv,const string& label){
  stringstream out;
  out.str(""); out << "flv";
       if(flv == 1) out << "p";
  else if(flv ==-1) out << "n";
  else if(flv == 0) out << "0";
  out << "cp";
       if(cp  == 1) out << "p";
  else if(cp  ==-1) out << "n";
  else if(cp  == 0) out << "0";
  out << label;

  f0name   = string("f0")     + out.str();
  f1name   = string("f1")     + out.str();
  f2name   = string("f2")     + out.str();
  f3name   = string("f3")     + out.str();
  flvname  = string("flvvar") + out.str();
  cpname   = string("cpvar")  + out.str();
  dgamname = string("dgam")   + out.str();
}

