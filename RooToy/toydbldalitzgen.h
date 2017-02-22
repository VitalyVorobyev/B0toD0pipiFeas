#ifndef TOYDBLDALITZGEN_H
#define TOYDBLDALITZGEN_H

#include <string>
#include <vector>

#include "toyflvpdf.h"
#include "toycppdf.h"
#include "toydbldalitzpdf.h"
#include "abstoydbldalitz.h"

#include "RooDataSet.h"

class ToyDblDalitzGen : protected AbsToyDblDalitz{
public:
  ToyDblDalitzGen(void);

  RooDataSet* GenerateFlv(const int Nev,const int flv);
  RooDataSet* GenerateCP(const int Nev,const int flv,const int cp, const int bin);
  RooDataSet* GenerateDblDlz(const int Nev, const int flv, const int binb, const int bind);

  RooDataSet* GenerateFlv(const int Nev);
  RooDataSet* GenerateCP(const int NevP,const int NevN);
  RooDataSet* GenerateDblDlz(const int Nev);

  RooBDecay*  FlvPdf(void)    const {return pdfflv->GetPdf();}
  RooBDecay*  CPPdf(void)     const {return pdfcp->GetPdf();}
  RooBDecay*  DblDlzPdf(void) const {return pdfdbl->GetPdf();}

  void SetKspipiBin(const int i);
  void SetD0pipiBin(const int i);
  void SetBins(const int binb, const int bind);

private:
  ToyFlvPdf*       pdfflv;
  ToyCPPdf*        pdfcp;
  ToyDblDalitzPdf* pdfdbl;

  void SetModels(void);
  void SetParams(void);

  RooRealVar* v_C;
  RooRealVar* v_S;
  RooRealVar* v_K;
  RooRealVar* v_Kb;

  RooRealVar* v_Cap;
  RooRealVar* v_Sig;
  RooRealVar* v_Kap;
  RooRealVar* v_Kapb;

  int m_bind, m_binb;
};

#endif // TOYDBLDALITZGEN_H
