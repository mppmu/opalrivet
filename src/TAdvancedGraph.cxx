#include "TAdvancedGraph.h"

void FoldGraph(TGraphAsymmErrors* A, int N)
{
    //Here we should merge the TGraphs properly
    int i,j;
    //const int N=4;
    int oldN=A->GetN();
    int newN=A->GetN()/N;
    for (i=0; i<newN; i++)
        {
            Double_t x,y,ye_h=0,ye_l=0;
            Double_t t_y=0,t_ye_h=0,t_ye_l=0;
            for (j=N-1; j>-1; j--)
                {
                    A->GetPoint(j*newN+i,x,y);
                    ye_h=A->GetErrorYhigh(j*newN+i);
                    ye_l=A->GetErrorYlow(j*newN+i);
                    t_y+=y;
                    ye_h=sqrt(ye_h*ye_h+t_ye_h*t_ye_h);
                    ye_l=sqrt(ye_l*ye_l+t_ye_l*t_ye_l);
                }
            A->SetPoint(i,x,t_y);
            A->SetPointError(i,0,0,ye_l,ye_h);
        }
    for (i=oldN-1; i>newN-1; i--) A->RemovePoint(i);

    //}

}


void ScaleGraph(TGraphAsymmErrors* A, double k,int scaleopt=0)
{
    //Here we should merge the TGraphs properly
    int i;
    for (i=0; i<A->GetN(); i++)
        {
            Double_t x,y;
            A->GetPoint(i,x,y);
            A->SetPoint(i,x,y*k);
            if (scaleopt==2) A->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),A->GetErrorYlow(i)*(k),A->GetErrorYhigh(i)*(k));
            if (scaleopt==1) A->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),A->GetErrorYlow(i)*sqrt(k),A->GetErrorYhigh(i)*sqrt(k));
            if (scaleopt==0) A->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),A->GetErrorYlow(i),A->GetErrorYhigh(i));
            //  puts(A->GetTitle());
            //  printf("Scale   %f %f\n",x,y);
        }
}




TGraphAsymmErrors* AddGraphs(double w1,double w2,TGraphAsymmErrors* A, TGraphAsymmErrors* B, TGraphAsymmErrors* D=NULL)
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
            Double_t Ax,Bx,Ay,By,Cx,Cy,Dx,Dy,Cyeh,Cyel,Byeh,Byel,Ayeh,Ayel,Byeh_=0,Byel_=0,Ayeh_=0,Ayel_=0;
            A->GetPoint(i,Ax,Ay);
            B->GetPoint(i,Bx,By);
            if (D) D->GetPoint(i,Dx,Dy);

            Ayel=A->GetErrorYlow(i);
            Ayeh=A->GetErrorYhigh(i);

            Byel=B->GetErrorYlow(i);
            Byeh=B->GetErrorYhigh(i);

            Cx=Ax;

            Cy=w1*Ay+w2*By;

            if (w1>0) {Ayeh_=Ayeh; Ayel_=Ayel;}
            if (w1<0) {Ayeh_=Ayel; Ayel_=Ayeh;}

            if (w2>0) {Byeh_=Byeh; Byel_=Byel;}
            if (w2<0) {Byeh_=Byel; Byel_=Byeh;}


            Cyeh=sqrt(w1*w1*Ayeh_*Ayeh_+w2*w2*Byeh_*Byeh_);
            Cyel=sqrt(w1*w1*Ayel_*Ayel_+w2*w2*Byel_*Byel_);



            C->SetPoint(i,Cx,Cy);
            C->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),Cyel,Cyeh);
            //    printf("S %i %f %f %f %f\n",Cx,Cy,Cyel,Cyeh);
            if(!TMath::AreEqualRel(Ax, Bx, 1.E-15))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E1");
                    return NULL;

                }

            if(!TMath::AreEqualRel(A->GetErrorXlow(i), B->GetErrorXlow(i), 1.E-15))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E2");
                    return NULL;

                }

            if(!TMath::AreEqualRel(A->GetErrorXhigh(i), B->GetErrorXhigh(i), 1.E-15))
                {
                    puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E3");
                    return NULL;
                }
            if (D)
                {

                    if(!TMath::AreEqualRel(Ax, Dx, 1.E-15))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E4");
                            return NULL;

                        }

                    if(!TMath::AreEqualRel(A->GetErrorXlow(i), D->GetErrorXlow(i), 1.E-15))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E5");
                            return NULL;

                        }

                    if(!TMath::AreEqualRel(A->GetErrorXhigh(i), D->GetErrorXhigh(i), 1.E-15))
                        {
                            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E6");
                            return NULL;
                        }




                }

        }
    return C;



}


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

