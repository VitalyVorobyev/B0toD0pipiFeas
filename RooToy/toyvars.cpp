#include "toyvars.h"

RooRealVar* ToyVars::v_dt;
RooRealVar* ToyVars::v_tau;
RooRealVar* ToyVars::v_dm;
RooRealVar* ToyVars::v_wrtag;
RooRealVar* ToyVars::v_cos2phi1;
RooRealVar* ToyVars::v_sin2phi1;

void ToyVars::InitVars(void){
  v_dt       = new RooRealVar("dt","dt",-70,70,"ps");
  v_tau      = new RooRealVar("tau","tau",1.520,0.11,3,"ps");
  v_dm       = new RooRealVar("dm","dm",0.505,0.02,10.);
  v_wrtag    = new RooRealVar("wrtag","wrtag",0.3,0.0,0.5);
  v_cos2phi1 = new RooRealVar("cos2phi1","cos2phi1",cos(23/180.*3.1415),-5.,5.);
  v_sin2phi1 = new RooRealVar("sin2phi1","sin2phi1",sin(23/180.*3.1415),-5.,5.);
  v_wrtag->setConstant(kTRUE);
  v_dm->setConstant(kTRUE);
}

void ToyVars::Set_dt_lim(const double& lval, const double& rval){
  v_dt->setRange(lval,rval);
}

void ToyVars::Set_tau(const double& val){
  v_tau->setVal(val);
}
void ToyVars::Set_dm(const double& val){
  v_dm->setVal(val);
}
void ToyVars::Set_wrtag(const double& val){
  v_wrtag->setVal(val);
}

void ToyVars::Set_sin(const double& val){
  v_sin2phi1->setVal(val);
}

void ToyVars::Set_cos(const double& val){
  v_cos2phi1->setVal(val);
}

void ToyVars::Fix_tau(const bool val){
  v_tau->setConstant(val ? kTRUE : kFALSE);
}

void ToyVars::Fix_dm(const bool val){
  v_dm->setConstant(val ? kTRUE : kFALSE);
}

void ToyVars::Fix_wrtag(const bool val){
  v_wrtag->setConstant(val ? kTRUE : kFALSE);
}

void ToyVars::Fix_sin(const bool val){
  v_sin2phi1->setConstant(val ? kTRUE : kFALSE);
}

void ToyVars::Fix_cos(const bool val){
  v_cos2phi1->setConstant(val ? kTRUE : kFALSE);
}

RooRealVar* ToyVars::Get_dt(void){
  return v_dt;
}

RooRealVar* ToyVars::Get_tau(void){
  return v_tau;
}

RooRealVar* ToyVars::Get_dm(void){
  return v_dm;
}

RooRealVar* ToyVars::Get_wrtag(void){
  return v_wrtag;
}

RooRealVar* ToyVars::Get_sin(void){
  return v_sin2phi1;
}

RooRealVar* ToyVars::Get_cos(void){
  return v_cos2phi1;
}
