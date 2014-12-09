//#include  "Code/Helpers.h"
//#include  "Code/Cuts.h"
//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
#ifndef ZROOT_H
#define ZROOT_H
#include <TH2.h>
#include <TColor.h>
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
#include "TH1D.h"
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
#include <TH1D.h>
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

gStyle->SetLegendBorderSize(0); 

    gStyle->SetStatColor(kWhite);

    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);

    gStyle->SetTitleFillColor(kWhite);

#define ROMAN
#ifdef ROMAN
    gStyle->SetTitleFont(22,"X");
    gStyle->SetTitleFont(22,"Y");
    gStyle->SetLabelFont(22,"X");
    gStyle->SetLabelFont(22,"Y");
    gStyle->SetTextFont(22);
#endif
}

/*
TH1D*  TGraphAsymmErrors_to_TH1D(const char* name,TGraphAsymmErrors* A)
{
	
	double* X= new double[A->GetN()+1];
	//X[0]=A->GetX()[0]-A->GetEXlow()[0];
	for (int i=0;i<A->GetN();i++)
	X[i]=A->GetX()[i]-A->GetEXlow()[i];
		X[A->GetN()]=A->GetX()[A->GetN()-1]+A->GetEXhigh()[A->GetN()-1];
		
		
		for (int i=0;i<A->GetN()+1;i++) X[i]=X[i]*pow(10.0,-0.25/2);
	
	TH1D* Q= 	new TH1D(name,"",  A->GetN(), X);
	for (int i=0;i<A->GetN();i++)
	{
	Q->SetBinError(i+1,A->GetEYlow()[i]);
	Q->SetBinContent(i+1,A->GetY()[i]);
      }
	return Q;
	
}	
*/
TH1D*  TGraphAsymmErrors_to_TH1D_template(const char* name,TGraphAsymmErrors* A,TH1D* B,int offset=0)//STUPID YODA!
{
	
	TH1D* Q= 	(TH1D*)B->Clone(name);
	for (int i=1;i<A->GetN()+1;i++)
	{
	Q->SetBinError(i+1+offset,A->GetEYlow()[i]);
	Q->SetBinContent(i+1+offset,A->GetY()[i]);
      }
	return Q;
	
}




#ifndef __CINT__
int main(int argc, char** argv){
#else
int plots(){	
	int arg=2; char* argv[2]={"","189"};
#endif

    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TGraphAsymmErrors*> fGMap;
	
	std::vector<std::string> GENERATORS;	
	std::vector<std::string> generators;
		
	std::vector<std::string> algorithms;	
	std::vector<std::string> ALGORITHMS;
	
	tokenize("PYTHIA8:SHERPA:HERWIG++",":",GENERATORS); 
	tokenize("pythia8:sherpa:herwig++",":",generators); 

//	tokenize("PYTHIA8",":",GENERATORS); 
//	tokenize("pythia8",":",generators); 


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
	std::string generator=generators[j];
	
TCanvas* D= new TCanvas("D","D",1024*2,768*2);
D->cd(1);
D->SetLogx();
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->Draw();
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->SetLineColor(kRed);
fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->GetXaxis()->SetRangeUser(0.001,1);
//fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->GetYaxis()->SetRangeUser(0,1.3);

fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_1-T",generator.c_str(),algorithm.c_str(),ENERGY)).Data())]->Draw("same");

//ScaleGraph(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],0.01,2);
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("SAMEPE");

TLegend* A0= new TLegend(0.1,0.9,0.30,0.75);
A0->AddEntry(fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())],"Data, new");
//A0->AddEntry(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"Data, old","P");
A0->AddEntry(fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_1-T",generator.c_str(),algorithm.c_str(),ENERGY)).Data())],Form("%s prediction",generator.c_str()));
A0->Draw();
D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
D->Delete();








TCanvas* C= new TCanvas("C","C",1024*2,768*2);
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


for (int k=0;k<fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->GetNbinsX();k++)
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetBinLabel(k+1,"");

fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Draw("same");

if (j==0) ScaleGraph(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],0.01,2);
fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("SAMEPE");

TLegend* A= new TLegend(0.1,0.9,0.30,0.75);
A->AddEntry(fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],"Data, new");
A->AddEntry(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"Data, old","P");
A->AddEntry(fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],Form("%s prediction",generator.c_str()));
A->Draw();
double c2=chi2_TH1(fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]);
printf("%f\n",c2);
}
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
C->SaveAs(Form("plots/H_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
C->Delete();
}
}




	std::string algorithm="durham";
	std::string generator,GENERATOR;
	int i=0;
