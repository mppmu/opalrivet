#ifndef ZROOT_H
#define ZROOT_H
#include <TH2.h>
#include <TStyle.h>
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  "TKey.h"

#include  <iostream>
#include  <TString.h>
#include  <TSystem.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TArrow.h>
#include  <math.h>
#include  "TEntryList.h"
#include "TProofOutputFile.h"
#include <TH2.h>
#include <TStyle.h>
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  <iostream>
#include  <TString.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TArrow.h>
#include  <math.h>
#include <TH2.h>
#include <TStyle.h>
#include "TF1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TEventList.h"
#include "TMath.h"
#include  <iostream>
#include  <TString.h>
#include  <TSystem.h>
#include  <TDatime.h>
#include  <TVector3.h>
#include  <TLorentzVector.h>
#include  <TPaveLabel.h>
#include  <TArrow.h>
#include  <math.h>
#include "TProofOutputFile.h"

#include "TApplication.h"
#include "math.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF2.h"
#include "TF1.h"
#include "TFile.h"
#include "TEllipse.h"
#include "TCanvas.h"
#include "TArrow.h"
#include "TLorentzVector.h"
#include "TStyle.h"
#include "TDSet.h"
#include "TMap.h"
#include "TLegend.h"
#include "TPaveLabel.h"
#include "TEntryList.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TTree.h"
#include "TLatex.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TChain.h"
#include "TSystem.h"
#include "TString.h"
#include "TProof.h"
#include "TEnv.h"
#include <TF1.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TH1F.h>
#include <TFile.h>
#include <TVirtualFitter.h>
#include <TError.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TMath.h>
#include <vector>
#include <cmath>
#include <cassert>

#endif

#include "Cuts.h"
#include "TFastJet.h"
#include  <map>
#include  <sstream>
#define ARRAY_PROTECT(...) __VA_ARGS__
#define H_INSERTER_DBL(a,b,c)     { const double temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(double)-1,temp); }


#define H_INSERTER_FLT(a,b,c)     { const float temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(float)-1,temp); }

#define H_INSERTER_INT(a,b,c)     { const   int temp[]=c;     H_inserter(a,b,sizeof(temp)/sizeof(int)-1,temp);   }


#define G_INSERTER_FLT(a,b,c)     { const float temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(float)-1,temp); }
#define G_INSERTER_DBL(a,b,c)     { const double temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(double)-1,temp); }

#define G_INSERTER_INT(a,b,c)     { const   int temp[]=c;     G_inserter(a,b,sizeof(temp)/sizeof(int)-1,temp);   }

#define OPT_TO_INT(a)    (256*((int)(a[0]))+(int)(a[1]))
#define OPT_TO_INT2(a,b)    (256*(int)(a)+(int)(b))
#define mpi2    0.13957018*0.13957018



enum TAnalysisType {kLEP1,kLEP2,kJADE};

static const Int_t nt_maxtrk= 501;
static const Int_t nt_maxp= 50;
static const Int_t nt_maxh= 2004;


//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
void tokenize(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
}
//http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
void replace_all(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
}

static void H_inserter(std::map<std::string,TH1D*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TH1D*>( t,new TH1D(t.c_str(),t.c_str(),s,a)));
    for (int b = 0; b < A[t]->GetNbinsX(); b++) A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b));
    //A[t]->SetBinErrorOption( TH1::EBinErrorOpt::kPoisson);
}

static void G_inserter(std::map<std::string,TGraphAsymmErrors*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TGraphAsymmErrors*>( t,new TGraphAsymmErrors(s)));
    for (int b = 0; b < s; b++) { A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b)); A[t]->SetPoint(b,a[b],0.0); }
    A[t]->SetDrawOption("APL");
    A[t]->SetTitle(t.c_str());
    A[t]->SetName(t.c_str());

}


