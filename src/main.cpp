#include "../libDalitz/libdalitz.h"
#include "../libDalitz/symdalitzmodel.h"
#include "../libDalitz/modelintegral.h"

#include "drawbdparams.h"

using namespace std;

void DrawBins(SymDalitzModel& model,const string& label){
  ModelIntegral integrator(&model);
  integrator.SetGridSize(1000);
  DrawBDParams drawpar;
  vector<double> C,S,K,Kb;
  integrator.Calculate(label,C,S,K,Kb);
  const string fname = label + string("_binning.txt");
  const string dpname = label + string("_binning");
  drawpar.DrawBinsmABmAC(fname,dpname);
  drawpar.DrawBinsmABmBC(fname,dpname);
  return;
}

void DrawKspipiBins(void){
  KspipiModel model;
  const string label("kspipi");
  DrawBins(model,label);
  return;
}

void DrawB0toD0pipiBins(void){
  B0toD0pipiModel model;
  const string label("d0pipi");
  DrawBins(model,label);
  return;
}

int main(int argc, char** argv){
//  const string csname("kspipi_cs_model");
//  drawpar.DrawCS(C,S,csname);
//  const string kname("kspipi_k_model");
//  drawpar.DrawK(K,Kb,kname);

  DrawB0toD0pipiBins();
  DrawKspipiBins();
  return 0;
}
