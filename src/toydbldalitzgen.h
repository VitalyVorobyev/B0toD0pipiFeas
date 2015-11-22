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
  ToyDblDalitzGen();

  RooDataSet* GenerateFlv(const int Nev,const int flv);
  RooDataSet* GenerateCP(const int Nev,const int flv,const int cp, const int bin);

  RooDataSet* GenerateFlv(const int Nev);
  RooDataSet* GenerateCP(const int Nev);

  RooBDecay*  FlvPdf(void) const {return pdfflv->GetPdf();}
  RooBDecay*  CPPdf(void)  const {return pdfcp->GetPdf();}

  double GetFractionFlv(const int bin, const int flv) const;
  double GetFractionCP(const int bin, const int flv, const int cp) const;
private:
  ToyFlvPdf*       pdfflv;
  ToyCPPdf*        pdfcp;
  ToyDblDalitzPdf* pdfdbl;
  void SetModels(void);
};

#endif // TOYDBLDALITZGEN_H
