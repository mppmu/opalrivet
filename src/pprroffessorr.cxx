
#include "TMinuit.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "math.h"
#include "TH1F.h"
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
#include "TEnv.h"
#include <TF1.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TH1F.h>
#include <TFile.h>
#include <TVirtualFitter.h>
#include <TError.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMath.h>
#include <vector>
#include <cmath>
#include <cassert>
#include "TGraphAsymmErrors.h"
#include "TKey.h"
#include "TMinuit.h"

void set_my_style()
{
gStyle->SetFrameFillColor(kWhite);
gStyle->SetPadColor(kWhite);
gStyle->SetCanvasColor(kWhite);
gStyle->SetStatColor(kWhite);
gStyle->SetTitleFillColor(kWhite);
gStyle->SetCanvasDefH(768);
gStyle->SetCanvasDefW(1024);
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
gStyle->SetMarkerColor(kBlue);
gStyle->SetMarkerSize(15);
gStyle->SetHistFillColor(kYellow);
gStyle->SetOptStat(kFALSE);

 gStyle->SetStatColor(kWhite);

 gStyle->SetCanvasBorderMode(0);     
 gStyle->SetPadBorderMode(0);

 gStyle->SetTitleFillColor(kWhite);

#ifdef ROMAN
gStyle->SetTitleFont(22,"X");
gStyle->SetTitleFont(22,"Y");
gStyle->SetLabelFont(22,"X");
gStyle->SetLabelFont(22,"Y");
gStyle->SetTextFont(22);
//gStyle->SetLegendFont(22);
#endif


}
    std::map<std::string,TH1D*> REF_fHMap;
    std::map<std::string,TGraphAsymmErrors*> REF_fGMap;

using namespace std;
//int Error;

extern void fcnk2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *x, Int_t iflag);

static int ncount = 0;
VoidFuncPtr_t dictfuncs[] = { NULL };
extern void Init();



typedef struct PARAM_
{ int    i;
char     n[40];
Double_t v;
Double_t e;
Double_t l;
Double_t u;
} par;

double GetChi2(TH1D* A,TH1D* B)
{
	
	double U=0;
	for (int i=1;i<A->GetNbinsX();i++)
	{
		double a=A->GetBinContent(i)-B->GetBinContent(i);
		double b=pow(A->GetBinError(i),2)+pow(B->GetBinError(i),2);
		if (b>0) U+=(a*a)/b;
		
	}	
	
	printf("U1= %lf\n",U);
	//U=A->Chi2Test(B,"WW");
	
	printf("U2= %lf\n",U);
	return U;
	
}	


static par IP[]= 
{
	
/*
#StringFlav:popcornSmeson = 0.50000
#StringFlav:popcornSpair = 0.50000
#StringZ:aExtraDiquark = 0.50000
#StringZ:aLund = 0.30000
#StringZ:bLund = 0.58000
*/

	
    { 0,"StringFlav:popcornSmeson", 0.50000,  0.05,  0.3,  0.7},
    { 1,"StringFlav:popcornSpair",  0.50000,  0.05,  0.3,  0.7},
    { 2,"StringZ:aExtraDiquark",    0.50000,  0.05,  0.3,  0.7},
    { 3,"StringZ:aLund",            0.30000,  0.01, 0.25,  0.35},
    { 4,"StringZ:bLund",            0.58000,  0.01, 0.50,  0.65}


};

void Init(std::string t)
{
	
	TFile* F = new TFile(t.c_str());
	
	TIter next(F->GetListOfKeys());
TKey *key;
while ((key = (TKey*)next())) {
TObject *obj = key->ReadObj();
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) REF_fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) REF_fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   );
}


//F->Close();	
	
}	



int main(int argc, char* argv[])
{
TApplication*  theApp= new TApplication("Analysis", &argc, argv);
set_my_style();
gStyle->SetHistFillColor(0);
Init("NEW/Output/OPAL_130.root");







   static Double_t p0=0;
   static Double_t p1=1;
   static Double_t p3=3;
   static Double_t p5=5;
   Int_t ierflg = 0;
   Double_t argl0[2]={ 1 ,  0.1};
Double_t argl[2]={ 100 ,  0.001};
Double_t argl2[2]={ 150 ,0.001};


   TMinuit *gMinuit = new TMinuit(5);  //initialize TMinuit with a maximum of 5 params
   gMinuit->mninit(5,6,7);
   gMinuit->SetFCN(fcnk2);

for (int i=0;i<5;i++)   gMinuit->mnparm(IP[i].i,IP[i].n,IP[i].v,IP[i].e,IP[i].l,IP[i].u,ierflg);

gMinuit->mnexcm("CALL FCN", &p1 ,1,ierflg);
gMinuit->mnexcm("SET PRINT", &p0 ,1,ierflg);
gMinuit->mnexcm("SIMPLEX", argl ,2,ierflg);
gMinuit->mnexcm("MIGRAD", argl ,2,ierflg);
gMinuit->mnexcm("MIGRAD", argl2 ,2,ierflg);

for (int i=0;i<5;i++)gMinuit->GetParameter(i,IP[i].v,IP[i].e);
theApp->Run();
}

void fcnk2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *xx, Int_t iflag)
{
	int i;
	char readdir[200];
	sprintf(readdir,"SAMPLES/TEST_%f_%f_%f_%f_%f",xx[0],xx[1],xx[2],xx[3],xx[4]);
	std::string t;
	t=std::string("mkdir -p ")+std::string(readdir);
	system(t.c_str());
	t=std::string("./")+std::string(readdir);
	
	system("cp Runpythia8.dat_bkp Runpythia8.dat");
	FILE* ff=fopen("Runpythia8.dat","a");
	for (i=0;i<5;i++) fprintf(ff,"%s=%f;\n",IP[i].n,xx[i]);
	fclose(ff);
	t=std::string("cp Runpythia8.dat ./")+std::string(readdir);
	system(t.c_str());

	/*
	 * 
	 * RUN MC
	 * 
	 */
	 system("make all_65.0");
	 t=std::string("cp run/PREDICTIONPYTHIA8_130.root  ./")+std::string(readdir);
	 system(t.c_str());
	 
	 t=std::string(readdir)+std::string("/PREDICTIONPYTHIA8_130.root");

    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;

	TFile* F = new TFile(t.c_str());
	
	TIter next(F->GetListOfKeys());
TKey *key;
while ((key = (TKey*)next())) {
TObject *obj = key->ReadObj();
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   );
}

	
	

Double_t chi2=0;

for (i=2;i<6;i++) chi2+=GetChi2(REF_fHMap[Form("H_corrected_durham_130GeV_JETR%i",i)],fHMap[Form("H_predictionpythia8_durham_130GeV_JETR%i",i)]);

f=chi2;

 t=std::string(readdir)+std::string("/chi2.txt");

FILE* fff=fopen(t.c_str(),"w");
fprintf(fff,"%f\n",chi2);
printf("CHi2======================================%f\n",chi2);
fclose(fff);

F->Close();
}