void FoldGraph(TGraphAsymmErrors* A, int N)
{
	//Here we should merge the TGraphs properly	
	int i,j;
	//const int N=4;
	int oldN=A->GetN();
	int newN=A->GetN()/N;
	for (i=0;i<newN;i++)
	{
	Double_t x,y,ye_h=0,ye_l=0;
	Double_t t_y=0,t_ye_h=0,t_ye_l=0;
	for (j=N-1;j>-1;j--)
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
	for (i=oldN-1;i>newN-1;i--) A->RemovePoint(i);
	
	//}	

}


void ScaleGraph(TGraphAsymmErrors* A, double k,int scaleopt=0)
{
	//Here we should merge the TGraphs properly	
	int i;
	for (i=0;i<A->GetN();i++)
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
	
 if(A->GetN() != B->GetN()) {
         puts("TEfficiency::CheckBinnrams are not consistent: they have different number of bins");
	 return NULL;
      }
TGraphAsymmErrors* C;
if (!D)  C= new TGraphAsymmErrors( B->GetN()); else C=D;
if (D)  if(A->GetN() != D->GetN()) {
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
        
        if (w1>0){Ayeh_=Ayeh;Ayel_=Ayel;}
        if (w1<0){Ayeh_=Ayel;Ayel_=Ayeh;}

        if (w2>0){Byeh_=Byeh;Byel_=Byel;}
        if (w2<0){Byeh_=Byel;Byel_=Byeh;}

        
        Cyeh=sqrt(w1*w1*Ayeh_*Ayeh_+w2*w2*Byeh_*Byeh_);
        Cyel=sqrt(w1*w1*Ayel_*Ayel_+w2*w2*Byel_*Byel_);
	    
	    
	    
        C->SetPoint(i,Cx,Cy);
        C->SetPointError(i,A->GetErrorXlow(i),A->GetErrorXhigh(i),Cyel,Cyeh);
            //    printf("S %i %f %f %f %f\n",Cx,Cy,Cyel,Cyeh);
         if(!TMath::AreEqualRel(Ax, Bx, 1.E-15)) {
            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E1");
	    return NULL;
       
          }
         
         if(!TMath::AreEqualRel(A->GetErrorXlow(i), B->GetErrorXlow(i), 1.E-15)) {
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
         
              if(!TMath::AreEqualRel(Ax, Dx, 1.E-15)) {
            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E4");
	    return NULL;
       
          }
         
         if(!TMath::AreEqualRel(A->GetErrorXlow(i), D->GetErrorXlow(i), 1.E-15)) {
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
	
 if(A->GetN() != B->GetN()) {
         puts("TEfficiency::CheckBinnrams are not consistent: they have different number of bins");
	 return NULL;
      }
TGraphAsymmErrors* C;
if (!D)  C= new TGraphAsymmErrors( B->GetN()); else C=D;
if (D)  if(A->GetN() != D->GetN()) {
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
         if(!TMath::AreEqualRel(Ax, Bx, toll)) {
            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E1");
	    return NULL;
       
          }
         
         if(!TMath::AreEqualRel(A->GetErrorXlow(i), B->GetErrorXlow(i),  toll)) {
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
         
              if(!TMath::AreEqualRel(Ax, Dx,  toll)) {
            puts("TEfficiency::CheckBinnrams are not consistent: they have different bin edges: E4");
	    return NULL;
       
          }
         
         if(!TMath::AreEqualRel(A->GetErrorXlow(i), D->GetErrorXlow(i),  toll)) {
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
#ifndef SIMPLE_HELPERS_ONLY
std::string ROOT_to_YODA_name(std::string a)//FIXME. Random so far
{

std::vector<std::string> tokens;
tokenize(a,"_",tokens);
if (tokens.size()<4) return a;

     int i_d=100000;
	 int i_x=100000;
     int i_y=100000;

int iconv=0;

	int energy;
	char alg[256];

	 
	 
	 
	 sscanf(tokens.at(1).c_str(),"%s",alg);
	 sscanf(tokens.at(2).c_str(),"%iGeV",&energy);
	         std::string sname;
	         unsigned int i;
	         for (i=3;i<tokens.size();i++) {sname+=tokens.at(i);if (i!=tokens.size()-1)sname+="_";}
	 
	 int i_energy=100000;

	 switch (energy)
            {
            case 35:
                i_energy = 7;
                iconv++;
                break;
            case 44:
                i_energy = 8;
                iconv++;
                break;
            case 91:
                i_energy = 9;
                iconv++;
                break;
            case 133:
                i_energy = 10;
                iconv++;
                break;
            case 161:
                i_energy = 11;
                iconv++;
                break;
            case 172:
                i_energy = 12;
                iconv++;
                break;
            case 183:
                i_energy = 13;
                iconv++;
                break;
            case 189:
                i_energy = 14;
                iconv++;
                break;
            default:
                break;
            }

         std::string salg(alg);
         if (salg=="jade")   {iconv++; i_d=i_energy; }
         if (salg=="durham") {iconv++; i_d=9+i_energy;}
        

        if (sname=="JETR2") {iconv++; i_x=1; i_y=1;}
        if (sname=="JETR3") {iconv++; i_x=1; i_y=2;}
        if (sname=="JETR4") {iconv++; i_x=1; i_y=3;}
        if (sname=="JETR5") {iconv++; i_x=1; i_y=4;}
        if (sname=="JETR6") {iconv++; i_x=1; i_y=5;}
    
    
    
    std::stringstream axisCode;
    axisCode << "d";
    if (i_d < 10) axisCode << 0;
    axisCode << i_d;//datasetId;
    axisCode << "-x";
    if (i_x < 10) axisCode << 0;
    axisCode << i_x;//xAxisId;
    axisCode << "-y";
    if (i_y < 10) axisCode << 0;
    axisCode << i_y;//yAxisId;
    if (iconv==3) return axisCode.str();
    else return a;

    
    }	

std::string YODA_to_ROOT_name(std::string a, std::string prefix="")
{
	
return prefix+a;
}	




template <class EXA>
void OPALObs(EXA * A,std::set<std::string> options,std::string Iprefix="")
{
	
	 TH1::SetDefaultSumw2(kTRUE);
	
     std::string prefix;
     prefix=std::string("H_")+Iprefix;
	
	std::vector<std::string> tok;
	tokenize(Iprefix,"_",tok);
	std::string senergy="91";
	if (tok.size()>2)  senergy=tok.at(2); 
	replace_all(senergy,"GeV","");
	int energy=atoi(senergy.c_str());
	
	printf("Prefix %s,  %i\n", senergy.c_str(),energy);
	
	
    H_INSERTER_DBL(A->fHMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.03, 0.04, 0.05,0.07, 0.09, 0.12, 0.15, 0.22, 0.30}));
    H_INSERTER_DBL(A->fHMap,prefix+"T",     ARRAY_PROTECT({0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,0.96, 0.97, 0.98, 0.99, 1.00}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,0.30, 0.40, 0.50, 0.60}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Min", ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    H_INSERTER_DBL(A->fHMap,prefix+"A",     ARRAY_PROTECT({0.00, 0.005, 0.010, 0.015, 0.025, 0.040,0.070, 0.100}));
    H_INSERTER_DBL(A->fHMap,prefix+"CP",    ARRAY_PROTECT({0.00, 0.05, 0.08, 0.11, 0.14, 0.18, 0.22, 0.30, 0.40, 0.50, 0.60, 0.75, 1.00}));
    H_INSERTER_DBL(A->fHMap,prefix+"MH",    ARRAY_PROTECT({0.060, 0.075, 0.090, 0.110, 0.140, 0.170,0.200, 0.250, 0.300, 0.350, 0.450, 0.600}));
    H_INSERTER_DBL(A->fHMap,prefix+"S",     ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.12, 0.20,0.30, 0.50, 0.70}));
    H_INSERTER_DBL(A->fHMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,0.30, 0.40, 0.50}));
    H_INSERTER_DBL(A->fHMap,prefix+"BT",    ARRAY_PROTECT({0.000, 0.030, 0.040, 0.050, 0.060, 0.075,0.090, 0.110, 0.130, 0.160, 0.200, 0.250,0.300, 0.350}));
    H_INSERTER_DBL(A->fHMap,prefix+"BW",    ARRAY_PROTECT({0.000, 0.020, 0.030, 0.040, 0.050, 0.065,0.080, 0.100, 0.150, 0.200, 0.250, 0.300}));
    H_INSERTER_DBL(A->fHMap,prefix+"D2",    ARRAY_PROTECT({0.0003, 0.00075, 0.0013, 0.0023, 0.0040, 0.0070,0.0120, 0.0225 ,0.0400, 0.0700, 0.1300, 0.2350, 0.4000, 0.7000 ,1.0000}));
    H_INSERTER_DBL(A->fHMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08, 0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    H_INSERTER_DBL(A->fHMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5}));
    H_INSERTER_DBL(A->fHMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,0.030, 0.045, 0.070, 0.100, 0.150,0.250, 0.500, 1.000}));
  
     


    H_INSERTER_DBL(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR3",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR4",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR5",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR6",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    H_INSERTER_DBL(A->fHMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                 }));
    H_INSERTER_DBL(A->fHMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                 0.170
                                                 }));


