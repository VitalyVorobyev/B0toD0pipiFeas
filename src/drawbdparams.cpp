#include "drawbdparams.h"

using namespace std;
using namespace ROOT;
Int_t colors[9] = {0,7,1,0,2,3,46,4,5};

DrawBDParams::DrawBDParams(){
  m_krf = false;
  m_csrf = false;
}

void DrawBDParams::DrawBDP(const string& infile,const string& outname,const int type){
  gStyle->SetPalette((sizeof(colors)/sizeof(Int_t)),colors);
  ifstream ifile(infile.c_str());
  if(!ifile.is_open()) return;

  int GridSize;
  double minX,maxX;
  double minY,maxY;
  int nbins = 0;

  string line;
  getline(ifile,line);
  sscanf(line.c_str(),"GridSize %d",&GridSize);
  cout << "Grid size: " << GridSize << endl;
  getline(ifile,line);
  double mmo,mcha,mchb,mchc;
  sscanf(line.c_str(),"%lf -> %lf %lf %lf",&mmo,&mcha,&mchb,&mchc);
  string Xtitle;
  string Ytitle;
  switch (type) {
  case 1:
    getline(ifile,line);
    sscanf(line.c_str(),"mAB: %lf %lf",&minX,&maxX);
    getline(ifile,line);
    sscanf(line.c_str(),"mAC: %lf %lf",&minY,&maxY);
    getline(ifile,line);
    getline(ifile,Xtitle);
    getline(ifile,Ytitle);
    getline(ifile,line);
    break;
  case 2:
    getline(ifile,line);
    sscanf(line.c_str(),"mAB: %lf %lf",&minX,&maxX);
    getline(ifile,line);
    getline(ifile,line);
    sscanf(line.c_str(),"mBC: %lf %lf",&minY,&maxY);
    getline(ifile,Xtitle);
    getline(ifile,line);
    getline(ifile,Ytitle);
    break;
  case 3:
    getline(ifile,line);
    getline(ifile,line);
    sscanf(line.c_str(),"mAC: %lf %lf",&minX,&maxX);
    getline(ifile,line);
    sscanf(line.c_str(),"mBC: %lf %lf",&minY,&maxY);
    getline(ifile,line);
    getline(ifile,Xtitle);
    getline(ifile,Ytitle);
    break;
  default:
    break;
  }

  cout << "min value: " << minX << endl;
  cout << "max value: " << maxX << endl;

  const int HalfSize = GridSize/2;
  TH2I* bin_hist = new TH2I("bin_hist","bin_hist",HalfSize,minX,maxX,HalfSize,minY,maxY);
  bin_hist->SetStats(0);
  bin_hist->SetContour(9);
  bin_hist->SetMarkerSize(1.7);
  bin_hist->GetXaxis()->SetTitle(Xtitle.c_str());
  bin_hist->GetXaxis()->SetLabelSize(0.05);
  bin_hist->GetXaxis()->SetTitleSize(0.05);
  bin_hist->GetXaxis()->SetTitleOffset(0.8);
  bin_hist->GetYaxis()->SetTitle(Ytitle.c_str());
  bin_hist->GetYaxis()->SetLabelSize(0.05);
  bin_hist->GetYaxis()->SetTitleSize(0.05);
  bin_hist->GetYaxis()->SetTitleOffset(0.8);

  double mp,mm,mbc;
  int bin;

  DalitzPhaseSpace phsp(mmo,mcha,mchb,mchc);
  while(!ifile.eof()){
    getline(ifile,line);
    sscanf(line.c_str(),"%lf %lf %lf %d",&mp,&mm,&mbc,&bin);
    if(bin > nbins) nbins = bin;
    switch (type) {
    case 1:
      bin_hist->SetBinContent(bin_hist->FindBin(mp,mm),bin);
      bin_hist->SetBinContent(bin_hist->FindBin(mm,mp),bin);
      break;
    case 2:
      bin_hist->SetBinContent(bin_hist->FindBin(mp,mbc),bin);
      mbc = phsp.mBCsq(mm,mp);
      bin_hist->SetBinContent(bin_hist->FindBin(mm,mbc),bin);
      break;
    case 3:
      bin_hist->SetBinContent(bin_hist->FindBin(mm,mbc),bin);
      mbc = phsp.mBCsq(mm,mp);
      bin_hist->SetBinContent(bin_hist->FindBin(mp,mbc),bin);
      break;
    default:
      break;
    }
  }

  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  c1->cd();
  bin_hist->SetMinimum(-0.5);
  bin_hist->SetMaximum(nbins + 0.5);
  bin_hist->Draw("ColZ");

  stringstream out;
  out.str("");
  out << outname << type << ".root";
  c1->Print(out.str().c_str());

  out.str("");
  out << outname << type << ".png";
  c1->Print(out.str().c_str());

  out.str("");
  out << "display " << outname << type << ".png &";
  system(out.str().c_str());

  return;
}

