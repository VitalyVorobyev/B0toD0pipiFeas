#include "toysimpdf.h"
#include "toycat.h"

#include <sstream>
#include <string>

using namespace std;

ToySimPdf::ToySimPdf():
  AbsToyDblDalitz()
{
  SetParams();
  SetModels();
}

void ToySimPdf::SetModels(void){
  SetNoTagPdf();
  SetFlvPdf();
  SetCPPdf();
  SetDDPdf();
  SetSimPdf();
//  spdfcp   = new RooSimultaneous("spdfcp", "spdfcp", *ToyCat::GetCPSuperCat());
//  spdfflv  = new RooSimultaneous("spdfflv","spdfflv",*ToyCat::GetFlv());
//  spdfdd   = new RooSimultaneous("spdfdd", "spdfdd", *ToyCat::GetDDSuperCat());
//  for(int i=0; i<2; i++){// flv
//    for(int j=-8; j<=8; j++){if(j!=0){// Binb
//      const int Bind = ToyCat::BinInd(j);
//      for(int k=0; k<2; k++){
//        const int cp = ToyCat::CP(k);
//        out.str(""); out << "cppdf" << Bind << "_" << i << "_" << k;
//        pdfcp[i][k][Bind] = new ToyCPPdf(out.str(),w_Kap[Bind],w_Kapb[Bind],w_Cap[Bind],w_Sig[Bind],cp,flv);
//        out.str(""); out << "{binb" << Bind << ";CP" << (cp == 1 ? "p" : "m") << ";" << (flv == 1 ? "B0" : "B0B") << "}";
//        spdfcp->addPdf(*pdfcp[i][k][Bind]->GetPdf(),out.str().c_str());
//      }
//      for(int k=-8; k<=8; k++){if(k!=0){// Dind
//        const int Dind = ToyCat::BinInd(k);
//        out.str(""); out << "dbldlzpdf" << Bind << "-" << Dind << "-" << i;
//        pdfdd[i][Bind][Dind] = new ToyDblDalitzPdf(out.str(),w_K[Dind],w_Kb[Dind],w_C[Dind],w_S[Dind],w_Kap[Bind],w_Kapb[Bind],w_Cap[Bind],w_Sig[Bind],flv);
//        out.str(""); out << "{binb" << Bind << ";bind" << Dind << ";" << (flv == 1 ? "B0" : "B0B") << "}";
//        spdfdd->addPdf(*pdfdd[i][Bind][Dind]->GetPdf(),out.str().c_str());
//      }}
//    }}
//  }
}

void ToySimPdf::SetNoTagPdf(void){
  pdfnotag = new ToyFlvPdf("pdfnotag",0);
}

void ToySimPdf::SetFlvPdf(void){
  stringstream out;
  spdfflv  = new RooSimultaneous("spdfflv","spdfflv",*ToyCat::GetFlv());
  for(int i=0; i<2; i++){//flv
    const int flv = ToyCat::Flv(i);
    out.str(""); out << "flvpdf" << i+1;
    pdfflv[i] = new ToyFlvPdf(out.str(),flv);
    out.str(""); out << (flv == 1 ? "B0" : "B0B");
    spdfflv->addPdf(*pdfflv[i]->GetPdf(),out.str().c_str());
  }
}

void ToySimPdf::SetCPPdf(const int N){
  const int Np = N/2;
  const int Nn = N/2;
  stringstream out;
  for(int i=0; i<2; i++){//flv
    const int flv = ToyCat::Flv(i);
    for(int j=-8; j<=8; j++){if(j!=0){//Bind
      const int Bind = ToyCat::BinInd(j);
      for(int k=0; k<2; k++){
        const int cp = ToyCat::CP(k);
        out.str(""); out << "cppdf" << Bind << "_" << i << "_" << k;
        const string ttl = out.str();
        const string exttl = string("ext") + ttl;
        const string extvt = string("extvar") + ttl;
        pdfcp[i][k][Bind] = new ToyCPPdf(ttl,w_Kap[Bind],w_Kapb[Bind],w_Cap[Bind],w_Sig[Bind],cp,flv);
        const int nev = cp == 1 ? 0.5*Np*GetFractionD0pipi(j,flv) : 0.5*Nn*GetFractionD0pipi(j,flv);
        const int Nev = nev>0 ? nev : 1;
        if(nev <= 0){
          cout << "ToySimPdf::SetCPPdf not positive amount of events " << nev << " is requested";
          cout << " for CP " << cp << ", flv " << flv << ", Bbin " << j << "!" << endl;
        }
        extvarcp[i][k][Bind] = new RooRealVar(extvt.c_str(),extvt.c_str(),Nev);
        extpdfcp[i][k][Bind] = new RooExtendPdf(exttl.c_str(),exttl.c_str(),*pdfcp[i][k][Bind]->GetPdf(),*extvarcp[i][k][Bind]);
      }
    }}
  }
}