prefix=std::string("G_")+Iprefix;

    G_INSERTER_DBL(A->fGMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.03, 0.04, 0.05,0.07, 0.09, 0.12, 0.15, 0.22, 0.30}));
    G_INSERTER_DBL(A->fGMap,prefix+"T",     ARRAY_PROTECT({0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,0.96, 0.97, 0.98, 0.99, 1.00}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,0.30, 0.40, 0.50, 0.60}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Min", ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    G_INSERTER_DBL(A->fGMap,prefix+"A",     ARRAY_PROTECT({0.00, 0.005, 0.010, 0.015, 0.025, 0.040,0.070, 0.100}));
    G_INSERTER_DBL(A->fGMap,prefix+"CP",    ARRAY_PROTECT({0.00, 0.05, 0.08, 0.11, 0.14, 0.18, 0.22, 0.30, 0.40, 0.50, 0.60, 0.75, 1.00}));
    G_INSERTER_DBL(A->fGMap,prefix+"MH",    ARRAY_PROTECT({0.060, 0.075, 0.090, 0.110, 0.140, 0.170,0.200, 0.250, 0.300, 0.350, 0.450, 0.600}));
    G_INSERTER_DBL(A->fGMap,prefix+"S",     ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.12, 0.20,0.30, 0.50, 0.70}));
    G_INSERTER_DBL(A->fGMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,0.30, 0.40, 0.50}));
    G_INSERTER_DBL(A->fGMap,prefix+"BT",    ARRAY_PROTECT({0.000, 0.030, 0.040, 0.050, 0.060, 0.075,0.090, 0.110, 0.130, 0.160, 0.200, 0.250,0.300, 0.350}));
    G_INSERTER_DBL(A->fGMap,prefix+"BW",    ARRAY_PROTECT({0.000, 0.020, 0.030, 0.040, 0.050, 0.065,0.080, 0.100, 0.150, 0.200, 0.250, 0.300}));
    G_INSERTER_DBL(A->fGMap,prefix+"D2",    ARRAY_PROTECT({0.0003, 0.00075, 0.0013, 0.0023, 0.0040, 0.0070,0.0120, 0.0225 ,0.0400, 0.0700, 0.1300, 0.2350, 0.4000, 0.7000 ,1.0000}));
    G_INSERTER_DBL(A->fGMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08, 0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    G_INSERTER_DBL(A->fGMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5}));
    G_INSERTER_DBL(A->fGMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020,0.030, 0.045, 0.070, 0.100, 0.150,0.250, 0.500, 1.000}));
  /*
    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({0.7000000E-05,
                 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,
                 0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,
                 0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,
                 0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,
                 0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140
                                                    }));
*/

switch (energy) 
{
case 91:
       G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316 , 
    0.3162278
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));
      break;

case 189:  


       G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({    6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125, 
    0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05, 
    0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({     6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125, 
    0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05, 
    0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({     6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125, 
    0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05, 
    0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({     6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125, 
    0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05, 
    0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({     6.5E-5, 8.8E-5, 1.25E-4, 2.0E-4, 3.0E-4, 4.5E-4, 6.5E-4, 8.75E-4, 0.00125, 
    0.002, 0.003, 0.0045, 0.0065, 0.00875, 0.0125, 0.02, 0.03, 0.04, 0.05, 
    0.06, 0.07, 0.08, 0.095, 0.115, 0.135, 0.16, 0.1875, 0.25
                                                    }));


      
    default:

       G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316 , 
    0.3162278
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));

    
}   



    G_INSERTER_DBL(A->fGMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                 }));
    G_INSERTER_DBL(A->fGMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                 0.170
                                                 }));




}




template <class EXA>
void JADEObs(EXA * A,std::set<std::string> options,std::string Iprefix="")
{
     std::string prefix;
     prefix=std::string("H_")+Iprefix;
	
    H_INSERTER_DBL(A->fHMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
				 0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
				 0.40, 0.50 }));
    H_INSERTER_DBL(A->fHMap,prefix+"T",     ARRAY_PROTECT({ 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
			       0.96, 0.97, 0.98, 0.99, 1.00}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
			       0.30, 0.40, 0.50, 0.60}));
    H_INSERTER_DBL(A->fHMap,prefix+"T-Min", ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
			       0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    H_INSERTER_DBL(A->fHMap,prefix+"A",     ARRAY_PROTECT({ 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
			       0.070, 0.100}));
    H_INSERTER_DBL(A->fHMap,prefix+"CP",    ARRAY_PROTECT({ 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
				0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
				1.00 }));
    H_INSERTER_DBL(A->fHMap,prefix+"MH",    ARRAY_PROTECT({0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
				0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
				0.60 }));
    H_INSERTER_DBL(A->fHMap,prefix+"S",     ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
			       0.30, 0.50, 0.70}));
    H_INSERTER_DBL(A->fHMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
			       0.30, 0.40, 0.50}));
    H_INSERTER_DBL(A->fHMap,prefix+"BT",    ARRAY_PROTECT({0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
				0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30, 
                                0.34, 0.38}));
    H_INSERTER_DBL(A->fHMap,prefix+"BW",    ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
				0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                                0.35}));
    H_INSERTER_DBL(A->fHMap,prefix+"D2",    ARRAY_PROTECT({0.000,0.001,0.002, 
                                0.004,0.006,
                                0.010,0.014,
                                0.020,0.030,0.040,
                                0.060,
                                0.100,0.140,
                                0.200,0.300}));
    H_INSERTER_DBL(A->fHMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
			       0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    H_INSERTER_DBL(A->fHMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 
			       8.5, 9.5, 10.5}));
    H_INSERTER_DBL(A->fHMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020, 
			       0.030, 0.045, 0.070, 0.100, 0.150,
			       0.250, 0.500,1.000}));
			       /*

H_INSERTER_DBL(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({
5.01187233627272462e-03,
8.70963589956080461e-03,
1.25892541179416749e-02,
1.99526231496887987e-02,
3.01995172040201605e-02,
3.98107170553497342e-02,
5.01187233627272202e-02,
6.02559586074357806e-02,
7.07945784384138022e-02,
7.94328234724281379e-02,
9.54992586021435885e-02,
1.14815362149688294e-01,
1.34896288259165359e-01,
1.58489319246111343e-01
}));

H_INSERTER_DBL(A->fHMap,prefix+"JETR3", ARRAY_PROTECT({
5.01187233627272462e-03,
8.70963589956080461e-03,
1.25892541179416749e-02,
1.99526231496887987e-02,
3.01995172040201605e-02,
3.98107170553497342e-02,
5.01187233627272202e-02,
6.02559586074357806e-02,
7.07945784384138022e-02,
7.94328234724281379e-02,
9.54992586021435885e-02,
1.14815362149688294e-01,
1.34896288259165359e-01,
1.58489319246111343e-01
}));

H_INSERTER_DBL(A->fHMap,prefix+"JETR4", ARRAY_PROTECT({
5.01187233627272462e-03,
8.70963589956080461e-03,
1.25892541179416749e-02,
1.99526231496887987e-02,
3.01995172040201605e-02,
3.98107170553497342e-02,
5.01187233627272202e-02,
6.02559586074357806e-02,
7.07945784384138022e-02,
7.94328234724281379e-02,
9.54992586021435885e-02,
1.14815362149688294e-01,
1.34896288259165359e-01,
1.58489319246111343e-01
}));

H_INSERTER_DBL(A->fHMap,prefix+"JETR5", ARRAY_PROTECT({
5.01187233627272462e-03,
8.70963589956080461e-03,
1.25892541179416749e-02,
1.99526231496887987e-02,
3.01995172040201605e-02,
3.98107170553497342e-02,
5.01187233627272202e-02,
6.02559586074357806e-02,
7.07945784384138022e-02,
7.94328234724281379e-02,
9.54992586021435885e-02,
1.14815362149688294e-01,
1.34896288259165359e-01,
1.58489319246111343e-01
}));
			       
H_INSERTER_DBL(A->fHMap,prefix+"JETR6", ARRAY_PROTECT({
5.01187233627272462e-03,
8.70963589956080461e-03,
1.25892541179416749e-02,
1.99526231496887987e-02,
3.01995172040201605e-02,
3.98107170553497342e-02,
5.01187233627272202e-02,
6.02559586074357806e-02,
7.07945784384138022e-02,
7.94328234724281379e-02,
9.54992586021435885e-02,
1.14815362149688294e-01,
1.34896288259165359e-01,
1.58489319246111343e-01
}));
			       
*/
      //Same as Donkers for Durham   -->  -2.50 .. -0.5     ; For Jade:  -2.30.. -0.80
    H_INSERTER_DBL(A->fHMap,prefix+"JETR2", ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR3",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR4",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));

    H_INSERTER_DBL(A->fHMap,prefix+"JETR5",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));


    H_INSERTER_DBL(A->fHMap,prefix+"JETR6",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));

    //<-- Same as Donkers for Durham  
    H_INSERTER_DBL(A->fHMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                 }));
    H_INSERTER_DBL(A->fHMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                 0.170
                                                 }));


