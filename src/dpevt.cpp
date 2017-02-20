/** Copyright 2017 Vitaly Vorobyev
 ** @file dpevt.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/dpevt.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;

typedef std::string str;

DPEvt::DPEvt(const bool iniflag) : TEvt() {
    AddFormat("/home/vitaly/B0toD0pipi/B0toD0pipiFeas/params/dpevt.txt");
    if (iniflag) {
        ReadStructure(Format());
        init();
    }
}

DPEvt::DPEvt(TTree* tree, const int ioflag): DPEvt(true) {
    SetTree(tree, ioflag);
}

DPEvt::DPEvt(TTree* itree, TTree* otree): DPEvt(true) {
    SetITree(itree);
    SetOTree(otree);
}

double DPEvt::mp(void) const {return DVar(mp_ind());}
double DPEvt::mm(void) const {return DVar(mm_ind());}
int    DPEvt::flv(void) const {return IVar(flv_ind());}

void DPEvt::Set_mp(const double& x) {SetDVar(mp_ind(), x);}
void DPEvt::Set_mm(const double& x) {SetDVar(mm_ind(), x);}
void DPEvt::Set_flv(const int& x)   {SetIVar(flv_ind(), x);}


void DPEvt::init(void) {
    cout << "DPEvt::init..." << endl;
    // The order of initialization is important!
//    m_ind.push_back(FindIndex(m_DVars, str("mp")));//0
//    m_ind.push_back(FindIndex(m_DVars, str("mm")));//1
//    m_ind.push_back(FindIndex(m_IVars, str("flv")));//2
    cout << "DPEvt::init... " << m_ind.size() << endl;
}
