#ifndef TOYRESMODEL_H
#define TOYRESMODEL_H

#include "RooGaussModel.h"
#include "RooRealVar.h"
#include "RooGaussian.h"

class ToyResModel{
public:
  ToyResModel();
  static void InitResolution(const double mean = 0, const double sigma = 0.8);
  static void FixResolution(void);
  static void ReleaseResolution(void);
  static void SetResolution(const double& m,const double& s);

  static RooGaussModel* GetModel(void) {return v_model;}

private:
  static RooRealVar* v_mean;
  static RooRealVar* v_sigma;
  static RooGaussModel* v_model;
};

#endif // TOYRESMODEL_H