void ToySimPdf::SetDDPdf(const int N){
  stringstream out;
  for(int i=0; i<2; i++){//flv
    const int flv = ToyCat::Flv(i);
    for(int j=-8; j<=8; j++){if(j!=0){//Bind
      const int Bind = ToyCat::BinInd(j);
      for(int k=-8; k<=8; k++){if(k!=0){//Dind
        const int Dind = ToyCat::BinInd(k);
        out.str(""); out << "ddpdf" << Bind << "_" << i << "_" << k;
        const string ttl = out.str();
        const string exttl = string("ext") + ttl;
        const string extvt = string("extvar") + ttl;
        pdfdd[i][Bind][Dind] = new ToyDblDalitzPdf(out.str(),w_K[Dind],w_Kb[Dind],w_C[Dind],w_S[Dind],w_Kap[Bind],w_Kapb[Bind],w_Cap[Bind],w_Sig[Bind],flv);
        const int nev = 0.5*N*GetFractionDblDlz(j,k,flv);
        const int Nev = nev>0 ? nev : 1;
        if(nev <= 0){
          cout << "ToySimPdf::SetDDPdf not positive amount of events " << nev << " is requested";
          cout << " for Dind " << Dind << ", flv " << flv << ", Bbin " << j << "!" << endl;
        }
        extvardd[i][Bind][Dind] = new RooRealVar(extvt.c_str(),extvt.c_str(),Nev);
        extpdfdd[i][Bind][Dind] = new RooExtendPdf(exttl.c_str(),exttl.c_str(),*pdfdd[i][Bind][Dind]->GetPdf(),*extvardd[i][Bind][Dind]);
      }}
    }}
  }
}

void ToySimPdf::SetSimPdf(void){
  stringstream out;
  spdf = new RooSimultaneous("spdf","spdf",*ToyCat::GetSuperCat());
  for(int i=0; i<2; i++){//flv
    const int flv = ToyCat::Flv(i);
    for(int j=-8; j<=8; j++){if(j!=0){//Bind
      const int Bind = ToyCat::BinInd(j);
      for(int k=-8; k<=8; k++){if(k!=0){//Dind
        const int Dind = ToyCat::BinInd(k);
        out.str(""); out << "{binb" << Bind << ";bind" << Dind << ";CP0;" << (flv == 1 ? "B0" : "B0B") << "}";
        spdf->addPdf(*extpdfdd[i][Bind][Dind],out.str().c_str());
//        spdf->addPdf(*pdfdd[i][Bind][Dind]->GetPdf(),out.str().c_str());
      }}
      for(int k=0; k<2; k++){
        const int cp = ToyCat::CP(k);
        out.str(""); out << "{binb" << Bind << ";bindz;CP" << (cp == 1 ? "p" : "m") << ";" << (flv == 1 ? "B0" : "B0B") << "}";
        spdf->addPdf(*extpdfcp[i][k][Bind],out.str().c_str());
//        spdf->addPdf(*pdfcp[i][k][Bind]->GetPdf(),out.str().c_str());
      }
    }}
  }
}

