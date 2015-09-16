#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h"
#include "TAdvancedGraph.h"

void DivideByBinWidth(TH1D& H)
{
    double y,ye,w;
    for (int i=1; i<H.GetNbinsX(); i++)
        {
            y=H.GetBinContent(i);
            ye=H.GetBinError(i);
            w=H.GetBinWidth(i);
            H.SetBinContent(i,y/w);
            H.SetBinError(i,ye/w);
        }

}




int main(int argc, char* argv[])
{
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    for (int i=2; i<argc; i++)
        {
            TFile* type_fFile= new TFile(argv[i], "READ");
            type_fFile->cd();
            TIter next(type_fFile->GetListOfKeys());
            TKey *key;
            while ((key = (TKey*)next()))
                {
                    TObject *obj = key->ReadObj();
                    if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj  ) );  fHMap[std::string(key->GetName())]->SetDirectory(0); }
                    if ( obj->IsA()->InheritsFrom( "TGraph" ) )
                        {
                            fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
                        }
                }
            type_fFile->Close();
        }
    std::vector<std::string> algorithms=return_tokenize(ALGORITHMS,":");
    std::vector<std::string> generators=return_tokenize("corrected:olddata:manipcorrected:pythia8:herwig++:sherpa",":");
    std::string energy=std::string(argv[1]);
    std::vector<std::string>  quantities=return_tokenize("JETR2:JETR3:JETR4:JETR5:JETR6:1-T:T:T-Maj:T-Min:A:CP:MH:S:O:BT:BW:D2:MH2:JTE0:DP",":");
