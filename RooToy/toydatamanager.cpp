#include "toydatamanager.h"
#include "toycat.h"
#include "toyvars.h"

#include "TChain.h"

#include <string>
#include <sstream>

using namespace std;

ToyDataManager::ToyDataManager(void):
  prefix("/home/vitaly/B0toD0pipi/B0toD0pipiFeas/data/")
{
}

RooDataSet* ToyDataManager::GetFlvDS(const int ind){
  cout << "Getting flv ds..." << endl;
  return GetDS(ind,"Flv");
}

RooDataSet* ToyDataManager::GetCPDS(const int ind){
  cout << "Getting CP ds..." << endl;
  return GetDS(ind,"CP");
}

RooDataSet* ToyDataManager::GetDblDlzDS(const int ind){
  cout << "Getting DblDlz ds..." << endl;
  return GetDS(ind,"DblDlz");
}

RooDataSet* ToyDataManager::GetDS(const int ind,const string& type){
  stringstream out; out.str(""); if(ind>0) out << ind;
  const string fname = prefix + string("GenTree") + type + out.str() + string(".root");
  TChain tree("tree","tree");
  tree.Add(fname.c_str());
  RooArgSet aset(*ToyVars::Get_dt(),*ToyCat::GetASet());
  RooDataSet* ds = new RooDataSet("ds","ds",&tree,aset);
  return ds;
}