void ToySimPdf::SetParams(){
  stringstream out;
  const DlzBinStruct *ddlz = DPars();
  const DlzBinStruct *bdlz = BPars();
  // * Binning parameters * //
  for(int i=0; i<8; i++){
    out.str(""); out << "C" << i+1;
    v_C[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),ddlz->C(i+1),-3.,3.);
    out.str(""); out << "S" << i+1;
    v_S[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),ddlz->S(i+1),-3.,3.);
    out.str(""); out << "K" << i+1;
    v_K[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),ddlz->Kp(i+1),0.,1.);
    out.str(""); out << "Kb" << i+1;
    v_Kb[i] = new RooRealVar(out.str().c_str(),out.str().c_str(),ddlz->Kn(i+1),0.,1.);

    out.str(""); out << "fC" << i+1;
    vf_C[i]   = new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_C[i]));
    out.str(""); out << "fS" << i+1;
    vf_S[i]   = new RooFormulaVar(out.str().c_str(),out.str().c_str(),"-@0",RooArgList(*v_S[i]));
    out.str(""); out << "fK" << i+1;
    vf_K[i]   = new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_Kb[i]));
    out.str(""); out << "fKb" << i+1;
    vf_Kb[i]  = new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_K[i]));

    out.str(""); out << "Cap" << i+1;
    v_Cap[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),bdlz->C(i+1),-3.,3.);
    out.str(""); out << "Sig" << i+1;
    v_Sig[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),bdlz->S(i+1),-3.,3.);
    out.str(""); out << "Kap" << i+1;
    v_Kap[i]  = new RooRealVar(out.str().c_str(),out.str().c_str(),bdlz->Kp(i+1),0.,1.);
    out.str(""); out << "Kapb" << i+1;
    v_Kapb[i] = new RooRealVar(out.str().c_str(),out.str().c_str(),bdlz->Kn(i+1),0.,1.);

    out.str(""); out << "fCap" << i+1;
    vf_Cap[i] = new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_Cap[i]));
    out.str(""); out << "fSig" << i+1;
    vf_Sig[i] = new RooFormulaVar(out.str().c_str(),out.str().c_str(),"-@0",RooArgList(*v_Sig[i]));
    out.str(""); out << "fKap" << i+1;
    vf_Kap[i] = new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_Kapb[i]));
    out.str(""); out << "fKapb" << i+1;
    vf_Kapb[i]= new RooFormulaVar(out.str().c_str(),out.str().c_str()," @0",RooArgList(*v_Kap[i]));

    const int pind = ToyCat::BinInd(  i+1);
    const int nind = ToyCat::BinInd(-(i+1));
    w_K[pind]  = v_K[i];  w_K[nind]  = vf_K[i];
    w_Kb[pind] = v_Kb[i]; w_Kb[nind] = vf_Kb[i];
    w_C[pind]  = v_C[i];  w_C[nind]  = vf_C[i];
    w_S[pind]  = v_S[i];  w_S[nind]  = vf_S[i];

    w_Kap[pind]  = v_Kap[i];  w_Kap[nind]  = vf_Kap[i];
    w_Kapb[pind] = v_Kapb[i]; w_Kapb[nind] = vf_Kapb[i];
    w_Cap[pind]  = v_Cap[i];  w_Cap[nind]  = vf_Cap[i];
    w_Sig[pind]  = v_Sig[i];  w_Sig[nind]  = vf_Sig[i];
  }
}

void ToySimPdf::FixBParams(const bool var){
  FixCap(var); FixSig(var); FixKap(true); FixKapb(true);
}

void ToySimPdf::ReleaseBBin(const int bin){
  v_Cap[bin-1]->setConstant(kFALSE);
  v_Sig[bin-1]->setConstant(kFALSE);
}

void ToySimPdf::FixDParams(const bool var){
  FixC(var); FixS(var); FixK(var); FixKb(var);
}

void ToySimPdf::FixCap(const bool var){
  for(int i=0; i<8; i++) v_Cap[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixSig(const bool var){
  for(int i=0; i<8; i++) v_Sig[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixKap(const bool var){
  for(int i=0; i<8; i++) v_Kap[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixKapb(const bool var){
  for(int i=0; i<8; i++) v_Kapb[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixC(const bool var){
  for(int i=0; i<8; i++) v_C[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixS(const bool var){
  for(int i=0; i<8; i++) v_S[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixK(const bool var){
  for(int i=0; i<8; i++) v_K[i]->setConstant(var ? kTRUE : kFALSE);
}

void ToySimPdf::FixKb(const bool var){
  for(int i=0; i<8; i++) v_Kb[i]->setConstant(var ? kTRUE : kFALSE);
}
