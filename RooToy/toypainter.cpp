#include "toypainter.h"
#include "toyvars.h"
#include "toycat.h"

#include "RooPlot.h"
#include "RooHist.h"

#include "TCanvas.h"
#include "TAxis.h"
#include "TLine.h"
#include "TPad.h"


void ToyPainter::DrawLifetime(RooDataSet* ds, RooBDecay* pdf){
  RooRealVar* dt = ToyVars::Get_dt();
  ToyVars::Set_dt_lim(-10,10);
  RooPlot* dtFrame = dt->frame();
  dtFrame->SetTitle("Toy lifetime fit");
  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerSize(1),RooFit::Name("data"));
  pdf->plotOn(dtFrame,RooFit::LineWidth(2));

  RooHist* hpull = dtFrame->pullHist();
  RooPlot* dtPull  = dt->frame(RooFit::Title(""));
  dtPull->addPlotable(hpull,"P");
  dtPull->GetYaxis()->SetRangeUser(-5,5);

  TCanvas* cm = new TCanvas("mc","mc",600,700);
  cm->cd();

  TPad *pad1 = new TPad("pad1","pad1",0.01,0.20,0.99,0.99);
  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.20);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLeftMargin(0.15);
  pad1->SetFillColor(0);

  dtFrame->GetXaxis()->SetTitleSize(0.05);
  dtFrame->GetXaxis()->SetTitleOffset(0.85);
  dtFrame->GetXaxis()->SetLabelSize(0.04);
  dtFrame->GetYaxis()->SetTitleOffset(1.6);
  dtFrame->Draw();

  pad2->cd(); pad2->SetLeftMargin(0.15); pad2->SetFillColor(0);
  dtPull->SetMarkerSize(0.05); dtPull->Draw();
  TLine *lineUP = new TLine(dt->getMin(),3,dt->getMax(),3);
  lineUP->SetLineColor(kBlue);
  lineUP->SetLineStyle(2);
  lineUP->Draw();
  TLine *line = new TLine(dt->getMin(),0,dt->getMax(),0);
  line->SetLineColor(kBlue);
  line->SetLineStyle(1);
  line->SetLineWidth((Width_t)2.);
  line->Draw();
  TLine *lineDOWN = new TLine(dt->getMin(),-3,dt->getMax(),-3);
  lineDOWN->SetLineColor(kBlue);
  lineDOWN->SetLineStyle(2);
  lineDOWN->Draw();

  cm->Update();
  cm->Print("pics/toylifetime.root");
  cm->Print("pics/toylifetime.eps");

  system("evince pics/toylifetime.eps &");
}

void ToyPainter::DrawFlvFit(RooDataSet* ds, RooSimultaneous* pdf){
  RooRealVar* dt = ToyVars::Get_dt();
  RooCategory* flv = ToyCat::GetFlv();
  ToyVars::Set_dt_lim(-10,10);
  RooPlot* dtFrame = dt->frame();
  dtFrame->SetTitle("Toy flavor fit");

  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::Cut("flv == -1"),RooFit::MarkerSize(1),RooFit::Name("data2"),RooFit::MarkerColor(kRed));
  pdf->plotOn(dtFrame,RooFit::LineWidth(1),RooFit::Slice(*flv,"B0B"),RooFit::ProjWData(*flv,*ds));

  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::Cut("flv == 1"),RooFit::MarkerSize(1),RooFit::Name("data1"),RooFit::MarkerColor(kBlue));
  pdf->plotOn(dtFrame,RooFit::LineWidth(1),RooFit::Slice(*flv,"B0"),RooFit::ProjWData(*flv,*ds));

  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerSize(1),RooFit::Name("data"));
  pdf->plotOn(dtFrame,RooFit::LineWidth(2),RooFit::ProjWData(*flv,*ds));

  RooHist* hpull = dtFrame->pullHist();
  RooPlot* dtPull  = dt->frame(RooFit::Title(""));
  dtPull->addPlotable(hpull,"P");
  dtPull->GetYaxis()->SetRangeUser(-5,5);

  TCanvas* cm = new TCanvas("mc","mc",600,700);
  cm->cd();

  TPad *pad1 = new TPad("pad1","pad1",0.01,0.20,0.99,0.99);
  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.20);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLeftMargin(0.15);
  pad1->SetFillColor(0);

  dtFrame->GetXaxis()->SetTitleSize(0.05);
  dtFrame->GetXaxis()->SetTitleOffset(0.85);
  dtFrame->GetXaxis()->SetLabelSize(0.04);
  dtFrame->GetYaxis()->SetTitleOffset(1.6);
  dtFrame->Draw();

  pad2->cd(); pad2->SetLeftMargin(0.15); pad2->SetFillColor(0);
  dtPull->SetMarkerSize(0.05); dtPull->Draw();
  TLine *lineUP = new TLine(dt->getMin(),3,dt->getMax(),3);
  lineUP->SetLineColor(kBlue);
  lineUP->SetLineStyle(2);
  lineUP->Draw();
  TLine *line = new TLine(dt->getMin(),0,dt->getMax(),0);
  line->SetLineColor(kBlue);
  line->SetLineStyle(1);
  line->SetLineWidth((Width_t)2.);
  line->Draw();
  TLine *lineDOWN = new TLine(dt->getMin(),-3,dt->getMax(),-3);
  lineDOWN->SetLineColor(kBlue);
  lineDOWN->SetLineStyle(2);
  lineDOWN->Draw();

  cm->Update();
  cm->Print("pics/toyflv.root");
  cm->Print("pics/toyflv.eps");

  system("evince pics/toyflv.eps &");
}

