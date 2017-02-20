/** Copyright 2017 Vitaly Vorobyev
 ** @file drawresonances.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/drawresonances.h"

#include <cstdlib>
#include <iostream>

#include "TChain.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TROOT.h"
#include "TPad.h"

typedef std::string str;

using std::to_string;
using std::cout;
using std::endl;

DrawResonances::DrawResonances(const double &mmo, const double &mcha,
                               const double &mchb, const double &mchc) :
    DalitzPhaseSpace(mmo, mcha, mchb, mchc),
    prefix("/home/vitaly/B0toD0pipi/B0toD0pipiFeas/DPTree_d0pipi"),
    exten(".root"),
    treename("tree"),
    sum_mass_sq(mmo * mmo + mcha * mcha + mchb * mchb + mchc * mchc) {
    names = {"_d2", "_d0", "_dv1", "_dJ", "_rho770", "_rho1450",
             "_rho1700", "_f2", "_f0bugg", "_f0flatte", "_f02020",
             "_nr", "_rho770_dv1", ""};
    labels = {"D*2(2460)", "D*0(2400)", "Dv*(2010)", "D*J(2760)",
              "rho(770)", "rho(1450)", "rho(1700)", "f2(1270)",
              "f0(500)", "f0(980)", "f0(2020)", "NR", "rho(770) + Dv*(2010)",
              "B^{0}#rightarrowD^{0}#pi^{+}#pi^{-} Dalitz plot"};
}

DrawResonances::DrawResonances(DalitzModel* model) :
    DrawResonances(model->mM(), model->mA(), model->mB(), model->mC()) {
    abaxis = model->ABaxis();
    acaxis = model->ACaxis();
    bcaxis = model->BCaxis();
}

void DrawResonances::Draw(void) {
    for (unsigned i = 0; i < names.size(); i++) Draw(i);
}

void DrawResonances::Draw(const int i) {
    const str fname = prefix + names[i] + exten;
    TChain* tree = new TChain(treename.c_str());
    tree->Add(fname.c_str());

    const str cname = "c" + names[i];
    TCanvas* c1 = new TCanvas(cname.c_str(), cname.c_str(), 800, 400);
    c1->Draw();
    TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.0, 0.5, 0.99);
    TPad* pad2 = new TPad("pad2", "pad2", 0.5, 0.0, 0.99, 0.99);
    pad1->Draw();
    pad2->Draw();
    pad1->cd();
    tree->Draw("mm:mp");
    TH2F *histo1 = reinterpret_cast<TH2F*>(gROOT->FindObject("htemp"));
    histo1->SetName("histo1");
    histo1->SetTitle(("m_{AC}^{2}:m_{AC}^{2} for " + labels[i]).c_str());
    histo1->GetXaxis()->SetRangeUser(mACsq_min(), mACsq_max());
    histo1->GetYaxis()->SetRangeUser(mABsq_min(), mABsq_max());
    histo1->GetXaxis()->SetTitle(acaxis.c_str());
    histo1->GetYaxis()->SetTitle(abaxis.c_str());
    histo1->GetXaxis()->SetLabelSize(0.05);
    histo1->GetYaxis()->SetLabelSize(0.05);
    histo1->GetXaxis()->SetTitleSize(0.05);
    histo1->GetYaxis()->SetTitleSize(0.05);
    histo1->GetXaxis()->SetTitleOffset(0.85);
    histo1->GetYaxis()->SetTitleOffset(0.85);
    gPad->Update();

    pad2->cd();
    tree->Draw((to_string(sum_mass_sq) + "-mm-mp:mp").c_str());
    TH2F *histo2 = reinterpret_cast<TH2F*>(gROOT->FindObject("htemp"));
    histo2->SetName("histo2");
    histo2->SetTitle(("m_{AC}^{2}:m_{BC}^{2} for " + labels[i]).c_str());
    histo2->GetXaxis()->SetRangeUser(mACsq_min(), mACsq_max());
    histo2->GetYaxis()->SetRangeUser(mBCsq_min(), mBCsq_max());
    histo2->GetXaxis()->SetTitle(acaxis.c_str());
    histo2->GetYaxis()->SetTitle(bcaxis.c_str());
    histo2->GetXaxis()->SetLabelSize(0.05);
    histo2->GetYaxis()->SetLabelSize(0.05);
    histo2->GetXaxis()->SetTitleSize(0.05);
    histo2->GetYaxis()->SetTitleSize(0.05);
    histo2->GetXaxis()->SetTitleOffset(0.85);
    histo2->GetYaxis()->SetTitleOffset(0.85);
    gPad->Update();

    const str epsname = "pics/DP" + names[i] + ".eps";
    c1->Print(epsname.c_str());
    if (!system(("evince " + epsname + " &").c_str()))
        cout << "File saving failed" << endl;
}
