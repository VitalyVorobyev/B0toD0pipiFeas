#include "toydbldalitzfit.h"
#include <sstream>

#include "RooConstVar.h"
#include "RooTruthModel.h"
#include "RooGenericPdf.h"

using namespace std;

ToyDblDalitzFit::ToyDblDalitzFit():
  ToySimPdf()
{
}

RooFitResult* ToyDblDalitzFit::FitFlv(RooDataSet* ds){
  return GetFlvPdf()->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
}

RooFitResult* ToyDblDalitzFit::FitCP(RooDataSet* ds){
//  return spdfcp->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
  return GetSimPdf()->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
}

RooFitResult* ToyDblDalitzFit::FitDblDlz(RooDataSet* ds){
//  return spdfdd->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
  return GetSimPdf()->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
}

RooFitResult* ToyDblDalitzFit::FitLifetime(RooDataSet* ds){
//  RooBDecay* pdfi = pdfnotag->GetPdf();
  return GetLifetimePdf()->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
}

RooFitResult* ToyDblDalitzFit::FitSimul(RooDataSet* ds){
  return GetSimPdf()->fitTo(*ds,RooFit::Save(),RooFit::Verbose(),RooFit::Timer());
}
