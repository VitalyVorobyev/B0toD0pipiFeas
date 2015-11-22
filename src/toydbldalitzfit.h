#ifndef TOYDBLDALITZFIT_H
#define TOYDBLDALITZFIT_H

#include "toyflvpdf.h"
#include "toycppdf.h"
#include "toydbldalitzpdf.h"

#include "RooSimultaious.h"
#include "RooCategory.h"
#include "RooSuperCategory.h"

class ToyDblDalitzFit{
public:
  ToyDblDalitzFit();

private:
  ToyFlvPdf* pdfflv[2];
  ToyFlvPdf* pdfcp[2][16];
  ToyFlvPdf* pdfcp[2][16][16];


};

#endif // TOYDBLDALITZFIT_H
