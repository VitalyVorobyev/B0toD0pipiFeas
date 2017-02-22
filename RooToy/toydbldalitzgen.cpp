#include "toydbldalitzgen.h"
#include "toycat.h"
#include "toyvars.h"

#include <fstream>

#include "RooGaussModel.h"
#include "RooCategory.h"
#include "TRandom3.h"

using namespace std;
ToyDblDalitzGen::ToyDblDalitzGen(void):
  AbsToyDblDalitz()
{
  SetParams();
  SetModels();
}

void ToyDblDalitzGen::SetParams(void){
  v_C    = new RooRealVar("C", "C", 0.,-1.,1.);
  v_S    = new RooRealVar("S", "S", 0.,-1.,1.);
  v_K    = new RooRealVar("K", "K", 0., 0.,1.);
  v_Kb   = new RooRealVar("Kb","Kb",0., 0.,1.);

  v_Cap  = new RooRealVar("Cap", "Cap", 0.,-1.,1.);
  v_Sig  = new RooRealVar("Sig", "Sig", 0.,-1.,1.);
  v_Kap  = new RooRealVar("Kap", "Kap", 0., 0.,1.);
  v_Kapb = new RooRealVar("Kapb","Kapb",0., 0.,1.);
}

void ToyDblDalitzGen::SetModels(void){
  pdfflv = new ToyFlvPdf("flvpdf");
  pdfcp  = new ToyCPPdf("cppdf",v_Kap,v_Kapb,v_Cap,v_Sig);
  pdfdbl = new ToyDblDalitzPdf("dbldlzpdf",v_K,v_Kb,v_C,v_S,v_Kap,v_Kapb,v_Cap,v_Sig);
}

void ToyDblDalitzGen::SetKspipiBin(const int i){
  if(i == 0 || abs(i)>8){
    cout << "AbsToyDblDalitz::SetKspipiBin: wrong bin number " << i << endl;
    return;
  }
  const DlzBinStruct* ddlz = DPars();
  m_bind = i;
  v_K->setVal( ddlz->Kp(m_bind));
  v_Kb->setVal(ddlz->Kn(m_bind));
  v_C->setVal( ddlz->C(m_bind));
  v_S->setVal( ddlz->S(m_bind));
}

void ToyDblDalitzGen::SetD0pipiBin(const int i){
  if(i == 0 || abs(i)>8){
    cout << "AbsToyDblDalitz::SetD0pipiBin: wrong bin number " << i << endl;
    return;
  }
  const DlzBinStruct* bdlz = BPars();
  m_binb = i;
  v_Kap->setVal( bdlz->Kp(m_binb));
  v_Kapb->setVal(bdlz->Kn(m_binb));
  v_Cap->setVal( bdlz->C(m_binb));
  v_Sig->setVal( bdlz->S(m_binb));
}

void ToyDblDalitzGen::SetBins(const int binb, const int bind){
  SetKspipiBin(bind);
  SetD0pipiBin(binb);
}

RooDataSet* ToyDblDalitzGen::GenerateFlv(const int Nev,const int flv){
  return pdfflv->Generate(Nev,flv);
}

RooDataSet* ToyDblDalitzGen::GenerateCP(const int Nev,const int flv,const int cp, const int bin){
  SetD0pipiBin(bin);
  return pdfcp->Generate(Nev,flv,cp);
}

RooDataSet* ToyDblDalitzGen::GenerateDblDlz(const int Nev, const int flv, const int binb, const int bind){
  SetBins(binb,bind);
  return pdfdbl->Generate(Nev,flv);
}

