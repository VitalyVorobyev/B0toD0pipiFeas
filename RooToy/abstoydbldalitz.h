#ifndef ABSTOYDBLDALITZ_H
#define ABSTOYDBLDALITZ_H

#include "toyresmodel.h"
#include "toyvars.h"
#include "dlzbinstruct.h"

class AbsToyDblDalitz{
public:
  AbsToyDblDalitz(void);

  void Init(void);

  void Set_tau(const double& x);
  void Set_dm(const double& x);
  void Set_wrtag(const double& x);

  double GetFractionKspipi(const int bin, const int flv) const;
  double GetFractionD0pipi(const int bin, const int flv) const;
  double GetFractionDblDlz(const int binb, const int bind, const int flv);

  const DlzBinStruct* DPars(void) const { return m_ddlz;}
  const DlzBinStruct* BPars(void) const { return m_bdlz;}

private:
  DlzBinStruct* m_ddlz;
  DlzBinStruct* m_bdlz;

  double m_tau;
  double m_dm;
  double m_wrtag;

  double m_xi, m_delut;

  void CalcKKKK(const int binb, const int bind);
  void CalcXiDelut(void);

  double m_kkpkk, m_kkmkk;
};

#endif // ABSTOYDBLDALITZ_H

