/** Copyright 2017 Vitaly Vorobyev
 ** @file asymtotictools.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_ASYMTOTICTOOLS_H_
#define SRC_ASYMTOTICTOOLS_H_

#include <vector>

#include "mylibs/libDalitz/smalldpbin.h"
#include "mylibs/libDalitz/symdalitzmodel.h"

#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

class AsymtoticTools {
 public:
    AsymtoticTools(SymDalitzModel* model, const int gsize = 1000,
                   const int phsize = 100);

    int Fill(void);

    void GetHist(TH1I* h) const;
    void GetMap(TH2D* h) const;
    void GetWeights(TH2D* h) const;

    TTree* GetTree(void) const;
    TH1I* GetHist(void) const;
    TH2D* GetMap(void) const;
    TH2D* GetWeights(void) const;

 private:
    SmallDPBin* m_dpbin;
    SymDalitzModel* m_model;

    TH1I* m_h1d;
    TH2D* m_h2ph;
    TH2D* m_h2wg;
    TTree* m_tree;
    double m_norm;
    int m_phsize;
    double x, y;
    std::vector<double> m_N0;
    std::vector<double> m_N1;
};

#endif  // SRC_ASYMTOTICTOOLS_H_
