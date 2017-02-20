/** Copyright 2017 Vitaly Vorobyev
 ** @file dpevt.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_DPEVT_H_
#define SRC_DPEVT_H_

#include <vector>

#include "mylibs/libTEvt/tevt.h"

///
/// \brief The DPEvt class.
///
class DPEvt : public TEvt {
 public:
    explicit DPEvt(const bool iniflag = true);
    DPEvt(TTree* tree, const int ioflag);
    DPEvt(TTree* itree, TTree* otree);

    double mp(void) const;
    double mm(void) const;
    int flv(void) const;

    void Set_mp(const double& x);
    void Set_mm(const double& x);
    void Set_flv(const int& x);

 private:
    void init(void);

    std::vector<int> m_ind;
    int mp_ind(void) const {return m_ind[0];}
    int mm_ind(void) const {return m_ind[1];}
    int flv_ind(void) const {return m_ind[2];}
};

#endif  // SRC_DPEVT_H_

