#ifndef DRAWBDPARAMS_H
#define DRAWBDPARAMS_H

#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TCanvas.h"

#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "../libDalitz/src/libdalitz.h"

class DrawBDParams{
public:
  DrawBDParams();
  void DrawBinsmABmAC(const std::string& infile,const std::string& outname){
    DrawBDP(infile,outname,1);
  }
  void DrawBinsmABmBC(const std::string& infile,const std::string& outname){
    DrawBDP(infile,outname,2);
  }
  void DrawBinsmACmBC(const std::string& infile,const std::string& outname){
    DrawBDP(infile,outname,3);
  }
  void DrawBDP(const std::string& infile,const std::string& outname,const int type);
  void DrawCS(const std::vector<double>& C,const std::vector<double>& S,const std::string& fname);
  void DrawK(const std::vector<double>& K,const std::vector<double>& Kb,const std::string& fname);

  void SetCSRef(std::vector<double>& C,std::vector<double>& S) {Cref = &C; Sref = &S; m_csrf = true; return;}
  void SetKRef(std::vector<double>& K,std::vector<double>& Kb) {Kref = &K; Kbref = &Kb; m_krf = true; return;}
  void RemoveCSRef(void) {m_csrf = false; return;}
  void RemoveKRef(void) {m_krf = false; return;}

private:
  std::vector<double>* Kref;
  std::vector<double>* Kbref;
  std::vector<double>* Cref;
  std::vector<double>* Sref;
  bool m_krf;
  bool m_csrf;
};

#endif // DRAWBDPARAMS_H
