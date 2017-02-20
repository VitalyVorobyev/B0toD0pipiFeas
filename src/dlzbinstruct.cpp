/** Copyright 2017 Vitaly Vorobyev
 ** @file dlzbinstruct.cpp
 **
 ** @brief This message displayed in Doxygen Files index
 **
 ** @author Vitaly Vorobyev
 ** Contact: vit.vorobiev@gmail.com
 **
 **/

#include "../src/dlzbinstruct.h"

#include <fstream>
#include <iostream>

typedef std::string str;

using std::cout;
using std::endl;

DlzBinStruct::DlzBinStruct(const unsigned nbins) : m_nbins(nbins) {
    for (unsigned i=0; i < m_nbins; i++) {
        m_C.push_back(0); m_S.push_back(0);
        m_Kp.push_back(0); m_Kn.push_back(0);
    }
}

DlzBinStruct::DlzBinStruct(const str& fname) {
    m_nbins = GetParams(fname);
}

void DlzBinStruct::Clear(void) {
    m_C.clear(); m_S.clear(); m_Kp.clear(); m_Kn.clear();
    m_nbins = 0;
}

int DlzBinStruct::GetParams(const str& fname) {
    Clear();
    cout << "Getting parameters from " << fname << endl;
    std::ifstream ifile(fname.c_str(), std::ifstream::in);
    if (!ifile.is_open()) return -1;
    str line;
    int bin;
    double c, s, kp, kn, q;
    int flag = 6;
    while (flag == 6) {
        int i = m_S.size();
        getline(ifile, line);
        flag = sscanf(line.c_str(),
                      "%d: C = %lf, S = %lf, K = %lf, Kb = %lf, Q = %lf",
                      &bin, &c, &s, &kp, &kn, &q);
        if (i != (bin-1) || flag != 6) break;
        m_C.push_back(c); m_S.push_back(s);
        m_Kp.push_back(kp); m_Kn.push_back(kn);
        cout << i+1 << " C: " << m_C[i] << " S: " << m_S[i]
                   << " Kp: " << m_Kp[i] << " Kn: " << m_Kn[i] << endl;
    }
    cout << "Done!" << endl;
    return m_nbins = m_C.size();
}

bool DlzBinStruct::CheckBinNumber(const unsigned bin) const {
    if (bin > 0 && bin <= m_nbins) return true;
    else
        cout << "Wrong bin number detected: " << bin << endl;
    return false;
}

void DlzBinStruct::SetKp(const int bin, const double& v) {
    if (!CheckBinNumber(bin)) return;
    m_Kp[bin-1] = v;
}

void DlzBinStruct::SetKn(const int bin, const double& v) {
    if (!CheckBinNumber(bin)) return;
    m_Kn[bin-1] = v;
}

void DlzBinStruct::SetC(const int bin, const double& v) {
    if (!CheckBinNumber(bin)) return;
    m_C[bin-1] = v;
}

void DlzBinStruct::SetS(const int bin, const double& v) {
    if (!CheckBinNumber(bin)) return;
    m_S[bin-1] = v;
}

double DlzBinStruct::Kp(const int bin) const {
    if (!CheckBinNumber(std::abs(bin))) return 0;
    return bin > 0 ? m_Kp[bin-1] : m_Kn[-bin-1];
}

double DlzBinStruct::Kn(const int bin) const {
    if (!CheckBinNumber(std::abs(bin))) return 0;
    return bin > 0 ? m_Kn[bin-1] : m_Kp[-bin-1];
}

double DlzBinStruct::C(const int bin) const {
    if (!CheckBinNumber(std::abs(bin))) return 0;
    return m_C[abs(bin)-1];
}

double DlzBinStruct::S(const int bin) const {
    if (!CheckBinNumber(std::abs(bin))) return 0;
    return bin > 0 ? m_S[bin-1] : -m_S[-bin-1];
}