prefix=std::string("G_")+Iprefix;

       G_INSERTER_DBL(A->fGMap,prefix+"1-T",   ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
				 0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
				 0.40, 0.50 }));
    G_INSERTER_DBL(A->fGMap,prefix+"T",     ARRAY_PROTECT({ 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
			       0.96, 0.97, 0.98, 0.99, 1.00}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Maj", ARRAY_PROTECT({0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
			       0.30, 0.40, 0.50, 0.60}));
    G_INSERTER_DBL(A->fGMap,prefix+"T-Min", ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
			       0.12, 0.14, 0.16, 0.20, 0.24, 0.30}));
    G_INSERTER_DBL(A->fGMap,prefix+"A",     ARRAY_PROTECT({ 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
			       0.070, 0.100}));
    G_INSERTER_DBL(A->fGMap,prefix+"CP",    ARRAY_PROTECT({ 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
				0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
				1.00 }));
    G_INSERTER_DBL(A->fGMap,prefix+"MH",    ARRAY_PROTECT({0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
				0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
				0.60 }));
    G_INSERTER_DBL(A->fGMap,prefix+"S",     ARRAY_PROTECT({ 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
			       0.30, 0.50, 0.70}));
    G_INSERTER_DBL(A->fGMap,prefix+"O",     ARRAY_PROTECT({0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
			       0.30, 0.40, 0.50}));
    G_INSERTER_DBL(A->fGMap,prefix+"BT",    ARRAY_PROTECT({0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
				0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30, 
                                0.34, 0.38}));
    G_INSERTER_DBL(A->fGMap,prefix+"BW",    ARRAY_PROTECT({0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
				0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                                0.35}));
    G_INSERTER_DBL(A->fGMap,prefix+"D2",    ARRAY_PROTECT({0.000,0.001,0.002, 
                                0.004,0.006,
                                0.010,0.014,
                                0.020,0.030,0.040,
                                0.060,
                                0.100,0.140,
                                0.200,0.300}));
    G_INSERTER_DBL(A->fGMap,prefix+"MH2",   ARRAY_PROTECT({0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
			       0.10, 0.15, 0.20, 0.25, 0.30, 0.40}));
    G_INSERTER_DBL(A->fGMap,prefix+"JTE0",  ARRAY_PROTECT({0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 
			       8.5, 9.5, 10.5}));
    G_INSERTER_DBL(A->fGMap,prefix+"DP",    ARRAY_PROTECT({0.001, 0.005, 0.010, 0.015, 0.020, 
			       0.030, 0.045, 0.070, 0.100, 0.150,
			       0.250, 0.500,1.000}));




    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316 , 
    0.3162278
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
                                                    }));

			       
			       /*
			        * 
			        *     1.0E-5, 1.33E-5, 1.78E-5, 2.37E-5, 3.16E-5, 4.22E-5, 5.62E-5, 7.5E-5,1.0E-4, 
    1.33E-4, 1.78E-4, 2.37E-4, 3.16E-4, 4.22E-4, 5.62E-4, 7.5E-4, 0.001, 0.00133, 0.00178, 
    0.00237, 0.00316, 0.00422, 0.00562, 0.0075, 0.01, 0.0133, 0.0178, 0.0237, 0.0316, 
    0.0422, 0.0562, 0.075, 0.1, 0.133, 0.178, 0.237, 0.316
			       
			       
1.000000e-05
1.330000e-05
1.780000e-05
2.370000e-05
3.160000e-05
4.220000e-05
5.620000e-05
7.500000e-05
1.000000e-04
1.330000e-04
1.780000e-04
2.370000e-04
3.160000e-04
4.220000e-04
5.620000e-04
7.500000e-04
1.000000e-03
1.330000e-03
1.780000e-03
2.370000e-03
3.160000e-03
4.220000e-03
5.620000e-03
7.500000e-03
1.000000e-02
1.330000e-02
1.780000e-02
2.370000e-02
3.160000e-02
4.220000e-02
5.620000e-02
7.500000e-02
1.000000e-01
1.330000e-01
1.780000e-01
2.370000e-01
3.160000e-01
			       
			       
    //Same as Donkers for Durham  +2 bins -->
    G_INSERTER_DBL(A->fGMap,prefix+"JETR2", ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR3",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR4",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));

    G_INSERTER_DBL(A->fGMap,prefix+"JETR5",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));


    G_INSERTER_DBL(A->fGMap,prefix+"JETR6",    ARRAY_PROTECT({0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278
                                                    }));
//<-- Same as Donkers for Durham  +2 bins

*/

    G_INSERTER_DBL(A->fGMap,prefix+"ML",    ARRAY_PROTECT({0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                 0.14, 0.16, 0.20, 0.24, 0.30, 0.40
                                                 }));
    G_INSERTER_DBL(A->fGMap,prefix+"BN",    ARRAY_PROTECT({0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                 0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
                 0.170
                                                 }));





}





#define MAX_RUNS   20

