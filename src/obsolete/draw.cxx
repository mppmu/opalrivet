#include "Helpers.h"

std::map<std::string,TH1D*> fHMap;
std::map<std::string,TGraphAsymmErrors*> fGMap;

void Init(std::string t)
{
    TFile* F = new TFile(t.c_str());

    TIter next(F->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
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
    EColor color[]= {kRed,kGreen,kBlue,kYellow,kOrange};


    TCanvas* C1= new TCanvas();
    C1->cd();
    C1->SetLogx();
    for (i=2; i<7; i++)
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



    theApp->Run();
}


