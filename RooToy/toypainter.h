#ifndef TOYPAINTER_H
#define TOYPAINTER_H

#include "RooDataSet.h"
#include "RooBDecay.h"
#include "RooSimultaneous.h"

class ToyPainter{
public:
  ToyPainter() {}

  static void DrawLifetime(RooDataSet* ds, RooBDecay* pdf);
  static void DrawFlvFit(RooDataSet* ds, RooSimultaneous* pdf);
  static void DrawCPFit(RooDataSet* ds, RooSimultaneous* pdf);
  static void DrawDblDlzFit(RooDataSet* ds, RooSimultaneous* pdf);
private:
};

#endif // TOYPAINTER_H