void ToyPainter::DrawCPFit(RooDataSet* ds, RooSimultaneous* pdf){
  RooRealVar* dt    = ToyVars::Get_dt();
  RooCategory* flv  = ToyCat::GetFlv();
  RooCategory* cp   = ToyCat::GetCP();
  RooCategory* binb = ToyCat::GetBBin();
  RooArgSet aset(*flv,*cp,*binb);
  ToyVars::Set_dt_lim(-10,10);
  RooPlot* dtFrame = dt->frame();
  dtFrame->SetTitle("Toy CP fit");

  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerSize(1),RooFit::Name("data"));
  pdf->plotOn(dtFrame,RooFit::LineWidth(2),RooFit::ProjWData(aset,*ds));

  RooHist* hpull = dtFrame->pullHist();
  RooPlot* dtPull  = dt->frame(RooFit::Title(""));
  dtPull->addPlotable(hpull,"P");
  dtPull->GetYaxis()->SetRangeUser(-5,5);

  TCanvas* cm = new TCanvas("mc","mc",600,700);
  cm->cd();

  TPad *pad1 = new TPad("pad1","pad1",0.01,0.20,0.99,0.99);
  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.20);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLeftMargin(0.15);
  pad1->SetFillColor(0);

  dtFrame->GetXaxis()->SetTitleSize(0.05);
  dtFrame->GetXaxis()->SetTitleOffset(0.85);
  dtFrame->GetXaxis()->SetLabelSize(0.04);
  dtFrame->GetYaxis()->SetTitleOffset(1.6);
  dtFrame->Draw();

  pad2->cd(); pad2->SetLeftMargin(0.15); pad2->SetFillColor(0);
  dtPull->SetMarkerSize(0.05); dtPull->Draw();
  TLine *lineUP = new TLine(dt->getMin(),3,dt->getMax(),3);
  lineUP->SetLineColor(kBlue);
  lineUP->SetLineStyle(2);
  lineUP->Draw();
  TLine *line = new TLine(dt->getMin(),0,dt->getMax(),0);
  line->SetLineColor(kBlue);
  line->SetLineStyle(1);
  line->SetLineWidth((Width_t)2.);
  line->Draw();
  TLine *lineDOWN = new TLine(dt->getMin(),-3,dt->getMax(),-3);
  lineDOWN->SetLineColor(kBlue);
  lineDOWN->SetLineStyle(2);
  lineDOWN->Draw();

  cm->Update();
  cm->Print("pics/toycp.root");
  cm->Print("pics/toycp.eps");

  system("evince pics/toycp.eps &");
}

void ToyPainter::DrawDblDlzFit(RooDataSet* ds, RooSimultaneous* pdf){
  std::cout << "Drawing..." << std::endl;
  RooRealVar* dt = ToyVars::Get_dt();
  ToyVars::Set_dt_lim(-10,10);
  RooPlot* dtFrame = dt->frame();
  dtFrame->SetTitle("Toy double Dalitz fit");

  ds->plotOn(dtFrame,RooFit::DataError(RooAbsData::SumW2),RooFit::MarkerSize(1),RooFit::Name("data"));
  pdf->plotOn(dtFrame,RooFit::LineWidth(2),RooFit::ProjWData(*ToyCat::GetASet(),*ds));

  RooHist* hpull = dtFrame->pullHist();
  RooPlot* dtPull  = dt->frame(RooFit::Title(""));
  dtPull->addPlotable(hpull,"P");
  dtPull->GetYaxis()->SetRangeUser(-5,5);

  TCanvas* cm = new TCanvas("mc","mc",600,700);
  cm->cd();

  TPad *pad1 = new TPad("pad1","pad1",0.01,0.20,0.99,0.99);
  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.20);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  pad1->SetLeftMargin(0.15);
  pad1->SetFillColor(0);

  dtFrame->GetXaxis()->SetTitleSize(0.05);
  dtFrame->GetXaxis()->SetTitleOffset(0.85);
  dtFrame->GetXaxis()->SetLabelSize(0.04);
  dtFrame->GetYaxis()->SetTitleOffset(1.6);
  dtFrame->Draw();

  pad2->cd(); pad2->SetLeftMargin(0.15); pad2->SetFillColor(0);
  dtPull->SetMarkerSize(0.05); dtPull->Draw();
  TLine *lineUP = new TLine(dt->getMin(),3,dt->getMax(),3);
  lineUP->SetLineColor(kBlue);
  lineUP->SetLineStyle(2);
  lineUP->Draw();
  TLine *line = new TLine(dt->getMin(),0,dt->getMax(),0);
  line->SetLineColor(kBlue);
  line->SetLineStyle(1);
  line->SetLineWidth((Width_t)2.);
  line->Draw();
  TLine *lineDOWN = new TLine(dt->getMin(),-3,dt->getMax(),-3);
  lineDOWN->SetLineColor(kBlue);
  lineDOWN->SetLineStyle(2);
  lineDOWN->Draw();

  cm->Update();
  cm->Print("pics/toydbldlz.root");
  cm->Print("pics/toydbldlz.eps");

  system("evince pics/toydbldlz.eps &");
}

