/** Copyright 2017 Vitaly Vorobyev
 ** @file main.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include <fstream>
#include <string>

#include "TFile.h"

#include "mylibs/libDalitz/kspipimodel.h"
#include "mylibs/libDalitz/dalitzmcintegral.h"

#include "./toytools.h"
#include "./asymtotictools.h"

typedef std::string str;
typedef std::vector<double> vectd;
// typedef std::vector<int>    vecti;

bool m_model = false;
bool m_gen   = false;
bool m_fit   = false;
bool m_sim   = false;
bool m_notag = false;
bool m_flv   = false;
bool m_cp    = false;
bool m_dd    = false;

int parse_input(int argc, char** argv) {
    str param;
    for (int i = 0; i < argc; i++) {
        param = str(argv[i]);
        if (param == "model") {
            m_model = true;
            continue;
        }
        if (param == "gen") {
            m_gen = true;
            continue;
        }
        if (param == "fit") {
            m_fit = true;
            continue;
        }
        if (param == "dd") {
            m_dd = true;
            continue;
        }
        if (param == "cp") {
            m_cp = true;
            continue;
        }
        if (param == "notag") {
            m_notag = true;
            continue;
        }
        if (param == "flv") {
            m_flv = true;
            continue;
        }
        if (param == "sim") {
            m_sim = true;
            continue;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
//  ToyTools::DrawKspipiBins();
    ToyTools::DrawKuzBins();
////    return 0;
    const str klabel("kuz_bdpp_broken");
    vectd mABsqv;
    vectd mACsqv;
    const int NEve = 10000;
    ToyTools::GenerateKuzminPlot(NEve, &mABsqv, &mACsqv);
    ToyTools::SaveDPTree(klabel, mABsqv, mACsqv);
    ToyTools::GetAKuzBr();

  //  ToyTools::GammaUBFit();
//  return 0;
//  KspipiModel model;
//  AsymtoticTools astools(&model);
//  astools.Fill();

//  TFile* ofile = new TFile("asbins.root","RECREATE");
//  TH1I* h1 = astools.GetHist();
//  TH2D* h2 = astools.GetMap();
//  TH2D* h3 = astools.GetWeights();
//  TTree* t = astools.GetTree();
////  astools.GetHist(h1);
////  astools.GetMap(h2);
////  astools.GetWeights(h3);
//  h1->Print();

//  h1->Write();
//  h2->Write();
//  h3->Write();
//  t->Write();

//  ofile->Close();

//  ToyTools::InitTools();
//  if(parse_input(argc,argv)) return -1;
//  if(m_model){
//    B0toD0pipiModel model(B0toD0pipiModelType::Belle);
//    DalitzMCIntegral mcint(model);
//    vector<double> vals;
//    vector<double> errs;
//    mcint.CalcBranchings(vals,errs);

//    const str label("d0pipi");
//    // Calculate binned parameters and show the result
//    ToyTools::DrawBins(model,label);

//    const str label("bdk");
//    vectd mABsqv;
//    vectd mACsqv;
//    vecti flvv;
//    const int NEve = 10000;
//    ToyTools::Generate_BDK_DKspipiDP(NEve,mABsqv,mACsqv,flvv);
//////    ToyTools::GenerateDalitzPlot(model,NEve,mABsqv,mACsqv);
//    ToyTools::SaveDPTree(label,mABsqv,mACsqv,flvv);
//////    ToyTools::GenerateEachResonance(model,10000);


//    cout << "A(0.77,1.50) = " << abs(model.Amp(0.77,1.50)) << endl;
//    cout << "A(1.50,0.77) = " << abs(model.Amp(1.50,0.77)) << endl;
//    DalitzMCIntegral mcint(model);
//    vector<double> vals;
//    vector<double> errs;
//    mcint.CalcBranchings(vals,errs);

//    const str label("kspp");
//    ToyTools::DrawKspipiBins();
//    vector<double> mABsqv;
//    vector<double> mACsqv;
//    ToyTools::GenerateKspipiDP(10000,mABsqv,mACsqv);
//    ToyTools::SaveDPTree(label,mABsqv,mACsqv);

//    const str label("kspp");
    // Calculate binned parameters and show the result
//    ToyTools::DrawBins(model,label);

//    B0toD0pipiModel model(B0toD0pipiModelType::Belle);
//    const str label("bdk2");
//    vectd mABsqv;
//    vectd mACsqv;
//    const int NEve = 10000;
//    ToyTools::GenerateDalitzPlot(model,NEve,mABsqv,mACsqv);
//    ToyTools::SaveDPTree(label,mABsqv,mACsqv);
//    ToyTools::GenerateEachResonance(model,10000);

    return 0;
//  }

//  ToyResModel::InitResolution()
//  if(m_gen){
//    ToyDblDalitzGen gen;

//    if(m_flv || m_notag){
//      RooDataSet* dsflv = gen.GenerateFlv(100000);
//      dsflv->Print();
//      ToyTools::SaveFlvGenTree("",dsflv);
//    }

//    if(m_cp || m_sim){
//      RooDataSet* dscp = gen.GenerateCP(50000,50000);
//      dscp->Print();
//      ToyTools::SaveCPGenTree("",dscp);
//    }

//    if(m_dd || m_sim){
//      RooDataSet* dsdbldlz = gen.GenerateDblDlz(100000);
//      dsdbldlz->Print();
//      ToyTools::SaveDblDlzGenTree("",dsdbldlz);
//    }
//  }

//  if(m_fit){
//    if(m_notag) ToyTools::LifetimeFit();
//    if(m_flv)   ToyTools::FlvFit();
//    if(m_cp)    ToyTools::CPFit(false);
//    if(m_dd)    ToyTools::DblDlzFit(true);
//    if(m_sim)   ToyTools::SimFit(true);
//  }
//  B0toD0pipiModel model;
//  DrawResonances artist(&model);
//  artist.Draw();

// return 0;
}
