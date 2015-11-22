#include "../libDalitz/src/libdalitz.h"
#include "../libDalitz/src/kspipimodel.h"
#include "../libDalitz/src/dalitzmcintegral.h"

#include "drawbdparams.h"

#include <fstream>

#include "TTree.h"
#include "TFile.h"

//#include "dalitzmodel.h"

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
  const string label("kspipi_new");
//  const string label("kspipi_kstar_rho");
  DrawBins(model,label);
  return;
}

void DrawB0toD0pipiBins(void){
  B0toD0pipiModel model;
  const string label("d0pipi_D2_rho");
  DrawBins(model,label);
  return;
}

void GenerateDalitzPlot(const DalitzModel& model, const int NEvents,vector<double>& mABsqv,vector<double>& mACsqv){
  DalitzGenerator* generator = new DalitzGenerator(model);
  generator->Generate(NEvents,mABsqv,mACsqv);
  return;
}

void GenerateKspipiDP(const int NEvents,vector<double>& mABsqv,vector<double>& mACsqv){
  KspipiModel model;
  GenerateDalitzPlot(model,NEvents,mABsqv,mACsqv);
  return;
}

void SaveDPTree(const string& label,const vector<double>& mABsqv,const vector<double>& mACsqv){
  stringstream out;
  out.str(""); out << "DPTree_" << label << ".root";
  TFile* file = new TFile(out.str().c_str(),"RECREATE");
  TTree* tree = new TTree("tree","tree");
  double mABsq, mACsq;
  tree->Branch("mp",&mABsq,"mp/d");
  tree->Branch("mm",&mACsq,"mm/d");
  for(int i=0; i<(int)mABsqv.size(); i++){
    mABsq = mABsqv[i]; mACsq = mACsqv[i];
    tree->Fill();
  }
  tree->Write();
  file->Close();
  return;
}

int main(int argc, char** argv){
//  DalitzPhaseSpace phsp(m_D0_Mass,0.497614,0.13957018,0.13957018);

//  KspipiModel model1;
//  DalitzModel1 model2;

//  double mp,mm;
//  for(int i=0; i<1e6; i++){
//    rndm_point.GetPoint(mp,mm);
//    model1.Amp(mp,mm);
//  }

//  B0toD0pipiModel model;
//  RandomDalitzPoint rndm_point(model);
//  rndm_point.GetPoint(mp,mm);

//  const EvtComplex amp1 = model.Amp(mp,mm);
//  const EvtComplex amp2 = model2.Amp(mp,mm);
//  cout << mp << " " << mm << ":" << endl;
//  cout << "  " << real(amp1) << " " << imag(amp1) << endl;
//  cout << "  " << real(amp2) << " " << imag(amp2) << endl;

//  KspipiModel model;
  B0toD0pipiModel model;
  DalitzMCIntegral mcint(model);
//  double val,err;
//  mcint.CalcIntegral(val,err);
  vector<double> vals;
  vector<double> errs;
  mcint.CalcBranchings(vals,errs);

  const string label("d0pipi");
  DrawBins(model,label);
//  const string csname("kspipi_cs_model");
//  drawpar.DrawCS(C,S,csname);
//  const string kname("kspipi_k_model");
//  drawpar.DrawK(K,Kb,kname);

//  DrawB0toD0pipiBins();
//  DrawKspipiBins();

  vector<double> mABsqv;
  vector<double> mACsqv;
  const int NEve = 10000;

//  GenerateKspipiDP(NEve,mABsqv,mACsqv);
  GenerateDalitzPlot(model,NEve,mABsqv,mACsqv);
  SaveDPTree(label,mABsqv,mACsqv);

//  ofstream ofile("out.txt",ofstream::out);
//  for(int i=0; i<(int)mABsqv.size(); i++){
//    ofile << mABsqv[i]  << " " << mACsqv[i] << endl;
//  }
//  ofile.close();

  return 0;
}
