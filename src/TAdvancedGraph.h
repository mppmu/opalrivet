#ifndef UBACKGROUND_H
#define UBACKGROUND_H
#include "TGraphAsymmErrors.h"
class TAdvancedGraph: public TGraphAsymmErrors
{
public:
 TAdvancedGraph(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exl = 0, const Double_t* exh = 0, const Double_t* eyl = 0, const Double_t* eyh = 0);

 TAdvancedGraph(Int_t n);// : TGraphAsymmErrors(n){};
int Merge(TCollection *hlist);
Bool_t Add( TAdvancedGraph* h,  TAdvancedGraph* h2, Double_t c1 = 1, Double_t c2 = 1);
void Divide(TAdvancedGraph* A,  TAdvancedGraph* B);
void Scale(double k);
ClassDef(TAdvancedGraph,0)
};
#endif