//",":");

    TFile* F= new TFile(("output/plots_"+energy+".root").c_str(),"RECREATE");
    F->cd();

    for (std::vector<std::string>::iterator algorithm=algorithms.begin(); algorithm!=algorithms.end(); algorithm++)
        {


            TCanvas* CH=new TCanvas((*algorithm+"_"+energy).c_str(),(*algorithm+"_"+energy).c_str(),4*1024,4*768);
            int M=sqrt(quantities.size())+1;
            std::vector<std::string> Q=  quantities;
            for (int j=Q.size(); j<M*M; j++) Q.push_back(Form("Placeholder_%i",j));
            TPad *pads[2*M*M];
            for (int z=0; z<M*M; z++)
                {
                    int i=z%M;
                    int j=z/M;
                    pads[2*z]=new TPad(Form("QPAD_%s",Q[z].c_str()),Form("%s",Q[z].c_str()),1.0*i/M,(j+0.3)/M,(i+1.0)/M,(j+1.0)/M);
                    pads[2*z]->SetBottomMargin(0);
                    pads[2*z]->Draw();
                    pads[2*z+1]=new TPad(Form("RPAD_%s",Q[z].c_str()),Form("%s",Q[z].c_str()),1.0*i/M,(j+0.0)/M,(i+1.0)/M,(j+0.3)/M);
                    pads[2*z+1]->SetTopMargin(0);
                    pads[2*z+1]->Draw();
                }


            int icanH=0;

            gStyle->SetOptStat(0);
            for (std::vector<std::string>::iterator quantity=quantities.begin(); quantity!=quantities.end(); quantity++)
                {
                    int color=0;
                    std::string hoption="";
                    std::string goption="APLE";
                    Color_t usecolors[5]= {kBlue,kRed,kGreen,kYellow,kBlack};
                    pads[2*icanH]->cd();
                    pads[2*icanH]->SetLogx();
                    pads[2*icanH+1]->SetLogx();


                    TLegend* LH= new TLegend(0.75,0.68,0.95,0.9);
                    color=0;

                    if (//(*algorithm=="durham"||*algorithm=="jade"||*algorithm=="eecambridge"||*algorithm=="siscone")||
                        (quantity->find("JETR")==std::string::npos)
                    )

                        {
                            for (std::vector<std::string>::iterator generator=generators.begin(); generator!=generators.end(); generator++)
                                {
                                    std::string name=	"H_"+*generator+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    std::string name0=	"H_"+generators[0]+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    if (fHMap.find(name)!=fHMap.end())
                                        {

                                            if (quantity->find("JETR")==std::string::npos)
                                                if (name.find("manip")==std::string::npos)
                                                    DivideByBinWidth(*fHMap[name]);



                                            fHMap[name]->SetTitle(";;Fraction");
                                            fHMap[name]->Draw(hoption.c_str());




                                            if (fHMap.find(name+"_systematics")!=fHMap.end())
                                                {
                                                    fHMap[name+"_systematics"]->Draw("E4SAME");


                                                    fHMap[name+"_systematics"]->SetLineColor(usecolors[color%4]);

                                                    fHMap[name+"_systematics"]->SetMarkerSize(1.1);
                                                    fHMap[name+"_systematics"]->SetMarkerColor(usecolors[color%4]);
                                                    fHMap[name+"_systematics"]->SetFillColor(usecolors[color%4]);

                                                }
                                            fHMap[name]->Draw("ASAME");

                                            fHMap[name]->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                            if (quantity->find("JETR")!=std::string::npos) fHMap[name]->GetYaxis()->SetRangeUser(-0.1,1.35);
                                            if (quantity->find("JETR")!=std::string::npos) fHMap[name]->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                            fHMap[name]->SetLineColor(usecolors[color%4]);
                                            fHMap[name]->SetMarkerStyle(kFullCircle);
                                            fHMap[name]->SetMarkerSize(1.1);
                                            fHMap[name]->SetMarkerColor(usecolors[color%4]);

                                            LH->AddEntry(fHMap[name],(*quantity+" "+*generator).c_str(),"AP");
                                            if (fHMap.find(name+"_systematics")!=fHMap.end())
                                                LH->AddEntry(fHMap[name+"_systematics"],(*quantity+" "+*generator).c_str(),"AP");
                                            hoption="same";


                                            if (name!=name0)
                                                {
                                                    TH1D* temp=(TH1D*)fHMap[name]->Clone();
                                                    temp->Divide(fHMap[name0]);
                                                    pads[2*icanH+1]->cd();
                                                    temp->Draw(hoption.c_str());
                                                    temp->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                                    if (quantity->find("JETR")!=std::string::npos) temp->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                                    temp->GetYaxis()->SetRangeUser(0.5,1.5);
                                                    TF1 *fa1 = new TF1("fa1","1",0.000001*sqrt(10),100);
                                                    fa1->SetLineColor(usecolors[0]);
                                                    fa1->DrawClone("same+");
                                                    pads[2*icanH]->cd();
                                                }


                                        }
                                    else printf("Not Found histo: %s\n",name.c_str());
                                    color++;
                                }
                        }

                    if (//(*algorithm=="cambridge"||*algorithm=="antikt"||*algorithm=="kt")&&
                        (quantity->find("JETR")!=std::string::npos)
                    )
                        {

                            for (std::vector<std::string>::iterator generator=generators.begin(); generator!=generators.end(); generator++)
                                {
                                    std::string name=	"G_"+*generator+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    std::string name0=	"G_"+generators[0]+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    if (fGMap.find(name)!=fGMap.end())
                                        {
                                            fGMap[name]->SetTitle(";;Fraction");
                                            fGMap[name]->Draw(goption.c_str());
                                            if (fGMap.find(name+"_systematics")!=fGMap.end())
                                                {
                                                    //fGMap[name+"_systematics"]->SetMarkerStyle(kFullCircle);
                                                    fGMap[name]->SetLineColor(usecolors[color%5]);
                                                    fGMap[name+"_systematics"]->SetMarkerSize(1.1);
                                                    fGMap[name+"_systematics"]->SetMarkerColor(usecolors[color%5]);
                                                    fGMap[name+"_systematics"]->SetFillColor(usecolors[color%5]);


                                                    fGMap[name+"_systematics"]->Draw("SAMELP4");

                                                }
                                            fGMap[name]->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                            fGMap[name]->GetXaxis()->SetLimits(0.000001*sqrt(10),1);
                                            if (*algorithm=="siscone")   fGMap[name]->GetHistogram()->GetXaxis()->SetRangeUser(1.0,100);
                                            if (*algorithm=="siscone")  fGMap[name]->GetHistogram()->GetXaxis()->SetLimits(1.0,100);
                                            if (*algorithm=="siscone")   fGMap[name]->GetXaxis()->SetRangeUser(1.0,100);
                                            if (*algorithm=="siscone")  fGMap[name]->GetXaxis()->SetLimits(1.0,100);

                                            fGMap[name]->GetYaxis()->SetRangeUser(-0.1,1.35);
                                            fGMap[name]->SetLineColor(usecolors[color%5]);
                                            fGMap[name]->SetMarkerStyle(kFullCircle);
                                            fGMap[name]->SetMarkerSize(1.1);
                                            fGMap[name]->SetMarkerColor(usecolors[color%5]);

                                            {

                                                pads[2*icanH+1]->cd();
                                                TAdvancedGraph* temp=new TAdvancedGraph(fGMap[name]->GetN());
                                                temp->SetName(("clone"+name).c_str());
                                                temp->Divide(fGMap[name],fGMap[name0],false);

                                                temp->DrawClone(goption.c_str());

                                                temp->SetLineColor(usecolors[color%5]);
                                                temp->SetMarkerStyle(kFullCircle);
                                                temp->SetMarkerSize(1.1);
                                                temp->SetMarkerColor(usecolors[color%5]);


                                                temp->GetHistogram()->GetXaxis()->   SetLimits(0.000001*sqrt(10),1);
                                                temp->GetHistogram()->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);

                                                temp->GetHistogram()->GetYaxis()->SetRangeUser(0.0,2.0);
                                                if (*algorithm=="siscone")  temp->GetHistogram()->GetXaxis()->SetLimits(1.0,100);
                                                if (*algorithm=="siscone")  temp->GetHistogram()->GetXaxis()->SetRangeUser(1.0,100);

                                                if (name==name0)
                                                    {
                                                        temp->GetHistogram()->Draw("AXIS");


                                                        TF1 *fa1;

                                                        if (*algorithm=="siscone") fa1 = new TF1("fa1","1",1.0,100);
                                                        else
                                                            fa1 = new TF1("fa1","1",0.000001*sqrt(10),1);
                                                        fa1->SetLineColor(usecolors[0]);
                                                        fa1->Draw("same+");
                                                    }
                                                else
                                                    temp->Draw("SAMELP");

                                                pads[2*icanH]->cd();


                                            }
                                            //printf("<------%s %s\n",name.c_str(),name0.c_str());


                                            LH->AddEntry(fGMap[name],(*quantity+" "+*generator).c_str(),"AP");
                                            if (fGMap.find(name+"_systematics")!=fGMap.end())
                                                LH->AddEntry(fGMap[name+"_systematics"],(*quantity+" "+*generator).c_str(),"AP");
                                            goption="PLESAME";///ROOT


                                        }


                                    else printf("Not Found g: %s\n",name.c_str());
                                    color++;
                                }
                        }
                    LH->Draw();

                    icanH++;
                }
            CH->Write();
            CH->SaveAs(("output/plots_"+energy+"_"+*algorithm+".pdf").c_str());
            CH->SaveAs(("output/plots_"+energy+"_"+*algorithm+".png").c_str());
            CH->SaveAs(("output/plots_"+energy+"_"+*algorithm+".root").c_str());
        }
    F->Close();
}
