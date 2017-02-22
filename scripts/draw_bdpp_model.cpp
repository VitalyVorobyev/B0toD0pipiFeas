const string tname("tree");
const string fname("/home/vitaly/B0toD0pipi/B0toD0pipiFeas/DPTree_d0pipi.root");

const string mdpip_cut("mp < 9 && 31.4-mp-mm > 3");
const string mpipi_cut("mp > 9 && 31.4-mp-mm < 3");

const int mdpip_color = kBlue;
const int mpipi_color = kMagenta;

const int hist_fill_style = 3001;

void draw_dp(TTree* t){
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  c1->cd();
  c1->Draw();
  const string xname("m^{2}(#pi^{+}#pi^{-}) (GeV^{2}/c^{4})");
  const string yname("m^{2}(D^{0}#pi^{+})   (GeV^{2}/c^{4})");

  gPad->SetLeftMargin(0.15);
  gPad->SetTopMargin(0.05);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);

  t->Draw("mp:31.4-mp-mm");
  TH2F* hist = (TH2F*)gROOT->FindObject("htemp");
  hist->SetName("");
  hist->SetTitle("");
  hist->GetXaxis()->SetTitle(xname.c_str());
  hist->GetYaxis()->SetTitle(yname.c_str());
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetLabelSize(0.06);

  c1->Update();
  c1->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_dp.root");
  c1->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_dp.eps");
}

void draw_dp_zones(TTree* t){
  TCanvas* c4 = new TCanvas("c4","c4",600,600);
  c4->cd();
  c4->Draw();
  const string xname("m^{2}(#pi^{+}#pi^{-}) (GeV^{2}/c^{4})");
  const string yname("m^{2}(D^{0}#pi^{+})   (GeV^{2}/c^{4})");
  const string varname("mp:31.4-mp-mm");

  gPad->SetLeftMargin(0.15);
  gPad->SetTopMargin(0.05);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);

  t->SetMarkerStyle(6);
  t->Draw("mp:31.4-mp-mm");
  TH2F* hist = (TH2F*)gROOT->FindObject("htemp");
  hist->SetName("");
  hist->SetTitle("");
  hist->GetXaxis()->SetTitle(xname.c_str());
  hist->GetYaxis()->SetTitle(yname.c_str());
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetLabelSize(0.06);

  t->SetMarkerColor(mdpip_color);
  t->Draw(varname.c_str(),mdpip_cut.c_str(),"same");

  t->SetMarkerColor(mpipi_color);
  t->Draw(varname.c_str(),mpipi_cut.c_str(),"same");

  c4->Update();
  c4->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_dp_zones.root");
  c4->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_dp_zones.eps");
}

void draw_mpipi(TTree* t){
  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  const string xname("m(#pi^{+}#pi^{-}) (GeV/c^{2})");
  c2->SetGridx();

  gPad->SetLeftMargin(0.1);
  gPad->SetTopMargin(0.05);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);

  t->Draw("sqrt(31.4-mp-mm)",mpipi_cut.c_str());
  TH1F* hist = (TH1F*)gROOT->FindObject("htemp");
  hist->SetName("");
  hist->SetTitle("");
  hist->SetStats(kFALSE);
  hist->SetFillStyle(hist_fill_style);
  hist->SetFillColor(mpipi_color);
  hist->GetXaxis()->SetTitle(xname.c_str());
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetLabelSize(0.06);
  c2->Update();
  c2->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_mpipi.root");
  c2->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_mpipi.eps");
}

void draw_mdpip(TTree* t){
  TCanvas* c3 = new TCanvas("c3","c3",800,600);
  const string xname("m(D^{0}#pi^{+}) (GeV/c^{2})");
  c3->SetGridx();

  gPad->SetLeftMargin(0.1);
  gPad->SetTopMargin(0.05);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.15);

  t->Draw("sqrt(mp)",mdpip_cut.c_str());
  TH1F* hist = (TH1F*)gROOT->FindObject("htemp");
  hist->SetName("");
  hist->SetTitle("");
  hist->SetStats(kFALSE);
  hist->SetFillStyle(hist_fill_style);
  hist->SetFillColor(mdpip_color);
  hist->GetXaxis()->SetTitle(xname.c_str());
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetLabelSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1);
  hist->GetYaxis()->SetLabelSize(0.06);
  c3->Update();
  c3->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_mdpip.root");
  c3->Print("/home/vitaly/B0toD0pipi/Note/pics/bdpp_model_mdpip.eps");
}

void draw_bdpp_model(void){
  TChain* tree = new TChain(tname.c_str());
  tree->Add(fname.c_str());
  draw_dp(tree);
  draw_mpipi(tree);
  draw_mdpip(tree);
  draw_dp_zones(tree);
}