RooDataSet* ToyDblDalitzGen::GenerateFlv(const int Nev){
  RooCategory* bin = ToyCat::GetBBin();
  RooCategory* flv = ToyCat::GetFlv();
  RooRealVar*  dt  = ToyVars::Get_dt();
  RooDataSet*  ds  = new RooDataSet("ds","ds",RooArgSet(*dt,*bin,*flv));
  RooArgSet argset; argset.add(*bin); argset.add(*flv);
//  TRandom3* rndm = new TRandom3();
//  rndm->SetSeed(0);

  for(int j=0; j<2; j++){
    flv->setIndex(2*j-1);
    for(int k=-8; k<=8; k++){if(k){
      bin->setIndex(k);
//      const int nev = rndm->Poisson(Nev*GetFractionFlv(k,2*j-1));
      const int nev = 0.5*Nev*GetFractionD0pipi(k,2*j-1);
      if(nev <= 0){
        std::cout << "ToyDblDalitzGen::GenerateFlv not positive number of event " << nev << " is requested";
        std::cout << " for flv " << 2*j-1 << ", Bbin " << k << "!" << std::endl;
        continue;
      }
      RooDataSet* protods = new RooDataSet("protods","protods",argset);
      for(int ii=0; ii<nev; ii++) protods->add(argset);
      RooDataSet* ds0 = GenerateFlv(nev,2*j-1);
      if(ds0->sumEntries() != nev){
        cout << "Wrong ds0 size " << ds0->sumEntries() << endl;
        return protods;
      }
      ds0->merge(protods);
      ds->append(*ds0);
    }}
  }
  return ds;
}

RooDataSet* ToyDblDalitzGen::GenerateCP(const int NevP,const int NevN){
  RooCategory* bin = ToyCat::GetBBin();
  RooCategory* flv = ToyCat::GetFlv();
  RooCategory* cp  = ToyCat::GetCP();
  RooRealVar*  dt  = ToyVars::Get_dt();
  RooDataSet* ds = new RooDataSet("ds","ds",RooArgSet(*dt,*bin,*flv,*cp));
  RooArgSet argset; argset.add(*bin); argset.add(*flv); argset.add(*cp);
//  TRandom3* rndm = new TRandom3();
//  rndm->SetSeed(0);

  for(int i=0; i<2; i++){
    cp->setIndex(2*i-1);
    for(int j=0; j<2; j++){
      flv->setIndex(2*j-1);
      for(int k=-8; k<=8; k++){if(k){
        bin->setIndex(k);
//        const int nev = rndm->Poisson(Nev*GetFractionCP(k,2*j-1,2*i-1));
        const int nev = i == 0 ? 0.5*NevN*GetFractionD0pipi(k,2*j-1) : 0.5*NevP*GetFractionD0pipi(k,2*j-1);
        if(nev <= 0){
          std::cout << "ToyDblDalitzGen::GenerateCP not positive number of event " << nev << " is requested";
          std::cout << " for CP " << 2*i-1 << ", flv " << 2*j-1 << ", Bbin " << k << "!" << std::endl;
          continue;
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

RooDataSet* ToyDblDalitzGen::GenerateDblDlz(const int Nev){
  RooCategory* binb= ToyCat::GetBBin();
  RooCategory* bind= ToyCat::GetDBin();
  RooCategory* flv = ToyCat::GetFlv();
  RooRealVar*  dt  = ToyVars::Get_dt();

  RooDataSet* ds = new RooDataSet("ds","ds",RooArgSet(*dt,*binb,*bind,*flv));
  RooArgSet argset; argset.add(*binb); argset.add(*bind); argset.add(*flv);

  for(int ib=-8; ib<=8; ib++){ if(ib != 0){
    binb->setIndex(ib);
    for(int id=-8; id<=8; id++){ if(id != 0){
      bind->setIndex(id);
      for(int j=0; j<2; j++){
        const int iflv = 2*j-1;
        flv->setIndex(iflv);
//        const int nev = rndm->Poisson(0.5*Nev*GetFractionDblDlz(ib,id,iflv));
        const int nev = 0.5*Nev*GetFractionDblDlz(ib,id,iflv);
        if(nev <= 0){
          std::cout << "ToyDblDalitzGen::GenerateDblDtz " << nev << " events is requested";
          std::cout << "for Bbin " << ib << ", Dbin " << id << ", flv " << iflv << "!" << std::endl;
          continue;
        }
        RooDataSet* protods = new RooDataSet("protods","protods",argset);
        for(int ii=0; ii<nev; ii++) protods->add(argset);
        RooDataSet* ds0 = GenerateDblDlz(nev,iflv,ib,id);
        ds0->merge(protods);
        ds->append(*ds0);
      }
    }}
  }}
  return ds;
}

