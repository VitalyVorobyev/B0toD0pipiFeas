#include "toydbldalitzgen.h"
#include <fstream>

#include "RooGaussModel.h"
#include "RooCategory.h"
#include "TRandom3.h"

using namespace std;
ToyDblDalitzGen::ToyDblDalitzGen():
  AbsToyDblDalitz()
{
  SetModels();
}

void ToyDblDalitzGen::SetModels(void){
  res_model = (RooResolutionModel*) new RooGaussModel("gauss","gauss",*dt,*res_mean,*res_sigma);
  pdfflv = new ToyFlvPdf("flv",dt,tau,dm,wrtag,res_model);
  pdfcp  = new ToyCPPdf("cp",dt,tau,dm,sin2phi1,cos2phi1,wrtag,Kap,Kapb,Cap,Sig,res_model);
}

RooDataSet* ToyDblDalitzGen::GenerateFlv(const int Nev,const int flv){
  return pdfflv->Generate(Nev,flv);
}

RooDataSet* ToyDblDalitzGen::GenerateCP(const int Nev,const int flv,const int cp, const int bin){
  double c,s,k,kb;
  if(bin>0){
    const int i = bin-1;
    c = m_Cap[i]; s = m_Sig[i]; k = m_Kap[i];  kb = m_Kapb[i];
  } else{
    const int i =-bin-1;
    c = m_Cap[i]; s =-m_Sig[i]; k = m_Kapb[i]; kb = m_Kap[i];
  }
  return pdfcp->Generate(Nev,flv,cp,c,s,k,kb);
}

double ToyDblDalitzGen::GetFractionFlv(const int bin, const int flv) const{
  double res = 0;
  switch(flv){
  case 1:
    res = bin>0 ? m_Kap[bin-1] : m_Kapb[-bin-1];
    break;
  case 2:
    res = bin>0 ? m_Kapb[bin-1] : m_Kap[-bin-1];
    break;
  }
  return 0.5*res;
}

double ToyDblDalitzGen::GetFractionCP(const int bin, const int flv, const int cp) const{
  double res = 0;
  switch(flv){
  case 1:
    res = bin>0 ? fabs(m_Kap[bin-1]+cp*m_Kapb[bin-1]) : fabs(m_Kapb[-bin-1]+cp*m_Kap[-bin-1]);
    break;
  case 2:
    res = bin>0 ? fabs(m_Kapb[bin-1]+cp*m_Kap[bin-1]) : fabs(m_Kap[-bin-1]+cp*m_Kapb[-bin-1]);
    break;
  }
  return 0.5*res;
}

RooDataSet* ToyDblDalitzGen::GenerateFlv(const int Nev){
  RooCategory* bin = new RooCategory("bin","bin");
  stringstream out;
  for(int i=0; i<8; i++){
    out.str(""); out << "bin" << i+1;
    bin->defineType(out.str().c_str(),i+1);
    out.str(""); out << "binb" << i+1;
    bin->defineType(out.str().c_str(),-(i+1));
  }
  RooCategory* flv = new RooCategory("flv","flv");
  flv->defineType("B0",  1);
  flv->defineType("B0B",-1);

  RooDataSet* ds = new RooDataSet("ds","ds",RooArgSet(*dt,*flv));
  RooArgSet argset; argset.add(*flv);
  TRandom3* rndm = new TRandom3();
  rndm->SetSeed(0);

  for(int j=0; j<2; j++){
    flv->setIndex(2*j-1);
    for(int k=-8; k<=8; k++){if(k){
      bin->setIndex(k);
//      const int nev = rndm->Poisson(Nev*GetFractionFlv(k,2*j-1));
      const int nev = 100;
      if(!nev){
        std::cout << "ToyDblDalitzGen::GenerateFlv Zero event requested!" << std::endl;
        return ds;
      }
      RooDataSet* protods = new RooDataSet("protods","protods",argset);
      for(int ii=0; ii<nev; ii++) protods->add(argset);
      RooDataSet* ds0 = GenerateFlv(nev,2*j-1);
      ds0->merge(protods);
      ds->append(*ds0);
    }}
  }
  return ds;
}

RooDataSet* ToyDblDalitzGen::GenerateCP(const int Nev){
  RooCategory* bin = new RooCategory("bin","bin");
  stringstream out;
  for(int i=0; i<8; i++){
    out.str(""); out << "bin" << i+1;
    bin->defineType(out.str().c_str(),i+1);
    out.str(""); out << "binb" << i+1;
    bin->defineType(out.str().c_str(),-(i+1));
  }
  RooCategory* flv = new RooCategory("flv","flv");
  flv->defineType("B0",  1);
  flv->defineType("B0B",-1);
  RooCategory* cp  = new RooCategory("cp","cp");
  cp->defineType("CP+", 1);
  cp->defineType("CP-",-1);

  RooDataSet* ds = new RooDataSet("ds","ds",RooArgSet(*dt,*bin,*flv,*cp));
  RooArgSet argset;
  argset.add(*bin); argset.add(*flv); argset.add(*cp);
  TRandom3* rndm = new TRandom3();
  rndm->SetSeed(0);

  for(int i=0; i<2; i++){
    cp->setIndex(2*i-1);
    for(int j=0; j<2; j++){
      flv->setIndex(2*j-1);
      for(int k=-8; k<=8; k++){if(k){
        bin->setIndex(k);
//        const int nev = rndm->Poisson(Nev*GetFractionCP(k,2*j-1,2*i-1));
        const int nev = 100;
        if(!nev){
          std::cout << "ToyDblDalitzGen::GenerateCP Zero event requested!" << std::endl;
          return ds;
        }
        RooDataSet* protods = new RooDataSet("protods","protods",argset);
        for(int ii=0; ii<nev; ii++) protods->add(argset);
        RooDataSet* ds0 = GenerateCP(nev,2*j-1,2*i-1,k);
        ds0->merge(protods);
        ds->append(*ds0);
      }}
    }
  }
  return ds;
}
