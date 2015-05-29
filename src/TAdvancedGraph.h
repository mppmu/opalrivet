#ifndef UBACKGROUND_H
#define UBACKGROUND_H
#include "TGraphAsymmErrors.h"
class TAdvancedGraph: public TGraphAsymmErrors
{
public:
 TAdvancedGraph(Int_t n);// : TGraphAsymmErrors(n){};
int Merge(TCollection *hlist);
Bool_t Add( TAdvancedGraph* h,  TAdvancedGraph* h2, Double_t c1 = 1, Double_t c2 = 1);
void Divide(TAdvancedGraph* A,  TAdvancedGraph* B);
void Scale(double k);
//ClassDef(TAdvancedGraph,0)
};
#endif