void DrawBDParams::DrawCS(const vector<double>& C,const vector<double>& S,const string& fname){
  const int nbins = C.size();
  double c[nbins];
  double s[nbins];
  for(int i=0; i<nbins; i++){ c[i] = C[i]; s[i] = S[i];}
  TGraph* grCS = new TGraph(8,c,s);
  grCS->SetMarkerStyle(20);
  grCS->SetMarkerSize(1);
  grCS->SetLineStyle(0);
  grCS->SetMarkerColor(kBlue);

  double circ_x[100],circ_y[100];
  for(int i=0; i<100; i++){
    circ_x[i] = cos(0.01*i*2.*M_PI);
    circ_y[i] = sin(0.01*i*2.*M_PI);
  }
  TGraph* gr_circ = new TGraph(100,circ_x,circ_y);
  gr_circ->SetMarkerStyle(20);
  gr_circ->SetMarkerSize(0.3);
  gr_circ->SetLineStyle(1);
  gr_circ->SetMarkerColor(kBlack);

  TMultiGraph* mgCS = new TMultiGraph("mgCS","mgCS");
  mgCS->Add(grCS);
  mgCS->Add(gr_circ);

  TCanvas* c1 = new TCanvas("c1","c1",400,470);
  c1->cd();
  c1->SetGrid();
  mgCS->Draw("ap");
  mgCS->GetXaxis()->SetTitle("C_{i}");
  mgCS->GetXaxis()->SetTitleSize(0.06);
  mgCS->GetXaxis()->SetTitleOffset(0.75);
  mgCS->GetXaxis()->SetLabelSize(0.06);
  mgCS->GetYaxis()->SetTitle("S_{i}");
  mgCS->GetYaxis()->SetTitleSize(0.06);
  mgCS->GetYaxis()->SetTitleOffset(0.75);
  mgCS->GetYaxis()->SetLabelSize(0.06);
  mgCS->Draw("ap");

  stringstream out;
  out.str("");
  out << fname << ".root";
  c1->Print(out.str().c_str());

  out.str("");
  out << fname << ".eps";
  c1->Print(out.str().c_str());

  out.str("");
  out << fname << ".png";
  c1->Print(out.str().c_str());

  out.str("");
  out << "display " << fname << ".png &";
  system(out.str().c_str());
  return;
}

void DrawBDParams::DrawK(const vector<double>& K,const vector<double>& Kb,const string& fname){
  const int nbins = K.size();
  double bin[nbins];
  double k[nbins];
  double kb[nbins];
  for(int i=0; i<nbins; i++){ bin[i] = i+1; k[i] = K[i]; kb[i] = Kb[i];}
  TGraph* grK  = new TGraph(8,bin,k);
  grK->SetMarkerStyle(20);
  grK->SetMarkerSize(1);
  grK->SetLineStyle(0);
  grK->SetMarkerColor(kBlue);
  TGraph* grKb = new TGraph(8,bin,kb);
  grKb->SetMarkerStyle(21);
  grKb->SetMarkerSize(1);
  grKb->SetLineStyle(0);
  grKb->SetMarkerColor(kBlue);

  TMultiGraph* mgK = new TMultiGraph("mgK","mgK");
  mgK->Add(grK);
  mgK->Add(grKb);

  TCanvas* c2 = new TCanvas("c2","c2",600,700);
  c2->cd();
  c2->SetGrid();
  mgK->Draw("ap");
  mgK->GetXaxis()->SetTitle("Dalitz bin");
  mgK->GetXaxis()->SetTitleSize(0.06);
  mgK->GetXaxis()->SetTitleOffset(0.75);
  mgK->GetXaxis()->SetLabelSize(0.06);
  mgK->GetYaxis()->SetTitle("K_{i}");
  mgK->GetYaxis()->SetTitleSize(0.06);
  mgK->GetYaxis()->SetTitleOffset(0.75);
  mgK->GetYaxis()->SetLabelSize(0.05);

  stringstream out;
  out.str("");
  out << fname << ".root";
  c2->Print(out.str().c_str());

  out.str("");
  out << fname << ".eps";
  c2->Print(out.str().c_str());

  out.str("");
  out << fname << ".png";
  c2->Print(out.str().c_str());

  out.str("");
  out << "display " << fname << ".png &";
  system(out.str().c_str());
  return;
}