typedef struct TAnalysisInfo_ {
	double fE;
	TAnalysisType fAT;
	std::string  fNames[MAX_RUNS];
	int          fTypes[MAX_RUNS];
	int          fRunsBegin[MAX_RUNS];
	int          fRunsEnd[MAX_RUNS];
	double       fSigmas[MAX_RUNS];
	double       fLumis[MAX_RUNS];
	int          fEvents[MAX_RUNS];
}  TAnalysisInfo;


template <class EXA>
void BookHistograms(EXA * A,TAnalysisInfo B, std::string Iprefix="")
{
	std::set<std::string> foo;
	//if (B.fE>89&&B.fE<92) foo.insert("fine_jet_rate");
	if (B.fAT==kLEP1||B.fAT==kLEP2) OPALObs(A,foo,Iprefix);
	if (B.fAT==kJADE)           JADEObs(A,foo,Iprefix);
	
}	

void Count(TChain* C, TAnalysisInfo& A)
{
	for (int i=0;i<MAX_RUNS;i++) if (A.fNames[i]!="") A.fEvents[i]= C->Draw("Irun",Form("(%i<Irun)&&(Irun<%i)",A.fRunsBegin[i],A.fRunsEnd[i]));

}	


int  Match(int run, TAnalysisInfo& Z, TH1F* H)
{
for (int i=0;i<MAX_RUNS;i++) { Z.fEvents[i]= H->Integral(Z.fRunsBegin[i],Z.fRunsEnd[i]);
//printf("%s %i %i %i\n",Z.fNames[i].c_str(), Z.fEvents[i],Z.fRunsBegin[i],Z.fRunsEnd[i]);
}
for (int i=0;i<MAX_RUNS;i++) if ((Z.fRunsBegin[i]<run)&& (run<Z.fRunsEnd[i])) return i;
	return -1;
}	



/*


// Set up binning arrays:
void JADEObservable::init_TH() {
  static const FReal  bins[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12 ,
				 0.14, 0.16, 0.18, 0.20, 0.23, 0.27, 0.32,
				 0.40, 0.50 };
  binMap["1-T"]= bins;
  nbinMap["1-T"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_THM() {
  static const FReal bins[]= { 0.70, 0.78, 0.85, 0.88, 0.91, 0.93, 0.95,
			       0.96, 0.97, 0.98, 0.99, 1.00 };
  binMap["T"]= bins;
  nbinMap["T"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_TMA() {
  static const FReal bins[]= { 0.00, 0.04, 0.08, 0.12, 0.16, 0.22,
			       0.30, 0.40, 0.50, 0.60 };
  binMap["T-Maj"]= bins;
  nbinMap["T-Maj"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_TMI() {
  static const FReal bins[]= { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10,
			       0.12, 0.14, 0.16, 0.20, 0.24, 0.30 };

  binMap["T-Min"]= bins;
  nbinMap["T-Min"]= sizeof( bins )/sizeof( FReal )-1;;
}
void JADEObservable::init_A() {
  static const FReal bins[]= { 0.000, 0.005, 0.010, 0.015, 0.025, 0.040,
			       0.070, 0.100 };
  binMap["A"]= bins;
  nbinMap["A"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_CP() {                // like Pedro
  static const FReal  bins[]= { 0.00, 0.10, 0.16, 0.22, 0.28, 0.34, 0.40,
				0.46, 0.52, 0.58, 0.64, 0.72 , 0.80, 0.88 ,
				1.00 };
  binMap["CP"]= bins;
  nbinMap["CP"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_MH() {                 // like Pedro
  static const FReal  bins[]= { 0.00, 0.06, 0.10, 0.14, 0.18, 0.22, 0.26,
				0.30, 0.34, 0.38, 0.42, 0.46, 0.50, 0.55,
				0.60 };
  binMap["MH"]= bins;
  nbinMap["MH"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_S() {
  static const FReal bins[]= { 0.00, 0.02, 0.04, 0.06, 0.12, 0.20,
			       0.30, 0.50, 0.70 };
  binMap["S"]= bins;
  nbinMap["S"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_O() {
  static const FReal bins[]= { 0.00, 0.05, 0.10, 0.15, 0.20, 0.25,
			       0.30, 0.40, 0.50 };
  binMap["O"]= bins;
  nbinMap["O"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BT() {                // like Pedro
  static const FReal  bins[]= { 0.00, 0.03, 0.06, 0.08, 0.10, 0.12, 0.14,
				0.16, 0.18, 0.20, 0.22, 0.24, 0.27, 0.30, 
                                0.34, 0.38 };
  binMap["BT"]= bins;
  nbinMap["BT"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BW() {                // like Pedro
  static const FReal  bins[]= { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12,
				0.14, 0.16, 0.18, 0.20, 0.23, 0.26, 0.30,
                                0.35 };
  binMap["BW"]= bins;
  nbinMap["BW"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_D2() {                 // like Pedro
  static const FReal  bins[]= { 0.000,0.001,0.002, 
                                0.004,0.006,
                                0.010,0.014,
                                0.020,0.030,0.040,
                                0.060,
                                0.100,0.140,
                                0.200,0.300 };
  binMap["D2"]= bins;
  nbinMap["D2"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_MH2() {
  static const FReal bins[]= { 0.00, 0.01, 0.02, 0.04, 0.06, 0.08,
			       0.10, 0.15, 0.20, 0.25, 0.30, 0.40 };
  binMap["MH2"]= bins;
  nbinMap["MH2"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_JTE0() {
  static const FReal bins[]= { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 
			       8.5, 9.5, 10.5 };
  binMap["JTE0"]= bins;
  nbinMap["JTE0"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_DP() {

  static const FReal bins[]= { 0.001, 0.005, 0.010, 0.015, 0.020, 
			       0.030, 0.045, 0.070, 0.100, 0.150,
			       0.250, 0.500,1.000};
  binMap["DP"]= bins;
  nbinMap["DP"]= sizeof( bins )/sizeof( FReal )-1;
}
// JETRATE a la Mike Donkers > 91 GeV or = 91 GeV:
void JADEObservable::init_JETR() {
//   static const FReal bins[]= {
//     0.7000000E-05, 0.1300000E-04, 0.2256600E-04, 0.4068000E-04,  
//     0.7178800E-04, 0.1282120E-03, 0.2274480E-03, 0.4050120E-03,  
//     0.7196680E-03, 0.1280330E-02, 0.2276270E-02, 0.4048330E-02,  
//     0.7198470E-02, 0.1280150E-01, 0.2276450E-01, 0.4048150E-01,  
//     0.7198650E-01, 0.1280140    , 0.2276460    , 0.4048140 };
    static const FReal bins[]= {
    0.1000000E-04, 0.1333521E-04, 0.1778279E-04, 0.2371374E-04,
    0.3162278E-04, 0.4216965E-04, 0.5623413E-04, 0.7498942E-04,
    0.1000000E-03, 0.1333522E-03, 0.1778279E-03, 0.2371374E-03,
    0.3162278E-03, 0.4216965E-03, 0.5623413E-03, 0.7498942E-03,
    0.1000000E-02, 0.1333521E-02, 0.1778279E-02, 0.2371374E-02,
    0.3162278E-02, 0.4216965E-02, 0.5623413E-02, 0.7498942E-02,
    0.1000000E-01, 0.1333521E-01, 0.1778279E-01, 0.2371374E-01,
    0.3162277E-01, 0.4216965E-01, 0.5623413E-01, 0.7498942E-01,
    0.1000000    , 0.1333521    , 0.1778279    , 0.2371374    , 
    0.3162278    };
  binMap["JETR"]= bins;
  nbinMap["JETR"]= sizeof( bins )/sizeof( FReal )-1;
}

// Bins M_L, B_N as in MAFs thesis, may not be ideal for JADE:
void JADEObservable::init_ML() {
  static const FReal bins[]= { 0.00, 0.04, 0.06, 0.08, 0.10, 0.12,
                               0.14, 0.16, 0.20, 0.24, 0.30, 0.40 };
  binMap["ML"]= bins;
  nbinMap["ML"]= sizeof( bins )/sizeof( FReal )-1;
}
void JADEObservable::init_BN() {
  static const FReal bins[]= { 0.000, 0.010, 0.015, 0.020, 0.025, 0.030,
                               0.035, 0.040, 0.050, 0.060, 0.080, 0.120,
			       0.170 };
  binMap["BN"]= bins;
  nbinMap["BN"]= sizeof( bins )/sizeof( FReal )-1;
}

*/
#ifndef USE_RIVET

