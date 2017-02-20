/** Copyright 2017 Vitaly Vorobyev
 ** @file dlzbinstruct.h
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#ifndef SRC_DLZBINSTRUCT_H_
#define SRC_DLZBINSTRUCT_H_

#include <vector>
#include <string>

/**
 * @brief The DlzBinStruct class. Class for keeping binned
 *  Dalitz plot parameters
 */
class DlzBinStruct {
 public:
    explicit DlzBinStruct(const unsigned nbins);
    explicit DlzBinStruct(const std::string& fname);

    void SetKp(const int bin, const double& v);
    void SetKn(const int bin, const double& v);
    void SetC(const int bin, const double& v);
    void SetS(const int bin, const double& v);

    double Kp(const int bin) const;
    double Kn(const int bin) const;
    double C(const int bin)  const;
    double S(const int bin)  const;

    int GetParams(const std::string& fname);
    void Clear(void);

 private:
    bool CheckBinNumber(const unsigned bin) const;
    unsigned m_nbins;
    std::vector<double> m_C;
    std::vector<double> m_S;
    std::vector<double> m_Kp;
    std::vector<double> m_Kn;
};

#endif  // SRC_DLZBINSTRUCT_H_
