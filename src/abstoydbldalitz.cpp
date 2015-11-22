#include "abstoydbldalitz.h"

#include <string>
#include <fstream>

AbsToyDblDalitz::AbsToyDblDalitz():
  m_dt_min(-70), m_dt_max(70), m_tau(1.534), m_dm(0.510), m_wrtag(0.3),
  m_res_mean(0.), m_res_sigma(0.8), m_cos2phi1(0.690), m_sin2phi1(sqrt(1.-m_cos2phi1*m_cos2phi1))
{
  GetParams("kspipi_eq_phase_params.txt",m_C,m_S,m_K,m_Kb);
  GetParams("d0pipi_eq_phase_params.txt",m_Cap,m_Sig,m_Kap,m_Kapb);

  SetVars();
}

int AbsToyDblDalitz::GetParams(std::string fname,double* C,double* S,double* K,double* Kb){
  std::cout << "Getting parameters from " << fname << std::endl;
  std::ifstream ifile(fname.c_str(),std::ifstream::in);
  if(!ifile.is_open()) return -1;
  std::string line;
  int bin;
  double c,s,k,kb,q;
  int flag;
  for(int i=0; i<8; i++){
    getline(ifile,line);
    flag = sscanf(line.c_str(),"%d: C = %lf, S = %lf, K = %lf, Kb = %lf, Q = %lf",&bin,&c,&s,&k,&kb,&q);
    if(i != (bin-1) || flag != 6) return -2;
    C[i]  = c; S[i]  = s; K[i]  = k; Kb[i] = kb;
    std::cout << i+1 << " C: " << C[i] << " S: " << S[i] << " K: " << K[i] << " Kb: " << Kb[i] << std::endl;
  }
  std::cout << "Done!" << std::endl;
  return 0;
}

void AbsToyDblDalitz::SetVars(void){
  dt    = new RooRealVar("dt","dt",m_dt_min,m_dt_max,"ps");
  tau   = new RooRealVar("tau","tau",m_tau,"ps");
  dm    = new RooRealVar("dm","dm",m_dm);
  wrtag = new RooRealVar("wrtag","wrtag",m_wrtag);

  res_mean  = new RooRealVar("res_mean","res_mean",m_res_mean);
  res_sigma = new RooRealVar("res_sigma","res_sigma",m_res_sigma);

  cos2phi1 = new RooRealVar("cos2phi1","cos2phi1",m_cos2phi1,-5.,5.);
  sin2phi1 = new RooRealVar("sin2phi1","sin2phi1",m_sin2phi1,-5.,5.);

  Cap = new RooRealVar("Cap","Cap",0.,-1.,1.);
  Sig = new RooRealVar("Sig","Sig",0.,-1.,1.);
  Kap = new RooRealVar("Kap","Kap",0., 0.,1.);
  Kapb = new RooRealVar("Kapb","Kapb",0.,0.,1.);
}