template <class EXA>
Float_t costt(EXA* A) { return A->Tvectc[2]; }
template <class EXA>
Float_t tdmt(EXA* A) { return A->Tdmt; }


template <class EXA>
bool LEP1Preselection(EXA* A)
{
    bool result= true;
    if( A->Icjst != MyCuts::Icjst || A->Iebst != MyCuts::Iebst ) result= false;
    if( A->Itkmh != MyCuts::Itkmh ) result= false;
    return result;
}
template <class EXA>
bool LEP1Selection(EXA* A)
{
    bool result= true;
    if( !LEP1Preselection(A) ) result= false;
    if( A->Ntkd02 < MyCuts::Ntkd02 ) result= false;
    if( costt(A) > MyCuts::costt ) result= false;
    return result;
}
template <class EXA>
bool MCNonRad(EXA* A)
{
    bool result= false;
    if( (Int_t) A->Inonr == MyCuts::Inonr ) result= true;
    return result;
}
template <class EXA>
Float_t dmt_ymerge(EXA* A, Int_t njet )
{
    if( njet > 0 && njet <= A->Nxjdmt ) return A->Yddmt[njet-1];
    else return -1;
}

#endif




template <class EXA>
void GetP(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < A->Ntrkp; itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkp[itrk][j];
    ntrack= A->Ntrkp;
    printf("ntrack=%i\n",ntrack);
    return;
}
template <class EXA>
void GetH(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    for( Int_t itrk= 0; itrk < A->Ntrkh; itrk++ ) for( Int_t j= 0; j < 4; j++ )  ptrack[itrk][j]= A->Ptrkh[itrk][j];
    ntrack= A->Ntrkh;
    return;
}

template <class EXA>
std::vector<TLorentzVector> GetH2(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    std::vector<TLorentzVector> vtlv2; 
    for( Int_t itrk= 0; itrk < A->Ntrkh; itrk++ ) 
    {

	

            vtlv2.push_back(TLorentzVector(A->Ptrkh[itrk][0],
                   A->Ptrkh[itrk][1],
                    A->Ptrkh[itrk][2],
                    A->Ptrkh[itrk][3]));
    }
    ntrack= A->Ntrkh;

    return vtlv2;
}

template <class EXA>
void GetTC(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    GetTrk(A, ptrack, maxtrack, ntrack );
    GetCls(A, ptrack, maxtrack, ntrack, ntrack );
    return;
}
template <class EXA>
void GetTrk(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{

    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
            if( A->Id02[itrk] == 0 ) continue;
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j];
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt( ptrack[ifill][3]+mpi2 );
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getTrk: array too small " << ifill << std::endl;
    ntrack= ifill;
    return;
}

template <class EXA>
void GetCls(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack, Int_t ioff )
{
    Int_t iclus;
    for( iclus= 0; iclus < TMath::Min( maxtrack, A->Nclus ); iclus++ )
        {
            ptrack[ioff+iclus][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ioff+iclus][j]= A->Pclus[iclus][j];
                    ptrack[ioff+iclus][3]+= pow( ptrack[ioff+iclus][j], 2 );
                }
            ptrack[ioff+iclus][3]= sqrt( ptrack[ioff+iclus][3] );
        }
    ntrack= ioff+iclus;
    if( A->Nclus > maxtrack )  std::cout << "Ntuple::getcls: array too small " << maxtrack << std::endl;
    return;
}

template <class EXA>
void GetMt(EXA* A, Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
    // Tracks first:
    Int_t ifill= 0;
    for( Int_t itrk= 0; (itrk < A->Ntrk)&&(ifill<maxtrack); itrk++ )
        {
         
            // Check if track is selected:
            if( A->Id02[itrk] == 0 ) continue;
            // Check if track is scaled:
            Float_t scf= 1.0;
            for( Int_t jmttrk= 0; jmttrk < A->Nmttrk; jmttrk++ )   scf= A->Mtscft[jmttrk];

            // Copy track components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Ptrk[itrk][j]*scf;
                    ptrack[ifill][3]+= pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]=sqrt(ptrack[ifill][3]+mpi2);
            
            ifill++;
        }
    if( ifill == maxtrack ) std::cout << "getMt: array too small " << ifill << std::endl;
    
    // Clusters are either killed, scaled or copied:
    for( Int_t iclus= 0; (iclus < TMath::Min( maxtrack, A->Nclus ))&&(ifill<maxtrack); iclus++ )
        {
            // Check if cluster is killed:
            bool killed= false;
            for( Int_t jmtkil= 0; jmtkil < A->Nmtkil; jmtkil++ )  if( A->Imtkil[jmtkil]-1 == iclus )  killed= true;
            if( killed ) continue;
            // Check if cluster is scaled:
            Float_t scf= 1.0;
            for( Int_t jmtcls= 0; jmtcls < A->Nmtcls; jmtcls++ )if( A->Imtcls[jmtcls]-1 == iclus ) scf= A->Mtscfc[jmtcls];

            // Copy cluster components:
            ptrack[ifill][3]= 0.0;
            for( Int_t j= 0; j < 3; j++ )
                {
                    ptrack[ifill][j]= A->Pclus[iclus][j]*scf;
                    ptrack[ifill][3]+=pow( ptrack[ifill][j], 2 );
                }
            ptrack[ifill][3]= sqrt(ptrack[ifill][3]);
            ifill++;

        }
         if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    ntrack= ifill;
    return;

}


