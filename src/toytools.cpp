/** Copyright 2017 Vitaly Vorobyev
 ** @file toytools.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/toytools.h"

#include <fstream>

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TRandom3.h"

#include "mylibs/libDalitz/kspipimodel.h"
#include "mylibs/libDalitz/dalitzgenerator.h"
#include "mylibs/libDalitz/b0tod0pipimodel.h"
#include "mylibs/libDalitz/btodk_dtokspipi_model.h"
#include "mylibs/libDalitz/dalitzmcintegral.h"
#include "mylibs/libDalitz/kuzbtodpipiamp.h"
#include "mylibs/libDalitz/modelintegral.h"

#include "./drawbdparams.h"
#include "./drawresonances.h"
#include "./btodkfit.h"

typedef std::string str;
typedef std::vector<double> vectd;
typedef std::vector<int> vecti;
typedef std::vector<unsigned> vectu;
typedef KuzBtoDpipiAmp KAmp;

using std::to_string;
using std::ofstream;
using std::endl;

const str ToyTools::txt_data_path =
        "/home/vitaly/B0toD0pipi/B0toD0pipiFeas/data/txt/";

void ToyTools::DrawBins(AbsDalitzModel* model, const str& label) {
    ModelIntegral integrator(model);
    integrator.SetGridSize(1000);
    DrawBDParams drawpar;
    vectd C, S, K, Kb;
    integrator.Calculate(label, &C, &S, &K, &Kb);
    const str fname = label + "_binning.txt";
    const str dpname = label + "_binning";
    drawpar.DrawBinsmABmAC(fname, dpname);
    drawpar.DrawBinsmABmBC(fname, dpname);
    const str csname = label + "_CS";
    drawpar.DrawCS(C, S, csname);
    const str kkbname = label + "_K";
    drawpar.DrawK(K, Kb, kkbname);
}

void ToyTools::DrawKspipiBins(void) {
    KspipiModel model;
    const str label("kspipi");
    ToyTools::DrawBins(&model, label);
}

void ToyTools::DrawB0toD0pipiBins(void) {
    B0toD0pipiModel model;
    const str label("d0pipi_D2_rho");
    ToyTools::DrawBins(&model, label);
}

void ToyTools::DrawKuzBins(void) {
    KAmp model;
    const str label("d0pipi_kuz");
    ToyTools::DrawBins(&model, label);
}

void ToyTools::GenerateDalitzPlot(const AbsDalitzModel& model,
                                  const uint64_t NEvents,
                                  vectd* mABsqv, vectd* mACsqv) {
    DalitzGenerator generator(&model);
    generator.Generate(NEvents, mABsqv, mACsqv);
}

void ToyTools::GenerateKuzminPlot(const uint64_t NEvents,
                                  vectd* mABsqv, vectd* mACsqv) {
    KAmp model;
    DalitzGenerator generator(&model);
    generator.Generate(NEvents, mABsqv, mACsqv);
}

void ToyTools::TabulateAmpl(const AbsDalitzModel& model,
                         const str& label, const unsigned gsize) {
    const str fname = txt_data_path + "tbl_" + label + ".txt";
    model.Tabulate(fname, gsize);
}

void ToyTools::TabulateKuzmin(const str& label, const unsigned gsize) {
    KAmp model;
    TabulateAmpl(model, label, gsize);
}

void ToyTools::WriteKuzminPlot(const uint64_t NEvents, const str& label) {
    KAmp model;
    DalitzGenerator generator(&model);
    generator.WriteDDist(NEvents, txt_data_path + "ddist_" + label + ".txt");
}

void ToyTools::GetAKuzBr(void) {
    KAmp model;
    DalitzMCIntegral mcint(&model);
    vectd vals;
    vectd errs;
    mcint.CalcBranchings(&vals, &errs);
}

void ToyTools::GenerateKspipiDP(const uint64_t NEvents,
                                vectd* mABsqv, vectd* mACsqv) {
    KspipiModel model;
    ToyTools::GenerateDalitzPlot(model, NEvents, mABsqv, mACsqv);
}

void ToyTools::addVector(vectd* v1, const vectd& v2) {
    v1->insert(v1->end(), v2.begin(), v2.end());
}

void ToyTools::Generate_BDK_DKspipiDP(const uint64_t NEvents, vectd* mABsqv,
                                      vectd* mACsqv, vecti* flvv) {
    mABsqv->clear(); mACsqv->clear(); flvv->clear();
    BtoDK_DtoKspipi_Model model(70, 120, 0.1);
    DalitzGenerator generator(&model);
    TRandom3 rndm;
    rndm.SetSeed(0);
    int flv = 1;
    double mAB, mAC;
    for (uint64_t i = 0; i < NEvents; i++) {
        flv = rndm.Rndm()-0.5 > 0 ? 1 : -1;
        model.SetFlv(flv);
        generator.Generate(&mAB, &mAC);
        mABsqv->push_back(mAB);
        mACsqv->push_back(mAC);
        flvv->push_back(flv);
    }
}

void ToyTools::SaveDP(const str& label, const vectd& mABsqv,
                      const vectd& mACsqv) {
    ofstream file(txt_data_path + "ddist_" + label + ".txt", ofstream::out);
    for (auto itAB = mABsqv.begin(), itAC = mACsqv.begin();
         itAB != mABsqv.end() && itAC != mACsqv.end();
         itAB++, itAC++) {
        file << *itAB << " " << *itAC << endl;
    }
    file.close();
}

void ToyTools::SaveDPTree(const str& label, const vectd& mABsqv,
                          const vectd& mACsqv) {
    const str fname = "DPTree_" + label + ".root";
    TFile* file = new TFile(fname.c_str(), "RECREATE");
    TTree* tree = new TTree("tree", "tree");
    double mABsq, mACsq;
    tree->Branch("mp", &mABsq, "mp/d");
    tree->Branch("mm", &mACsq, "mm/d");
    for (unsigned i=0; i < mABsqv.size(); i++) {
        mABsq = mABsqv[i]; mACsq = mACsqv[i];
        tree->Fill();
    }
    tree->Write();
    file->Close();
}

void ToyTools::SaveDPTree(const str& label, const vectd& mABsqv,
                          const vectd& mACsqv, const vecti &flvv) {
    const str fname = "DPTree_" + label + ".root";
    TFile* file = new TFile(fname.c_str(), "RECREATE");
    TTree* tree = new TTree("tree", "tree");
    double mABsq, mACsq;
    int flv;
    tree->Branch("mp", &mABsq, "mp/D");
    tree->Branch("mm", &mACsq, "mm/D");
    tree->Branch("flv", &flv, "flv/I");
    for (unsigned i = 0; i < mABsqv.size(); i++) {
        mABsq = mABsqv[i]; mACsq = mACsqv[i]; flv = flvv[i];
        tree->Fill();
    }
    tree->Write();
    file->Close();
}

void ToyTools::GenerateEachResonance(DalitzModel* model,
                                     const uint64_t NEvents) {
    DalitzGenerator generator(model);
    const int NRes = model->ResNum();
    vectu subres;
    vectd mABsqv;
    vectd mACsqv;
    for (int i = 0; i < NRes; i++) {
        subres.clear(); subres.push_back(i);
        if (model->ResName(i) == "rho(770)") {  // rho and omega together
            i++; subres.push_back(i);
        }
        mABsqv.clear(); mACsqv.clear();
        model->SetRVec(subres);
        generator.Generate(NEvents, &mABsqv, &mACsqv);
        SaveDPTree("DPTree" + to_string(i), mABsqv, mACsqv);
    }
    subres.clear(); model->SetRVec(subres);
}
