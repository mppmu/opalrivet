/*
 * ZBestNumber.h
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#ifndef TADVANCEDGRAPH_CXX
#define TADVANCEDGRAPH_CXX
#include "TAdvancedGraph.h"
#include "TCollection.h"
#include "TH1D.h"
#include <algorithm>
ClassImp(TAdvancedGraph)


TAdvancedGraph::TAdvancedGraph(TH1D* a): TGraphAsymmErrors(a) {}

TAdvancedGraph::TAdvancedGraph(): TGraphAsymmErrors() {}

TAdvancedGraph::TAdvancedGraph(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exl , const Double_t* exh , const Double_t* eyl , const Double_t* eyh ):
    TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh) {}
TAdvancedGraph::TAdvancedGraph(Int_t n) : TGraphAsymmErrors(n) {}
int TAdvancedGraph::Merge(TCollection *hlist)
{
    if (hlist)
        {
            TAdvancedGraph *xh = 0;
            TIter nxh(hlist);
            while ((xh = (TAdvancedGraph *) nxh()))  Add(this,xh);
        }
    return this->GetN();
}


TH1D* TAdvancedGraph::ToTH1D(std::string n,int l)
{
    int N=this->GetN();
    double* xx=(double*)malloc((N+1)*sizeof(double));
    double Ax,Ay;
    double yel,yeh,xel,xeh;
    for (int i = 0; i < this->GetN() ; ++i)
        {
            this->GetPoint(i,Ax,Ay);

            yel=this->GetErrorYlow(i);
            yeh=this->GetErrorYhigh(i);
            xel=this->GetErrorXlow(i);
            xeh=this->GetErrorXhigh(i);

            if (l<0) xx[i]=Ax-xel;
            if (l==0) xx[i]=Ax;
            if (l>0) xx[i]=Ax+xeh;
        }
    if (l<0) xx[N]=Ax-xel;
    if (l==0) xx[N]=Ax;
    if (l>0) xx[N]=Ax+xeh;


    TH1D* H= new TH1D(n.c_str(),n.c_str(),N,xx);


    for (int i = 0; i < this->GetN() ; ++i)
        {
            this->GetPoint(i,Ax,Ay);

            yel=this->GetErrorYlow(i);
            yeh=this->GetErrorYhigh(i);
            xel=this->GetErrorXlow(i);
            xeh=this->GetErrorXhigh(i);



            H->SetBinContent(i+1,Ay);
            H->SetBinError(i+1,0.5*std::abs(yel)+0.5*std::abs(yeh));
        }

    return H;


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
    for (std::vector<double>::iterator it=allx.begin(); it!=allx.end(); it++)
        if 	(finalx.size()==0) finalx.push_back(*it);
        else if (std::abs(*it-finalx.back())>1e-9&&(std::abs(*it-finalx.back())/std::abs(*it+finalx.back())>1e-3 )  ) finalx.push_back(*it);


    for (unsigned int j=0; j<finalx.size(); j++)
        {
            double Cy=0,Cyeh=0,Cyel=0;

            if (A) for (int i = 0; i < A->GetN() ; ++i)
                    {
                        double x,y,yel,yeh;
                        A->GetPoint(i,x,y);
                        yel=A->GetErrorYlow(i);
                        yeh=A->GetErrorYhigh(i);
                        if (std::abs(x-finalx[j])>1e-9&&(std::abs(x-finalx[j])/std::abs(x+finalx[j])>1e-3 )  ) {}
                        else
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
                        if (std::abs(x-finalx[j])>1e-9&&(std::abs(x-finalx[j])/std::abs(x+finalx[j])>1e-3 )  ) {}
                        else
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
    for (unsigned int j=0; j<finalx.size(); j++)
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
            this->SetPointError(i,this->GetErrorXlow(i),this->GetErrorXhigh(i),k*this->GetErrorYlow(i),k*this->GetErrorYhigh(i));
        }
}


void TAdvancedGraph::ScaleNorm(double k)
{
    int i;
    for (i=0; i<this->GetN(); i++)
        {
            Double_t x,y;
            this->GetPoint(i,x,y);
            this->SetPoint(i,x,y*k);
            if (y*k>1.0) printf("TAdvancedGraph::ScaleNorm Error\n");
            this->SetPointError(i,this->GetErrorXlow(i),this->GetErrorXhigh(i),sqrt(k*(1-y*k)),sqrt(k*(1-y*k)));
        }
}



void TAdvancedGraph::Divide(TAdvancedGraph* AA, TAdvancedGraph* BB, bool keepconsistent)
{

    if (keepconsistent)
        if(AA->GetN() != BB->GetN())
            {
                printf("TAdvancedGraph::Divide are not consistent: they have different number of bins: %i and %i\n",AA->GetN() , BB->GetN());
                AA->Print();
                BB->Print();
                return;
            }
    TAdvancedGraph* A=new  TAdvancedGraph();
    A->Add(AA,BB,1.0,0.0);
    TAdvancedGraph* B=new  TAdvancedGraph();
    B->Add(AA,BB,0.0,1.0);
    std::vector<double>	finaly;
    std::vector<double>	finalyel;
    std::vector<double>	finalyeh;
    std::vector<double>	finalx;
    std::vector<double>	finalxel;
    std::vector<double>	finalxeh;


    for(Int_t i = 0; i < B->GetN() ; ++i)

        {
            Double_t Ax,Bx,Ay,By,Cx,Cy,Cyeh,Cyel,Cxeh,Cxel,Byeh,Byel,Ayeh,Ayel;
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
    for (unsigned int j=0; j<finalx.size(); j++)
        {
            this->SetPoint(j,finalx[j],	finaly[j]);
            this->SetPointError(j,finalxel[j],	finalxeh[j],	finalyel[j],	finalyeh[j]);

        }


}
#endif

