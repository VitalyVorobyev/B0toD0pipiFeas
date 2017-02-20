/** Copyright 2017 Vitaly Vorobyev
 ** @file drawresonances.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_DRAWRESONANCES_H_
#define SRC_DRAWRESONANCES_H_

#include <vector>
#include <string>

#include "mylibs/libDalitz/dalitzmodel.h"

class DrawResonances : public DalitzPhaseSpace {
 public:
    DrawResonances(const double& mmo, const double& mcha,
                   const double& mchb, const double& mchc);
    explicit DrawResonances(DalitzModel* model);
    void Draw(void);
    void Draw(const int i);

 private:
    std::vector<std::string> names;
    std::vector<std::string> labels;
    std::string prefix;
    std::string exten;
    std::string treename;

    std::string abaxis;
    std::string acaxis;
    std::string bcaxis;

    double sum_mass_sq;
};

#endif  // SRC_DRAWRESONANCES_H_
