/** Copyright 2017 Vitaly Vorobyev
 ** @file toytools.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_TOYTOOLS_H_
#define SRC_TOYTOOLS_H_

#include <string>
#include <vector>
#include <cstdint>

#include "mylibs/libDalitz/dalitzmodel.h"

/**
 * @brief The ToyTools class. Various tools to study tree-body decays models
 */
class ToyTools {
 public:
    ToyTools() {}
    static void InitTools(void);

    static void DrawBins(AbsDalitzModel* model, const std::string& label);
    static void DrawKspipiBins(void);
    static void DrawB0toD0pipiBins(void);
    static void DrawKuzBins(void);

    static void GenerateKuzminPlot(const uint64_t NEvents,
                                   std::vector<double>* mABsqv,
                                   std::vector<double>* mACsqv);
    static void GenerateDalitzPlot(const AbsDalitzModel& model,
                                   const uint64_t NEvents,
                                   std::vector<double>* mABsqv,
                                   std::vector<double>* mACsqv);
    static void GenerateKspipiDP(const uint64_t NEvents,
                                 std::vector<double>* mABsqv,
                                 std::vector<double>* mACsqv);
    static void Generate_BDK_DKspipiDP(const uint64_t NEvents,
                                       std::vector<double>* mABsqv,
                                       std::vector<double>* mACsqv,
                                       std::vector<int> *flvv);
    static void GenerateEachResonance(DalitzModel* model,
                                      const uint64_t NEvents);

    static void GetAKuzBr(void);

    static void SaveDPTree(const std::string& label,
                           const std::vector<double>& mABsqv,
                           const std::vector<double>& mACsqv);
    static void SaveDPTree(const std::string& label,
                           const std::vector<double>& mABsqv,
                           const std::vector<double>& mACsqv,
                           const std::vector<int> &flvv);
    static void addVector(std::vector<double>* v1,
                          const std::vector<double>& v2);
    static void GammaUBFit(void);

    /// untagged lifetime fit
//    static void LifetimeFit(void);
    /// tagget lifetime or/and dm fit
//    static void FlvFit(void);
    /// tagget CPV fit with D decays into CP eigenstates
//    static void CPFit(const bool cpvfit);
    /// fit of double Dalitz distribution
//    static void DblDlzFit(const bool cpvfit);
    ///
//    static void SimFit(const bool fixphases);

//    static void DblDlzToyGenAndFit(void);
};

#endif  // SRC_TOYTOOLS_H_
