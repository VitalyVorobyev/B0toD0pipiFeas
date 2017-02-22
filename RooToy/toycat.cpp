#include "toycat.h"
#include <sstream>

RooCategory*      ToyCat::v_bbin;
RooCategory*      ToyCat::v_dbin;
RooCategory*      ToyCat::v_cp;
RooCategory*      ToyCat::v_flv;
RooSuperCategory* ToyCat::v_cat;
RooSuperCategory* ToyCat::v_cpcat;
RooSuperCategory* ToyCat::v_ddcat;
RooArgSet*        ToyCat::v_cat_argset;

using namespace std;

void ToyCat::InitCat(void){
  cout << "Categories definition...";
  stringstream out;
  v_bbin = new RooCategory("binb","binb");
  v_dbin = new RooCategory("bind","bind");
  for(int i=-8; i<=8; i++){
    if(i != 0){
      out.str(""); out << "binb" << BinInd(i);
//      if(abs(i) == 7) v_bbin->defineType(out.str().c_str(),i);
      v_bbin->defineType(out.str().c_str(),i);
      out.str(""); out << "bind" << BinInd(i);
      v_dbin->defineType(out.str().c_str(),i);
    } else{
      v_bbin->defineType("binbz",i);
      v_dbin->defineType("bindz",i);
    }
  }
  v_cp  = new RooCategory("cp","cp");
  v_cp->defineType("CPp", 1);
  v_cp->defineType("CPm",-1);
  v_cp->defineType("CP0", 0);
  v_flv = new RooCategory("flv","flv");
  v_flv->defineType("B0",  1);
  v_flv->defineType("B0B",-1);
  v_flv->defineType("cpstate",  0);
  v_cat_argset = new RooArgSet(*v_bbin,*v_dbin,*v_cp,*v_flv);
  v_cat   = new RooSuperCategory("cat","cat",*v_cat_argset);
  v_cpcat = new RooSuperCategory("cpcat","cpcat",RooArgSet(*v_bbin,*v_cp,  *v_flv));
  v_ddcat = new RooSuperCategory("ddcat","ddcat",RooArgSet(*v_bbin,*v_dbin,*v_flv));
  cout << " done." << endl;
}

int ToyCat::BinInd(const int bin){
  return bin>0 ? bin+7 : bin+8;
}

int ToyCat::Bin(const int ind){
  return ind>7 ? ind-7 : ind-8;
}

int ToyCat::FlvInd(const int flv){
  return flv>0 ? 1 : 0;
}

int ToyCat::Flv(const int ind){
  return ind == 0 ? -1 : 1;
}

int ToyCat::CPInd(const int cp){
  return cp>0 ? 1 : 0;
}

int ToyCat::CP(const int ind){
  return ind == 0 ? -1 : 1;
}

