#ifndef TOYCAT_H
#define TOYCAT_H

#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooSuperCategory.h"

/// Class for keeping and manipulations with bin-independent RooCategories

class ToyCat{
public:
  ToyCat() {}
  static void InitCat(void);
  static RooArgSet* GetASet(void) {return v_cat_argset;}
  static RooSuperCategory* GetSuperCat(void)   {return v_cat;}
  static RooSuperCategory* GetCPSuperCat(void) {return v_cpcat;}
  static RooSuperCategory* GetDDSuperCat(void) {return v_ddcat;}

  static RooCategory* GetBBin(void) {return v_bbin;}
  static RooCategory* GetDBin(void) {return v_dbin;}
  static RooCategory* GetFlv(void)  {return v_flv;}
  static RooCategory* GetCP(void)   {return v_cp;}

  static int BinInd(const int bin);
  static int Bin(const int ind);
  static int FlvInd(const int flv);
  static int Flv(const int ind);
  static int CPInd(const int cp);
  static int CP(const int ind);

private:
  static RooCategory* v_bbin;
  static RooCategory* v_dbin;
  static RooCategory* v_cp;
  static RooCategory* v_flv;
  static RooSuperCategory* v_cat;
  static RooSuperCategory* v_cpcat;
  static RooSuperCategory* v_ddcat;
  static RooArgSet* v_cat_argset;
};

#endif // TOYCAT_H

