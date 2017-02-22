#ifndef TOYVARS_H
#define TOYVARS_H

#include "RooRealVar.h"

/// Class for keeping and manipulations with bin-independent RooRealVars

class ToyVars{
public:
  ToyVars() {}
  static void InitVars(void);

  static RooRealVar* Get_dt(void);
  static RooRealVar* Get_tau(void);
  static RooRealVar* Get_dm(void);
  static RooRealVar* Get_wrtag(void);
  static RooRealVar* Get_sin(void);
  static RooRealVar* Get_cos(void);

  static void Set_dt_lim(const double& lval, const double& rval);
  static void Set_tau(const double& val);
  static void Set_dm(const double& val);
  static void Set_wrtag(const double& val);
  static void Set_sin(const double& val);
  static void Set_cos(const double& val);

  static void Fix_tau(const bool val);
  static void Fix_dm(const bool val);
  static void Fix_wrtag(const bool val);
  static void Fix_sin(const bool val);
  static void Fix_cos(const bool val);

private:
  static RooRealVar* v_dt;
  static RooRealVar* v_tau;
  static RooRealVar* v_dm;
  static RooRealVar* v_wrtag;
  static RooRealVar* v_cos2phi1;
  static RooRealVar* v_sin2phi1;
};

#endif // TOYVARS_H
