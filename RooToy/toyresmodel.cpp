#include "toyresmodel.h"
#include "toyvars.h"

RooRealVar*    ToyResModel::v_mean;
RooRealVar*    ToyResModel::v_sigma;
RooGaussModel* ToyResModel::v_model;

ToyResModel::ToyResModel() {}

void ToyResModel::InitResolution(const double mean, const double sigma){
  v_mean  = new RooRealVar("res_mean","res_mean",mean);
  v_sigma = new RooRealVar("res_sigma","res_sigma",sigma);
  v_model = new RooGaussModel("gauss","gauss",*ToyVars::Get_dt(),*v_mean,*v_sigma);
  FixResolution();
  std::cout << "Resolution model is initialized" << std::endl;
}

void ToyResModel::FixResolution(void){
  v_sigma->setConstant(kTRUE);
  v_mean->setConstant(kTRUE);
}

void ToyResModel::ReleaseResolution(void){
  v_sigma->setConstant(kFALSE);
  v_mean->setConstant(kFALSE);
}

void ToyResModel::SetResolution(const double& m,const double& s){
  v_mean->setVal(m);
  v_sigma->setVal(s);
}
