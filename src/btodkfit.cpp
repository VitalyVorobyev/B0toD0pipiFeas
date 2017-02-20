/** Copyright 2017 Vitaly Vorobyev
 ** @file btodkfit.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/btodkfit.h"

typedef UBinFCN<BtoDK_DtoKspipi_Model, DPEvt> gfcn;
typedef UBinGammaFit<gfcn> gfit;
typedef std::string str;

BtoDKfit::BtoDKfit(const str& tname, const std::vector<str>& flist) {
    m_tree = new TChain(tname.c_str());
    for (unsigned i = 0; i < flist.size(); i++) m_tree->Add(flist[i].c_str());

    m_model = new BtoDK_DtoKspipi_Model();
    m_evt = new DPEvt(m_tree, TEvt::In);
    m_fcn = new gfcn(m_model, m_evt);
    m_fit = new gfit(m_fcn);
}

const ROOT::Minuit2::MnUserParameterState& BtoDKfit::Fit(void) {
    m_fit->Fit();
    return m_fit->PState();
}
