#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
#include "TAdvancedGraph.h"
int main(int argc, char* argv[])
{
	  //TApplication* theApp = new TApplication("App", &argc, argv);
	    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
for (int i=2;i<argc;i++)
{
TFile* type_fFile= new TFile(argv[i], "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj  ) );  fHMap[std::string(key->GetName())]->SetDirectory(0); }
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) { fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   ); 
				}
        }

type_fFile->Close();
}


std::vector<std::string> algorithms=return_tokenize(ALGORITHMS,":");
std::vector<std::string> generators=return_tokenize("corrected:pythia8",":");
std::string energy=std::string(argv[1])+"GeV";
std::vector<std::string>  quantities=return_tokenize("JETR2:JETR3:JETR4:JETR5:JETR6:1-T:T:T-Maj:T-Min:A:CP:MH:S:O:BT:BW:D2:MH2:JTE0:DP",":");

TFile* F= new TFile(("output/plots_"+energy+".root").c_str(),"RECREATE");
F->cd();

for (std::vector<std::string>::iterator algorithm=algorithms.begin();algorithm!=algorithms.end();algorithm++)
{
/*
TCanvas* CG=new TCanvas((*algorithm+"G").c_str(),algorithm->c_str(),2*1024,2*768);
CG->Divide(sqrt(quantities.size())+1,sqrt(quantities.size())+1);
*/

TCanvas* CH=new TCanvas((*algorithm+"H").c_str(),algorithm->c_str(),2*1024,2*768);
CH->Divide(sqrt(quantities.size())+1,sqrt(quantities.size())+1);

int icanH=1;
int icanG=1;
gStyle->SetOptStat(0);
for (std::vector<std::string>::iterator quantity=quantities.begin();quantity!=quantities.end();quantity++)
{
int color=0;
std::string option="";
Color_t usecolors[4]={kBlue,kRed,kGreen,kYellow};


CH->cd(icanH);
gPad->SetLogx();
icanH++;


TLegend* LH= new TLegend(0.75,0.7,0.95,0.9);
color=0;
for (std::vector<std::string>::iterator generator=generators.begin();generator!=generators.end();generator++)
{
std::string name=	"H_"+*generator+"_"+*algorithm+"_"+energy+"_"+*quantity;
if (fHMap.find(name)!=fHMap.end()) 
{
fHMap[name]->SetTitle(";;Fraction");	
fHMap[name]->Draw(option.c_str());
fHMap[name]->Draw("ASAME");

    fHMap[name]->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
    fHMap[name]->GetYaxis()->SetRangeUser(0,1.25);
	fHMap[name]->SetLineColor(usecolors[color%4]);
	fHMap[name]->SetMarkerStyle(kFullCircle);
	fHMap[name]->SetMarkerSize(1.1);
	fHMap[name]->SetMarkerColor(usecolors[color%4]);

LH->AddEntry(fHMap[name],(*quantity+" "+*generator).c_str(),"AP");
option="same";
}
else puts("Not Found");
color++;
}
LH->Draw();

/*
CG->cd(icanG);
gPad->SetLogx();
icanG++;



TLegend* LG= new TLegend(0.75,0.7,0.95,0.9);
color=0;
for (std::vector<std::string>::iterator generator=generators.begin();generator!=generators.end();generator++)
{
std::string name=	"G_"+*generator+"_"+*algorithm+"_"+energy+"_"+*quantity;
if (fGMap.find(name)!=fGMap.end()) 
{
fGMap[name]->SetTitle(";;Fraction");	
fGMap[name]->Draw(option.c_str());
fGMap[name]->Draw("ASAME");

    fGMap[name]->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
    fGMap[name]->GetYaxis()->SetRangeUser(0,1.25);
	fGMap[name]->SetLineColor(usecolors[color%4]);
	fGMap[name]->SetMarkerStyle(kFullCircle);
	fGMap[name]->SetMarkerSize(1.1);
	fGMap[name]->SetMarkerColor(usecolors[color%4]);

LH->AddEntry(fGMap[name],(*quantity+" "+*generator).c_str(),"AP");
option="same";
}
else puts("Not Found");
color++;
}
LG->Draw();
*/


}

CH->Write();
CH->SaveAs(("output/plots_"+energy+"_"+*algorithm+"_H.pdf").c_str());
CH->SaveAs(("output/plots_"+energy+"_"+*algorithm+"_H.png").c_str());

/*
CG->Write();
CG->SaveAs(("output/plots_"+energy+"_"+*algorithm+"_G.pdf").c_str());
CG->SaveAs(("output/plots_"+energy+"_"+*algorithm+"_G.png").c_str());
*/


}
F->Close();
}