#ifdef USE_RIVET

//A=particles
template <class EXA>
void GetMC1(EXA*A,  Float_t ptrack[nt_maxtrk][4], Int_t maxtrack, Int_t & ntrack )
{
//printf("->>>>>>>>>>>>%i\n",particles.size());
	int i;
	int ifill=0;
	for (i=0;(i<A->size())&&(ifill<maxtrack);i++)
	{
		const Rivet::FourMomentum fv = A->at(i).momentum();
		

                    ptrack[ifill][0]= fv.px();
                    ptrack[ifill][1]= fv.py();
                    ptrack[ifill][2]= fv.pz();
                    ptrack[ifill][3]= fv.E();
            ifill++;
		
	}	
	
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    ntrack= ifill;
    return;
	
	
}	

template <class EXA>
std::vector<TLorentzVector> GetMC2(EXA*A)
{
	unsigned int i;
	int ifill=0;
	int maxtrack=500;
	std::vector<TLorentzVector> vtlv2; 
	
	for (i=0;(i<A->size())&&(ifill<maxtrack);i++)
	{
		const Rivet::FourMomentum fv = A->at(i).momentum();
            vtlv2.push_back(TLorentzVector(fv.px(),
                    fv.py(),
                    fv.pz(),
                    fv.E()));
            ifill++;
		
	}	
	
    if( ifill == maxtrack )  std::cout << "Ntuple::getmt: array too small " << ifill << std::endl;
    // The End:
    //ntrack= ifill;
    return vtlv2;
	
	
}	

#endif

#include  "fastjet/ClusterSequence.hh"
#include  "fastjet/PseudoJet.hh"

 double  Thrust(std::vector<fastjet::PseudoJet> A,  TVector3& taxis)  {
	  
	  double t;
    std::vector<TVector3> jetstlv;//= new std::vector<TVector3>();
    fastjet::PseudoJet pj;
    double momsum=0;
    for( UInt_t i= 0; i < A.size(); i++ )
        {
            pj= A[i];
            TVector3 tlv( pj.px(), pj.py(), pj.pz());
            jetstlv.push_back( tlv );
        momsum+=tlv.Mag();
        }

TFastJet::_calcT(jetstlv,t,taxis);
t=1-t/momsum;
return t;
}



template <class EXA> bool Analysis_type1(EXA* A, TFastJet* tfj,  float weight,int filly=0,std::string Iprefix="")
{
//printf("Param filly=%i\n",filly);
bool PASSED=false;
std::string H_prefix=std::string("H_")+Iprefix;
std::string G_prefix=std::string("G_")+Iprefix;
    int j;

    if (tfj->GetClusterSequence())
        {

			
            PASSED=true;
            
						 A->fHMap[H_prefix+"1-T"]->Fill(tfj->fThrust,weight);


            
            
            
            int filly=1;
            std::vector<double> ycuts;
          //  std::vector<std::pair<double,double> > bounds;
            ycuts.push_back(1.0);
            for ( j=0; j<4; j++)  ycuts.push_back(tfj->GetClusterSequence()->exclusive_ymerge_max(2+j));  //y_{n,n+1} = d_{n,n+1}/Q^2
            ycuts.push_back(0.0);
            //for ( j=0; j<5; j++)             bounds.push_back(std::pair<double,double>(ycuts.at(j),ycuts.at(j+1)));
            if (filly)  for ( j=0; j<4; j++) {/*  local_f_h_y_jet_algorithm[j]->fill(ycuts.at(j+1), weight); //FIXME */}
            for ( j=0; j<5; j++) 
            
            {
            for (int i=A->fHMap[H_prefix+Form("JETR%i",j+2)]->FindBin(ycuts.at(j+1));i<A->fHMap[H_prefix+Form("JETR%i",j+2)]->FindBin(ycuts.at(j));i++)
            A->fHMap[H_prefix+Form("JETR%i",j+2)]->Fill(A->fHMap[H_prefix+Form("JETR%i",j+2)]->GetBinCenter(i),weight);
        
        
        
        for (int i=0;i<A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetN();i++)
         if ((A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetX()[i]>ycuts.at(j+1))&&(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetX()[i]<ycuts.at(j)))
         {
         
        
	              
	              
	           double x,y;   
	      A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetPoint(i,x,y);        
	      A->fGMap[G_prefix+Form("JETR%i",j+2)]->SetPoint(i,x,y+weight);
A->fGMap[G_prefix+Form("JETR%i",j+2)]->SetPointError(i,0,0,sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetEYlow()[i],2)+weight*weight),sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",j+2)]->GetEYhigh()[i],2)+weight*weight));

	               
	               
	        }
        
        
	}
        

        }
        

        
return PASSED;
}









template <class EXA> bool Analysis_type2(EXA* A, TFastJet* tfj,  float weight,int filly=0,std::string Iprefix="")
{
bool PASSED=false;
//printf("Param filly=%i\n",filly);
std::string H_prefix=std::string("H_")+Iprefix;
std::string G_prefix=std::string("G_")+Iprefix;

    if (tfj->GetClusterSequence())
        {
            PASSED=true;
						 A->fHMap[H_prefix+"1-T"]->Fill(tfj->fThrust,weight);
            			

           
			int q=0;
            for (q=0; q<5; q++) {
              for (  int binL = 0; binL < A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetN(); binL++ )
              {
              std::vector<fastjet::PseudoJet> fdjets =  tfj->GetClusterSequence()->inclusive_jets();
              Double_t x,y;
              A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetPoint(binL,x,y);
              int fdjet=0;
              
              double  E_min = x*sqrt(tfj->GetClusterSequence()->Q2());
            
              for (  unsigned  int i = 0; i < fdjets.size(); i++) 	     {  if ( fdjets[i].E() > E_min )    fdjet++;   /* printf("%i %f %f %f\n",fdjet, x, E_min,  fdjets[i].E()); */ }
              if (fdjet==q+2)  {
A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPoint(binL,x,y+weight);
A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPointError(binL,0,0,sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight),sqrt(pow(A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(binL),2)+weight*weight));

							    }
              }        
	         }
	
	
}
        

        
return PASSED;
}




