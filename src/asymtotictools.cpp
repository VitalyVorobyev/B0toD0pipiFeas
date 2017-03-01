/** Copyright 2017 Vitaly Vorobyev
 ** @file asymtotictools.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/asymtotictools.h"

#include <iostream>
#include <cmath>

typedef std::vector<double> vectd;

using std::cout;
using std::endl;

AsymtoticTools::AsymtoticTools(AbsSymDalitzModel* model,
                               const int gsize, const int phsize) :
    m_dpbin(new SmallDPBin(model)),
    m_model(model),
    m_norm(1),
    m_phsize(phsize) {
    m_dpbin->SetGridSize(gsize);
    m_h1d = new TH1I("h1", "h1", phsize, -M_PI, M_PI);
    const double mmin = model->mABsq_min();
    const double mmax = model->mABsq_max();
    m_h2ph = new TH2D("hph", "hph", gsize, mmin, mmax, gsize, mmin, mmax);
    m_h2wg = new TH2D("hwg", "hwg", gsize, mmin, mmax, gsize, mmin, mmax);
    m_tree = new TTree("tree", "tree");
}

TTree* AsymtoticTools::GetTree(void) const {
    return reinterpret_cast<TTree*>(m_tree->Clone());
}

int AsymtoticTools::Fill(void) {
    const unsigned nbins = m_model->nbins();
    vectd Kp; Kp.resize(nbins, 0);
    vectd Km; Km.resize(nbins, 0);
    vectd sqKK; sqKK.resize(nbins, 0);

    double mp, mm;
    double deld;
    double P;
    double Pb;
    double wght;
    int dpbin;

    m_tree->Branch("mp", &mp, "mp/D");
    m_tree->Branch("mm", &mm, "mm/D");
    m_tree->Branch("deld", &deld, "deld/D");
    m_tree->Branch("p", &P, "p/D");
    m_tree->Branch("pb", &Pb, "pb/D");
    m_tree->Branch("wght", &wght, "wght/D");
    m_tree->Branch("dpbin", &dpbin, "dpbin/I");

    int ncounts = 0;
    double norm = 0;
    const unsigned gsize = m_dpbin->GSize();
    for (unsigned i = 0; i < gsize; i++) {
        for (unsigned j = 0; j < i; j++) {
            m_dpbin->SetBin(i, j);
            m_dpbin->GetCurrentPoint(&mp, &mm); ncounts++;
            deld = m_dpbin->Phase();
            P = m_dpbin->P();  // /Norm;
            Pb = m_dpbin->Pb();  // /Norm;
            wght = m_dpbin->Weight();
            dpbin = std::abs(m_model->bin(mp, mm));
            m_tree->Fill();

            Kp[dpbin-1] += P;
            Km[dpbin-1] += Pb;
            sqKK[dpbin-1] += std::sqrt(P*Pb);
            norm += P + Pb;

            cout << i << " " << j << " " << deld << " " << wght << endl;
            m_h1d->Fill(deld, wght);
            const int bin = m_h2ph->GetBin(i+1, j+1);
            m_h2ph->SetBinContent(bin, deld);
            m_h2wg->SetBinContent(bin, wght);
            const int binb = m_h2ph->GetBin(j+1, i+1);
            m_h2ph->SetBinContent(binb, -deld);
            m_h2wg->SetBinContent(binb, wght);
        }
    }
    m_h1d->Print();
    m_h2ph->Print();
    m_h2wg->Print();

    cout << "Dalitz plot scanning complete. Norm = " << norm << endl;
    for (unsigned i = 0; i < nbins; i++) {
        Kp[i] /= norm; Km[i] /= norm; sqKK[i] /= norm;
        cout << "bin " << i+1 << ": ";
        cout << "K+ = " << Kp[i] << ", ";
        cout << "K- = " << Km[i] << ", ";
        cout << "SummKK = " << sqKK[i] << ", ";
        cout << "sqrtKK = " << std::sqrt(Kp[i] * Km[i]) << endl;
    }
    return ncounts;
}

void AsymtoticTools::GetHist(TH1I* h) const {
    h = reinterpret_cast<TH1I*>(m_h1d->Clone());
}

void AsymtoticTools::GetMap(TH2D* h) const {
    h = reinterpret_cast<TH2D*>(m_h2ph->Clone());
}

void AsymtoticTools::GetWeights(TH2D* h) const {
    h = reinterpret_cast<TH2D*>(m_h2wg->Clone());
}

TH1I* AsymtoticTools::GetHist(void) const {
    return reinterpret_cast<TH1I*>(m_h1d->Clone());
}

TH2D* AsymtoticTools::GetMap(void) const {
    return reinterpret_cast<TH2D*>(m_h2ph->Clone());
}

TH2D* AsymtoticTools::GetWeights(void) const {
    return reinterpret_cast<TH2D*>(m_h2wg->Clone());
}
