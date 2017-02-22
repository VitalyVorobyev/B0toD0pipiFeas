#include "toyflvpdf.h"
#include "toyresmodel.h"
#include "toyvars.h"

using namespace std;

ToyFlvPdf::ToyFlvPdf(const string& label, const int flv){
  if(!flv) cout << "ToyFlvPdf Warning: flv " << flv << endl;
  SetNames(flv,label);
  dt    = ToyVars::Get_dt();
  tau   = ToyVars::Get_tau();
  f0    = new RooRealVar(f0name.c_str(),f0name.c_str(),1); f0->setConstant(kTRUE);
  f1    = new RooRealVar(f1name.c_str(),f1name.c_str(),0); f1->setConstant(kTRUE);
  f3    = new RooRealVar(f3name.c_str(),f3name.c_str(),0); f3->setConstant(kTRUE);
  flvr  = new RooRealVar(flvname.c_str(),flvname.c_str(),flv);
  wrtag = ToyVars::Get_wrtag();
  dm    = ToyVars::Get_dm();
  f2    = new RooFormulaVar(f2name.c_str(),f2name.c_str(),"@1*(1.-2.*@0)",RooArgList(*wrtag,*flvr));
  dgam  = new RooRealVar(dgamname.c_str(),dgamname.c_str(),0); dgam->setConstant();
  model = ToyResModel::GetModel();
  pdf   = new RooBDecay(label.c_str(),label.c_str(),*dt,*tau,*dgam,*f0,*f1,*f2,*f3,*dm,*model,RooBDecay::DoubleSided);
//  pdf->Print("t");
}

RooDataSet* ToyFlvPdf::Generate(const int Nev,const int flv){
  flvr->setVal(flv);
  return pdf->generate(*dt,Nev);
}

void ToyFlvPdf::SetNames(const int flv,const string& label){
  stringstream out;
  out.str(""); out << "flv";
       if(flv == 1) out << "p";
  else if(flv ==-1) out << "n";
  else if(flv == 0) out << "0";
  out << label;
//  cout << "ToyFlvPdf suffix " << out.str() << endl;

  f0name   = string("f0") + out.str();
  f1name   = string("f1") + out.str();
  f2name   = string("f2") + out.str();
  f3name   = string("f3") + out.str();
  flvname  = string("flvvar") + out.str();
  dgamname = string("dgam") + out.str();
}
