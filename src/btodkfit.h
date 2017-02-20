/** Copyright 2017 Vitaly Vorobyev
 ** @file btodkfit.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_BTODKFIT_H_
#define SRC_BTODKFIT_H_

#include <string>
#include <vector>

#include "TChain.h"
#include "Minuit2/MnUserParameterState.h"

#include "mylibs/libDalitzFit/ubinfcn.h"
#include "mylibs/libDalitzFit/ubingammafit.h"
#include "mylibs/libDalitz/btodk_dtokspipi_model.h"

#include "./dpevt.h"

///
/// \brief The BtoDKfit class. Unbinned fit of the angle gamma in
/// B- -> D0 K-, D0 -> Ks0 pi+ pi- decays
///
class BtoDKfit {
 public:
    BtoDKfit(const std::string& tname, const std::vector<std::string>& flist);
    const ROOT::Minuit2::MnUserParameterState& Fit(void);

 private:
    BtoDK_DtoKspipi_Model* m_model;
    UBinFCN<BtoDK_DtoKspipi_Model, DPEvt>* m_fcn;
    UBinGammaFit<UBinFCN<BtoDK_DtoKspipi_Model, DPEvt>>* m_fit;
    TChain* m_tree;
    DPEvt* m_evt;
};

#endif  // SRC_BTODKFIT_H_
