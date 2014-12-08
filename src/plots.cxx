//#include  "Code/Helpers.h"
//#include  "Code/Cuts.h"
//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
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
#include "Helpers.h"

#include <map>


double chi2_TH1(TH1D* A, TH1D* B)
{
	double chi2=0;
	int N=0;
for (int i=0;i<A->GetNbinsX();i++)	if (pow(A->GetBinError(i),2)+pow(B->GetBinError(i),2)>0.000001)
{N++; chi2+=pow(A->GetBinContent(i)-B->GetBinContent(i),2)/(pow(A->GetBinError(i),2)+pow(B->GetBinError(i),2));}
	return chi2/N;
	
}	



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
#endif
}

#ifndef __CINT__
int main(int argc, char** argv)
#else
int plots()
#endif
{	
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;
	
	std::vector<std::string> GENERATORS;	
	std::vector<std::string> generators;
		
	std::vector<std::string> algorithms;	
	std::vector<std::string> ALGORITHMS;
	
	tokenize("PYTHIA8:SHERPA",":",GENERATORS); 
	tokenize("pythia8:sherpa",":",generators); 

    tokenize("DURHAM:JADE",":",ALGORITHMS); 
    tokenize("durham:jade",":",algorithms);



        if (argc<2) {printf("Not enough arguments\n"); exit(1);}


int ENERGY;

sscanf(argv[1],"%i",&ENERGY);
//=189;
  //  ENERGY=130;

std::map<std::pair<float,std::string>,int> yodaconv;
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(130.0,"durham"),19));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(161.0,"durham"),20));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(172.0,"durham"),21));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(183.0,"durham"),22));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(189.0,"durham"),23));


yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(130.0,"jade"),10));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(161.0,"jade"),11));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(172.0,"jade"),12));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(183.0,"jade"),13));
yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(189.0,"jade"),14));


std::vector < std::string > ofiles;
for (int j=0;j<GENERATORS.size();j++) ofiles.push_back(std::string(TString(Form("output/PREDICTION%s_%i.root",GENERATORS[j].c_str(),ENERGY)).Data()));
ofiles.push_back(std::string(TString(Form("output/OPAL_%i.root",ENERGY)).Data()));
ofiles.push_back(std::string(TString("output/JADE_OPAL_2000_S4300807a.root").Data()));

for (int j=0;j<ofiles.size();j++) {
TFile* F = new TFile(ofiles.at(j).c_str());	
puts(ofiles.at(j).c_str());
TIter next(F->GetListOfKeys());
TKey *key;
while ((key = (TKey*)next())) {
TObject *obj = key->ReadObj();
if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   ); 
	if (fHMap.find(std::string(key->GetName()))!=fHMap.end()) if (fHMap.at(std::string(key->GetName())))  fHMap[std::string(key->GetName())]->SetDirectory(0); 
	}
if ( obj->IsA()->InheritsFrom( "TGraph" ) ) { fGMap.insert(std::pair<std::string,TGraphAsymmErrors*> (std::string(key->GetName()) ,(TGraphAsymmErrors*)obj)   );  
	//fGMap[std::string(key->GetName())]->SetDirectory(0); 
	}
if(key) puts(key->GetName());
}	
F->Close();	
}	

set_my_style();
system("mkdir -p plots");
for (int r=0;r<algorithms.size();r++)
{
std::string ALGORITHM=ALGORITHMS[r];    
std::string algorithm=algorithms[r];
puts(algorithm.c_str());
for (int j=0;j<GENERATORS.size();j++)
{
TCanvas* C= new TCanvas("","",1024*2,768*2);
C->SetLogx();
C->Divide(2,3);
for (int i=0;i<5;i++)
{
C->cd(i+1);
gPad->SetLogx();
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetTitle(Form("Integrated %i-jet rate with %s algorithm (%iGeV);x;Ratio",i+2,ALGORITHM.c_str(),ENERGY));

for (int k=0;k<fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetNbinsX();k++)
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetBinLabel(k+1,"");

fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->Draw();
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineColor(kRed);
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetRangeUser(0.00001,1);
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetRangeUser(0,1.3);


for (int k=0;k<fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[j].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->GetNbinsX();k++)
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[j].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetBinLabel(k+1,"");

fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[j].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Draw("same");

ScaleGraph(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],0.01,2);
fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("SAMEPE");

TLegend* A= new TLegend(0.1,0.9,0.30,0.75);
A->AddEntry(fHMap[std::string(TString(Form("H_corrected_durham_%iGeV_JETR%i",ENERGY,i+2)).Data())],"Data, new");
A->AddEntry(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"Data, old","P");
A->AddEntry(fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[j].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],Form("%s prediction",generators[j].c_str()));
A->Draw();
double c2=chi2_TH1(fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[j].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]);
printf("%f\n",c2);
}
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generators[j].c_str()));
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generators[j].c_str()));
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generators[j].c_str()));
C->Delete();
}
}

}