template <class EXA> bool Analysis_type3(EXA* A, TFastJet* scsJet,  float weight,int filly=0,std::string Iprefix="")
{
	//printf("Param filly=%i\n",filly);
	std::string H_prefix=std::string("H_")+Iprefix;
std::string G_prefix=std::string("G_")+Iprefix;
	
bool PASSED=false;
  //  int j;
//    int i;
int k;
        
                        for (k=0; k<7; k++)// FIXME
					{
                if (scsJet->GetClusterSequence())
                    {
PASSED=true;
                        int q=0;
                        for (q=0; q<3; q++)
                            {
                                std::vector<fastjet::PseudoJet> fdjets = scsJet->GetClusterSequence()->inclusive_jets();
                                int fdjet=0;
                                double E_min =0.077/2.0*sqrt(scsJet->GetClusterSequence()->Q2());
                                for (  unsigned  int i = 0; i < fdjets.size(); i++) 	       if ( fdjets[i].E() > E_min )    fdjet++;
                                //if (fdjet==q+2) local_f_h_R_jet_algorithm[q]->point(k).setY( local_f_h_R_jet_algorithm[q]->point(k).y()+weight);
                                        if (fdjet==q+2) A->fHMap[H_prefix+Form("JETR%i",q+2)]->AddBinContent(k+1,weight);
                                        if (fdjet==q+2) 
                                        {
                                        Double_t y,ye;
                                        Double_t x;//,xe;
                                        A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetPoint(k,x,y);
                                        ye=A->fGMap[G_prefix+Form("JETR%i",q+2)]->GetErrorY(k);
                                        A->fGMap[G_prefix+Form("JETR%i",q+2)]->SetPointError(k,x,0,y+weight,sqrt(ye*ye+weight*weight));
                                        
                                        
									    }
                                        
                            }
                    }

}


return PASSED;
}


template <class EXA> bool Analysis(EXA* A, TFastJet* scsJet,  float weight,int filly=0,std::string Iprefix="")
{
	bool ret=false;
	switch (filly) 
	{
		case 0: ret=Analysis_type1(A,scsJet, weight,filly,Iprefix); break;
		case 1: ret=Analysis_type2(A,scsJet, weight,filly,Iprefix); break;
		case 2: ret=Analysis_type3(A,scsJet, weight,filly,Iprefix); break;
		default: ret=Analysis_type1(A,scsJet, weight,filly,Iprefix); break;
	}	
	return ret;
	
}	



template <class EXA>
std::vector<TLorentzVector> GetLorentzVectors(EXA* A, const std::string & opt )
{
	std::string OPT(opt);
	OPT+="xx";
    Float_t ptrack[nt_maxtrk][4];
    Int_t ntrack;
     int ioff=0;
    switch (OPT_TO_INT2(OPT[0],OPT[1])) 
    {		

	case 	(OPT_TO_INT2('p','x')): GetP(A, ptrack, nt_maxtrk, ntrack ); break; 		
	case 	(OPT_TO_INT2('h','x')): GetH(A, ptrack, nt_maxtrk, ntrack ); break; 		
    case 	(OPT_TO_INT2('t','x')): GetTrk(A, ptrack, nt_maxtrk, ntrack ); break; 			
    case 	(OPT_TO_INT2('c','x')): GetCls(A, ptrack, nt_maxtrk, ntrack ,ioff); break; 	
    case 	(OPT_TO_INT2('t','c')): GetTC(A, ptrack, nt_maxtrk, ntrack ); break; 	    
	case 	(OPT_TO_INT2('m','t')): GetMt(A, ptrack, nt_maxtrk, ntrack ); break;
#ifdef USE_RIVET
	case 	(OPT_TO_INT2('m','c')): GetMC1(A, ptrack, nt_maxtrk, ntrack ); break; 			
#endif
	case 	(OPT_TO_INT2('x','x')): printf("Empty option %s\n",OPT.c_str()); break; 
	default:                        printf("Wrong option %s\n",OPT.c_str()); break; 
	}
    std::vector<TLorentzVector> vtlv;
    vtlv.reserve( ntrack );
    for( Int_t itrk= 0; itrk < ntrack; itrk++ ) vtlv.push_back( TLorentzVector( ptrack[itrk][0], ptrack[itrk][1], ptrack[itrk][2], ptrack[itrk][3] ));
    return vtlv;
}



#endif






#ifdef USE_RIVET



//#include "YODA/ROOTConvert.h"
#include "YODA/Histo1D.h"
#include "YODA/Histo2D.h"
#include "YODA/Histo1D.h"
#include "YODA/Profile1D.h"
#include "YODA/Scatter2D.h"

#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TVectorF.h"
#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1D.h"
#include <string>

namespace YODA
{

Histo1D* TH1toHisto1D(const TH1* th1, std::string fname)
{
    std::vector<HistoBin1D> bins;
    const TArrayD* sumw2s = th1->GetSumw2();
    Dbn1D dbn_uflow, dbn_oflow;
    double sumWtot=0, sumW2tot=0;
    for (int i = 0; i <= th1->GetNbinsX()+1; ++i)
        {
            Dbn1D dbn(static_cast<unsigned long>(th1->GetBinContent(i)), th1->GetBinContent(i), sumw2s->GetAt(i) 
                      , 0, 0);
            //th1->GetBinContent(i)*th1->GetBinCenter(i), th1->GetBinContent(i)*sqr(th1->GetBinCenter(i)));
            if (i == 0) dbn_uflow = dbn;
            else if (i == th1->GetNbinsX()+1) dbn_oflow = dbn;
            else bins.push_back(HistoBin1D(std::make_pair(th1->GetBinLowEdge(i), th1->GetBinLowEdge(i+1)), dbn));
            sumWtot += th1->GetBinContent(i);
            sumW2tot +=   sumw2s->GetAt(i);
        }
    Dbn1D dbn_tot(static_cast<unsigned long>(th1->GetEntries()), sumWtot, sumW2tot, 0, 0);

    Histo1D* rtn =new Histo1D(bins, dbn_tot, dbn_uflow, dbn_oflow,std::string("/")+fname+std::string("/")+th1->GetName(), th1->GetTitle());
    rtn->setAnnotation("XLabel", th1->GetXaxis()->GetTitle());
    rtn->setAnnotation("YLabel", th1->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+th1->GetTitle());
    return rtn;
}

Scatter2D* TH1toScatter2D(const TH1* th1, std::string fname)
{
    Scatter2D* rtn = new Scatter2D(std::string("/")+fname+std::string("/")+th1->GetName());
    for (int i = 1; i <= th1->GetNbinsX(); ++i)
        {
            const double x = th1->GetBinCenter(i);
            const double exminus = x - th1->GetBinLowEdge(i);
            const double explus = th1->GetBinLowEdge(i+1) - x;
            const double width = exminus + explus;
            rtn->addPoint(x, th1->GetBinContent(i)/width,
                          exminus, explus,
                          th1->GetBinErrorLow(i)/width, th1->GetBinErrorUp(i)/width);
        }
    rtn->setAnnotation("XLabel", th1->GetXaxis()->GetTitle());
    rtn->setAnnotation("YLabel", th1->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+th1->GetTitle());
    return rtn;
}



}

#endif















