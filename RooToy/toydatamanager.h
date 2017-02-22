#ifndef TOYDATAMANAGER_H
#define TOYDATAMANAGER_H

#include <string>
#include "RooDataSet.h"
#include "RooRealVar.h"

class ToyDataManager{
public:
  ToyDataManager(void);
  RooDataSet* GetFlvDS(const int ind);
  RooDataSet* GetCPDS(const int ind);
  RooDataSet* GetDblDlzDS(const int ind);
private:
  RooDataSet* GetDS(const int ind,const std::string& type);
  std::string prefix;
};

#endif // TOYDATAMANAGER_H

