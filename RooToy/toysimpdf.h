#ifndef TOYSIMPDF_H
#define TOYSIMPDF_H

#include "toyflvpdf.h"
#include "toycppdf.h"
#include "toydbldalitzpdf.h"
#include "abstoydbldalitz.h"

#include "RooSimultaneous.h"
#include "RooExtendPdf.h"

class ToySimPdf : public AbsToyDblDalitz{
public:
  ToySimPdf();

  RooBDecay* GetLifetimePdf(void)  {return pdfnotag->GetPdf();}
  RooSimultaneous* GetFlvPdf(void) {return spdfflv;}
  RooSimultaneous* GetCPPdf(void)  {return spdfcp;}
  RooSimultaneous* GetDDPdf(void)  {return spdfdd;}
  RooSimultaneous* GetSimPdf(void) {return spdf;}

  void FixBParams(const bool var);
  void FixDParams(const bool var);
  void FixCap(const bool var);
  void FixSig(const bool var);
  void FixKap(const bool var);
  void FixKapb(const bool var);
  void FixC(const bool var);
  void FixS(const bool var);
  void FixK(const bool var);
  void FixKb(const bool var);
  void ReleaseBBin(const int bin);

private:
  ToyFlvPdf*       pdfnotag;
  ToyFlvPdf*       pdfflv[2];
  ToyCPPdf*        pdfcp[2][2][16];
  ToyDblDalitzPdf* pdfdd[2][16][16];

  RooExtendPdf* extpdfcp[2][2][16];
  RooExtendPdf* extpdfdd[2][16][16];
  RooRealVar*   extvarcp[2][2][16];
  RooRealVar*   extvardd[2][16][16];

  RooSimultaneous* spdfdd;
  RooSimultaneous* spdfflv;
  RooSimultaneous* spdfcp;
  RooSimultaneous* spdf;

private:
  void SetModels(void);
  void SetParams(void);
  void SetNoTagPdf(void);
  void SetFlvPdf(void);
  void SetCPPdf(const int N = 1400);
  void SetDDPdf(const int N = 1300);
  void SetSimPdf(void);

  // Real parameters
  RooRealVar* v_C[8];
  RooRealVar* v_S[8];
  RooRealVar* v_K[8];
  RooRealVar* v_Kb[8];

  RooRealVar* v_Cap[8];
  RooRealVar* v_Sig[8];
  RooRealVar* v_Kap[8];
  RooRealVar* v_Kapb[8];

  // Formulas for negative bins
  RooFormulaVar* vf_C[8];
  RooFormulaVar* vf_S[8];
  RooFormulaVar* vf_K[8];
  RooFormulaVar* vf_Kb[8];

  RooFormulaVar* vf_Cap[8];
  RooFormulaVar* vf_Sig[8];
  RooFormulaVar* vf_Kap[8];
  RooFormulaVar* vf_Kapb[8];

  // Arrays of pointers
  RooAbsReal* w_C[16];
  RooAbsReal* w_S[16];
  RooAbsReal* w_K[16];
  RooAbsReal* w_Kb[16];

  RooAbsReal* w_Cap[16];
  RooAbsReal* w_Sig[16];
  RooAbsReal* w_Kap[16];
  RooAbsReal* w_Kapb[16];
};

#endif // TOYSIMPDF_H
