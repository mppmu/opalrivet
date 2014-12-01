
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
#include "TColor.h"
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
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;

void Init(std::string t)
{
	TFile* F = new TFile(t.c_str());
	
	TIter next(F->GetListOfKeys());
TKey *key;
while ((key = (TKey*)next())) {
TObject *obj = key->ReadObj();
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   ); fHMap[std::string(key->GetName())]->SetDirectory(0);}
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) { fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   ); }
}


F->Close();	
	
}	



int main(int argc, char* argv[])
{
TApplication*  theApp= new TApplication("Analysis", &argc, argv);
set_my_style();
gStyle->SetHistFillColor(0);
Init("NEW/Output/OPAL_161.root");
Init("run/PREDICTIONPYTHIA8_161.root");
int i;
EColor color[]={kRed,kGreen,kBlue,kYellow,kOrange};


TCanvas* C1= new TCanvas();
C1->cd();
C1->SetLogx();
for (i=2;i<7;i++) 
{
std::string opt1="same";
std::string opt2="sameP";
if (i==2)   opt1="";
fHMap[Form("H_corrected_durham_161GeV_JETR%i",i)]->SetLineColor(color[i-2]);
fHMap[Form("H_corrected_durham_161GeV_JETR%i",i)]->Draw(opt1.c_str()); 
fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]->SetLineColor(color[i-2]);
fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]->SetMarkerColor(color[i-2]);
fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]->SetMarkerSize(0.7);
fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]->SetMarkerStyle(kCircle);
fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]->Draw(opt2.c_str()); 
}

/*
TCanvas* C2= new TCanvas();
C2->cd();
C2->SetLogx();
for (i=2;i<7;i++) 
{
std::string opt1="same";
std::string opt2="sameP";
if (i==2)   opt1="APLE";
fGMap[Form("G_corrected_antikt_161GeV_JETR%i",i)]->SetLineColor(color[i-2]);
fGMap[Form("G_corrected_antikt_161GeV_JETR%i",i)]->Draw(opt1.c_str()); 
fGMap[Form("G_predictionpythia8_antikt_161GeV_JETR%i",i)]->SetLineColor(color[i-2]);
fGMap[Form("G_predictionpythia8_antikt_161GeV_JETR%i",i)]->SetMarkerColor(color[i-2]);
fGMap[Form("G_predictionpythia8_antikt_161GeV_JETR%i",i)]->SetMarkerSize(0.7);
fGMap[Form("G_predictionpythia8_antikt_161GeV_JETR%i",i)]->SetMarkerStyle(kCircle);
fGMap[Form("G_predictionpythia8_antikt_161GeV_JETR%i",i)]->Draw(opt2.c_str()); 
}

*/

theApp->Run();
}


//for (i=2;i<6;i++) chi2+=GetChi2(REF_fHMap[Form("H_corrected_durham_161GeV_JETR%i",i)],fHMap[Form("H_predictionpythia8_durham_161GeV_JETR%i",i)]);
