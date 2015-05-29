#ifndef TADVANCEDGRAPH_CXX
#define TADVANCEDGRAPH_CXX
#include "TAdvancedGraph.h"
//#include "TIter.h"
#include "TCollection.h"
#include <algorithm>
//ClassImp(TAdvancedGraph)


TAdvancedGraph::TAdvancedGraph(Int_t n) : TGraphAsymmErrors(n){};
int TAdvancedGraph::Merge(TCollection *hlist)
{
   // Possible implementation for TH1::Merge; the real one add checks on the ranges ...
 
   if (hlist) {
      TAdvancedGraph *xh = 0;
      TIter nxh(hlist);
      while (xh = (TAdvancedGraph *) nxh()) {
         // Add this histogram to me
         Add(this,xh);
      }
   }
 return this->GetN();
}





Bool_t TAdvancedGraph::Add( TAdvancedGraph* A, TAdvancedGraph* B, Double_t cA , Double_t cB )
{
if (!A&&!B) return false;
std::vector<double>	allx;
double Ax,Bx,Ay,By;
if (A) for (int i = 0; i < A->GetN() ; ++i) {A->GetPoint(i,Ax,Ay);  allx.push_back(Ax);}
if (B) for (int i = 0; i < B->GetN() ; ++i) {B->GetPoint(i,Bx,By);  allx.push_back(Bx);}
std::sort(allx.begin(), allx.end());
std::vector<double>	finalx;
std::vector<double>	finaly;
std::vector<double>	finalyel;
std::vector<double>	finalyeh;
for (std::vector<double>::iterator it=allx.begin();it!=allx.end();it++)
if 	(finalx.size()==0) finalx.push_back(*it);
else if (std::abs(*it-finalx.back())>1e-12) finalx.push_back(*it);	



for (unsigned int j=0;j<finalx.size();j++)
{
double Cx=finalx[j],Cy=0,Cyeh=0,Cyel=0;

if (A) for (int i = 0; i < A->GetN() ; ++i) 
{
double x,y,yel,yeh;
A->GetPoint(i,x,y); 
yel=A->GetErrorYlow(i);
yeh=A->GetErrorYhigh(i);	
if (std::abs(finalx[j]-x)<1e-12)
{
Cy+=cA*y;
Cyel=std::sqrt(Cyel*Cyel+cA*yel*cA*yel);
Cyeh=std::sqrt(Cyeh*Cyeh+cA*yeh*cA*yeh);
}	
}

if (B) for (int i = 0; i < B->GetN() ; ++i) 
{
double x,y,yel,yeh;
B->GetPoint(i,x,y); 
yel=B->GetErrorYlow(i);
yeh=B->GetErrorYhigh(i);	
if (std::abs(finalx[j]-x)<1e-12)
{
Cy+=cB*y;
Cyel=std::sqrt(Cyel*Cyel+cB*yel*cB*yel);
Cyeh=std::sqrt(Cyeh*Cyeh+cB*yeh*cB*yeh);
}	
}
            finaly.push_back(Cy);
            finalyel.push_back(Cyel);
            finalyeh.push_back(Cyeh);            

}	

this->Set(finalx.size());
for (unsigned int j=0;j<finalx.size();j++)
{
this->SetPoint(j,finalx[j],	finaly[j]);
this->SetPointError(j,0,0,	finalyel[j],	finalyeh[j]);	
	
}	



	
}	




void TAdvancedGraph::Scale(TGraphAsymmErrors* A, double k)
{
    int i;
    for (i=0; i<A->GetN(); i++)
        {
            Double_t x,y;
            A->GetPoint(i,x,y);
            A->SetPoint(i,x,y*k);
            A->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),A->GetErrorYlow(i),A->GetErrorYhigh(i));
        }
}


#endif

/*
TGraphAsymmErrors* DivideGraphs(TGraphAsymmErrors* A, TGraphAsymmErrors* B, TGraphAsymmErrors* D=NULL,double toll=1.E-15)
{

    if(A->GetN() != B->GetN())
        {
            puts("TEfficiency::CheckBinnrams are not consistent: they have different number of bins");
            return NULL;
        }
    TGraphAsymmErrors* C;
    if (!D)  C= new TGraphAsymmErrors( B->GetN());
    else C=D;
    if (D)  if(A->GetN() != D->GetN())
            {
                puts("TEfficiency::CheckBinnrams are not consistent: they have different number of bins");
                return NULL;
            }

    for(Int_t i = 0; i < B->GetN() ; ++i)

        {
            Double_t Ax,Bx,Ay,By,Cx,Cy,Dx,Dy,Cyeh,Cyel,Byeh,Byel,Ayeh,Ayel;
            A->GetPoint(i,Ax,Ay);
            B->GetPoint(i,Bx,By);
            if (D) D->GetPoint(i,Dx,Dy);

            Ayel=A->GetErrorYlow(i);
            Ayeh=A->GetErrorYhigh(i);

            Byel=B->GetErrorYlow(i);
            Byeh=B->GetErrorYhigh(i);

            Cx=Ax;
            if (TMath::Abs(By)>1.E-15)
                {
                    Cy=Ay/By;
                    Cyeh=sqrt(Ayeh*Ayeh/(By*By)+Byel*Byel/(By*By*By*By)*Ay*Ay);
                    Cyel=sqrt(Ayel*Ayel/(By*By)+Byeh*Byeh/(By*By*By*By)*Ay*Ay);
                }
            else { Cy=0; Cyel=0; Cyeh=0;}
            C->SetPoint(i,Cx,Cy);
            C->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),Cyel,Cyeh);
            //  printf("D %i %f %f %f %f\n",Cx,Cy,Cyel,Cyeh);
            if(!TMath::AreEqualRel(Ax, Bx, toll))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E1");
                    return NULL;

                }

            if(!TMath::AreEqualRel(A->GetErrorXlow(i), B->GetErrorXlow(i),  toll))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E2");
                    return NULL;

                }

            if(!TMath::AreEqualRel(A->GetErrorXhigh(i), B->GetErrorXhigh(i),  toll))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E3");
                    return NULL;
                }
            if (D)
                {

                    if(!TMath::AreEqualRel(Ax, Dx,  toll))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E4");
                            return NULL;

                        }

                    if(!TMath::AreEqualRel(A->GetErrorXlow(i), D->GetErrorXlow(i),  toll))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E5");
                            return NULL;

                        }

                    if(!TMath::AreEqualRel(A->GetErrorXhigh(i), D->GetErrorXhigh(i), toll))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E6");
                            return NULL;
                        }




                }

        }
    return C;



}
*/
