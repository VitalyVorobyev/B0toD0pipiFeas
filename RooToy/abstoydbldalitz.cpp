#include "abstoydbldalitz.h"
#include "toyvars.h"

#include <string>
#include <fstream>

using namespace std;

AbsToyDblDalitz::AbsToyDblDalitz(void):
  m_tau(1.520), m_dm(0.505), m_wrtag(0.3)
{
  Init();
}

void AbsToyDblDalitz::Init(void){
  m_ddlz  = new DlzBinStruct("params/d0pipi_eq_phase_params.txt");
  m_bdlz  = new DlzBinStruct("params/kspipi_eq_phase_params.txt");
  m_tau   = ToyVars::Get_tau()->getVal();
  m_dm    = ToyVars::Get_dm()->getVal();
  m_wrtag = ToyVars::Get_wrtag()->getVal();
  CalcXiDelut();
}

void AbsToyDblDalitz::CalcKKKK(const int binb, const int bind){
  m_kkpkk = m_ddlz->Kp(bind)*m_bdlz->Kp(binb) + m_ddlz->Kn(bind)*m_bdlz->Kn(binb);
  m_kkmkk = m_ddlz->Kp(bind)*m_bdlz->Kp(binb) - m_ddlz->Kn(bind)*m_bdlz->Kn(binb);
}

void AbsToyDblDalitz::CalcXiDelut(void){
  m_xi    = 1+m_tau*m_dm*m_tau*m_dm;
  m_delut = 1.-2.*m_wrtag;
}

void AbsToyDblDalitz::Set_tau(const double& x){
  m_tau = x;
  ToyVars::Set_tau(m_tau);
  CalcXiDelut();
}

void AbsToyDblDalitz::Set_dm(const double& x){
  m_dm = x;
  ToyVars::Set_tau(m_dm);
  CalcXiDelut();
}

void AbsToyDblDalitz::Set_wrtag(const double& x){
  m_wrtag = x;
  ToyVars::Set_tau(m_wrtag);
  CalcXiDelut();
}

double AbsToyDblDalitz::GetFractionD0pipi(const int bin, const int flv) const{
  return 0.5*((m_bdlz->Kp(bin)+m_bdlz->Kn(bin))*m_xi + m_delut*flv*(m_bdlz->Kp(bin)-m_bdlz->Kn(bin)))/m_xi;
}

double AbsToyDblDalitz::GetFractionKspipi(const int bin, const int flv) const{
  return 0.5*((m_ddlz->Kp(bin)+m_ddlz->Kn(bin))*m_xi + m_delut*flv*(m_ddlz->Kp(bin)-m_ddlz->Kn(bin)))/m_xi;
}

double AbsToyDblDalitz::GetFractionDblDlz(const int binb, const int bind, const int flv){
  CalcKKKK(binb,bind);
  return 0.5*(m_kkpkk+flv/m_xi*m_kkmkk);
}