TCanvas* E= new TCanvas("E","E",1024*2,1024*2);
TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0,kWhite,0,0);
TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2,kWhite,0,0);
   pad1->SetRightMargin(0.05);
   pad1->SetTopMargin(0.05);
   pad1->SetBottomMargin(0.075);

pad1->Draw();
pad2->Draw();

EColor Colors[10]={kBlack,kRed, kBlue, kGreen};

EMarkerStyle Markers[10]={kOpenCircle,kFullCircle,kFullSquare,kFullTriangleUp};
double LineWidths[10]={3,2,2,2};
double MarkerSize[10]={1.3,1.2,1.2,1.2};

pad1->cd();
pad1->SetLogx();
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("ALPE");
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->GetXaxis()->SetRangeUser(0.000001,1);
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->GetYaxis()->SetRangeUser(0,1.25);



TH1D* HJ[GENERATORS.size()];

TH1D* H=  TGraphAsymmErrors_to_TH1D_template("HH",fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[0].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],4);
H->SetTitle(";x;1/#sigma d#sigma/dx;");
H->Draw();

H->SetLineColor(Colors[0]);
H->SetMarkerColor(Colors[0]);
H->SetMarkerStyle(Markers[0]);
H->SetMarkerSize(MarkerSize[0]);
//H->GetYaxis()->SetTitleSize(0.10);	
H->GetXaxis()->SetLabelSize(0.05);	

H->SetLineWidth(LineWidths[0]);

H->GetXaxis()->SetRangeUser(0.00001*sqrt(10),1);
H->GetYaxis()->SetRangeUser(0,1.25);
//H->GetXaxis()->SetTitleSize(0.10);	
//H->GetXaxis()->SetLabelSize(0.14);	
	

TLegend* L= new TLegend(0.13,0.87,0.45,0.65);
L->AddEntry(H,"Data");

for (int j=0;j<GENERATORS.size();j++)
{
	generator=generators[j];
	GENERATOR=GENERATORS[j];

fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Draw("SAME");
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineColor(Colors[j+1]);
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerColor(Colors[j+1]);
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerStyle(Markers[j+1]);
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerSize(MarkerSize[j+1]);
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineWidth(LineWidths[j+1]);
//fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetRangeUser(0.00001,1);
//fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetRangeUser(0,1.3);
pad2->cd();
pad2->SetLogx();

   pad2->SetRightMargin(0.05);
   pad1->SetTopMargin(0.02);
   pad2->SetBottomMargin(0.04);

HJ[j]=(TH1D*)fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Clone(Form("H%i",j));

HJ[j]->Divide(H);
HJ[j]->SetTitle(";x;Data/MC;");
if (j==0)  { HJ[j]->Draw();  
	
HJ[j]->GetXaxis()->SetRangeUser(0.00001*sqrt(10),1);
HJ[j]->GetYaxis()->SetRangeUser(0.2,1.8);
HJ[j]->GetYaxis()->SetTitleOffset(0.4);
HJ[j]->GetYaxis()->SetTitleSize(0.10);


HJ[j]->GetYaxis()->SetLabelSize(0.13);	
//HJ[j]->GetXaxis()->SetLabelFont(42);
HJ[j]->GetXaxis()->SetLabelSize(0.035);
   HJ[j]->GetXaxis()->SetTitleSize(0.0);
   HJ[j]->GetXaxis()->SetLabelSize(0.0);   
//   HJ[j]->GetXaxis()->SetTitleFont(42);
   HJ[j]->GetYaxis()->SetLabelFont(42);
   //HJ[j]->GetYaxis()->SetLabelSize(0.035);
   //HJ[j]->GetYaxis()->SetTitleSize(0.035);
//   HJ[j]->GetYaxis()->SetTitleFont(42);

	
	}else HJ[j]->Draw("SAME");
pad1->cd();
pad1->SetLogx();
L->AddEntry(fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],Form("%s prediction,   #chi^{2}/ndof=%3.2f",GENERATOR.c_str(),
chi2_TH1(
fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],
H)


));

}
L->SetTextSize(0.03);
L->Draw();



pad2->cd();
TF1* one= new TF1("1","1",0,1);
one->SetLineColor(kBlack);
one->SetLineWidth(2);
//one->GetXaxis()->SetNdivisions(57);
one->Draw("SAME");

pad1->SetTitle("");
pad2->SetTitle("");

generator="all";



E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
E->Delete();




}
