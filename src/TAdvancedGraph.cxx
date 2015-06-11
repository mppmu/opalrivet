#ifndef TADVANCEDGRAPH_CXX
#define TADVANCEDGRAPH_CXX
#include "TAdvancedGraph.h"
//#include "TIter.h"
#include "TCollection.h"
#include <algorithm>
ClassImp(TAdvancedGraph)

TAdvancedGraph::TAdvancedGraph(): TGraphAsymmErrors(){};

 TAdvancedGraph::TAdvancedGraph(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exl , const Double_t* exh , const Double_t* eyl , const Double_t* eyh ):
 TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh){};
TAdvancedGraph::TAdvancedGraph(Int_t n) : TGraphAsymmErrors(n){};
int TAdvancedGraph::Merge(TCollection *hlist)
{
   // Possible implementation for TH1::Merge; the real one add checks on the ranges ...
 
   if (hlist) {
      TAdvancedGraph *xh = 0;
      TIter nxh(hlist);
      while ((xh = (TAdvancedGraph *) nxh())) {
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


return true;
	
}	




void TAdvancedGraph::Scale(double k)
{
    int i;
    for (i=0; i<this->GetN(); i++)
        {
            Double_t x,y;
            this->GetPoint(i,x,y);
            this->SetPoint(i,x,y*k);
            this->SetPointError(i,this->GetErrorXlow(i),this->GetErrorXhigh(i),this->GetErrorYlow(i),this->GetErrorYhigh(i));
        }
}




void TAdvancedGraph::Divide(TAdvancedGraph* A, TAdvancedGraph* B)
{

    if(A->GetN() != B->GetN())
        {
            puts("TAdvancedGraph::Divide are not consistent: they have different number of bins");
            return;
        }

std::vector<double>	finaly;
std::vector<double>	finalyel;
std::vector<double>	finalyeh;
 std::vector<double>	finalx;
std::vector<double>	finalxel;
std::vector<double>	finalxeh;


    for(Int_t i = 0; i < B->GetN() ; ++i)

        {
            Double_t Ax,Bx,Ay,By,Cx,Cy,Dx,Dy,Cyeh,Cyel,Cxeh,Cxel,Byeh,Byel,Ayeh,Ayel;
            A->GetPoint(i,Ax,Ay);
            B->GetPoint(i,Bx,By);

            Cxel=A->GetErrorXlow(i);
            Cxeh=A->GetErrorXhigh(i);

            Ayel=A->GetErrorYlow(i);
            Ayeh=A->GetErrorYhigh(i);

            Byel=B->GetErrorYlow(i);
            Byeh=B->GetErrorYhigh(i);

            Cx=Ax;
            if (std::abs(By)>1.E-15)
                {
                    Cy=Ay/By;
                    Cyeh=sqrt(Ayeh*Ayeh/(By*By)+Byel*Byel/(By*By*By*By)*Ay*Ay);
                    Cyel=sqrt(Ayel*Ayel/(By*By)+Byeh*Byeh/(By*By*By*By)*Ay*Ay);
                }
            else { Cy=0; Cyel=0; Cyeh=0;}
            
            
            finaly.push_back(Cy);
            finalyel.push_back(Cyel);
            finalyeh.push_back(Cyeh);       
            
                        finalx.push_back(Cx);
            finalxel.push_back(Cxel);
            finalxeh.push_back(Cxeh);     
            
             if(std::abs(Ax-Bx)>1e-12)
                {
                    puts("TAdvancedGraph::Divide are not consistent: they have different bin edges: E1");
                    return;

                }

            if(std::abs(A->GetErrorXlow(i)- B->GetErrorXlow(i))>1e-12)
                {
                    puts("TAdvancedGraph::Divide are not consistent: they have different bin edges: E2");
                    return;

                }

            if(std::abs(A->GetErrorXhigh(i)- B->GetErrorXhigh(i))>1e-12)
                {
                    puts("TAdvancedGraph::Divide are not consistent: they have different bin edges: E3");
                    return;
                }

        }
        
this->Set(finalx.size());
for (unsigned int j=0;j<finalx.size();j++)
{
this->SetPoint(j,finalx[j],	finaly[j]);
this->SetPointError(j,finalxel[j],	finalxeh[j],	finalyel[j],	finalyeh[j]);	
	
}	
        
        
}
#endif

