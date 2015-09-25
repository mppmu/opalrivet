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

#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h"
#include "TAdvancedGraph.h"





int main(int argc, char* argv[])
{
    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    for (int i=4; i<argc; i++)
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
    std::vector<std::string> generators=return_tokenize(std::string(argv[3]),":");
    //=return_tokenize("corrected:mcall:truesignal:data:olddata:manipcorrected:pythia8:herwig++:sherpa",":");
    
    int types[2];types[0]=0; types[1]=0;
    
    if(std::find(generators.begin(), generators.end(), std::string("corrected")) != generators.end())types[0]++;
    if(std::find(generators.begin(), generators.end(), std::string("olddata")) != generators.end())types[0]++;
    if(std::find(generators.begin(), generators.end(), std::string("pythia8")) != generators.end())types[0]++;
    if(std::find(generators.begin(), generators.end(), std::string("herwig++")) != generators.end())types[0]++;
    if(std::find(generators.begin(), generators.end(), std::string("acceptancesignal")) != generators.end())types[0]++;
    if(std::find(generators.begin(), generators.end(), std::string("data")) != generators.end()) types[1]++;
    if(std::find(generators.begin(), generators.end(), std::string("mcall")) != generators.end()) types[1]++;
    if(std::find(generators.begin(), generators.end(), std::string("truesignal")) != generators.end())types[1]++;
    
    if (types[0]&&types[1]) {printf("Incompatible list of histos\n"); exit(2);}
    
    std::string energy=std::string(argv[2]);
    std::string nick=std::string(argv[1]);
    std::vector<std::string>  quantities=return_tokenize("JETR2:JETR3:JETR4:JETR5:JETR6:1-T:T:T-Maj:T-Min:A:CP:MH:S:O:BT:BW:D2:MH2:JTE0:DP",":");
//",":");

    TFile* F= new TFile(("output/plots_"+nick+"_"+energy+".root").c_str(),"RECREATE");
    F->cd();

    for (std::vector<std::string>::iterator algorithm=algorithms.begin(); algorithm!=algorithms.end(); algorithm++)
        {


            TCanvas* CH=new TCanvas((*algorithm+"_"+energy).c_str(),(*algorithm+"_"+energy).c_str(),4*1024,4*768);
            const int M=sqrt(quantities.size())+1;
            std::vector<std::string> Q=  quantities;
            for (int j=Q.size(); j<M*M; j++) Q.push_back(Form("Placeholder_%i",j));
            //TPad *pads[2*M*M];
            std::map<std::string,TPad* > pads;
            for (int z=0; z<M*M; z++)
                {
                    int i=z%M;
                    int j=z/M;
                    std::string qname=std::string("QPAD_")+Q[z];
                    std::string rname=std::string("RPAD_")+Q[z];
                    pads.insert(std::pair<std::string,TPad* >(qname,new TPad(qname.c_str(),Q[z].c_str(),1.0*i/M,(j+0.35)/M,(i+1.0)/M,(j+1.0)/M)));
                    pads[qname]->SetBottomMargin(0);
                    pads[qname]->SetRightMargin(0.05);
                    pads[qname]->Draw();
                    pads.insert(std::pair<std::string,TPad* >(rname,new TPad(rname.c_str(),Q[z].c_str(),1.0*i/M,(j+0.0)/M,(i+1.0)/M,(j+0.35)/M)));
                    pads[rname]->SetTopMargin(0);
                               pads[rname]->SetRightMargin(0.05);
                    pads[rname]->SetBottomMargin(0.25);
                    pads[rname]->Draw();
                }


            //int icanH=0;

            gStyle->SetOptStat(0);
            for (std::vector<std::string>::iterator quantity=Q.begin(); quantity!=Q.end(); quantity++)
                {
                    int color=0;
                    std::string hoption="";
                    std::string goption="APLE";
                    Color_t usecolors[5]= {kBlue,kRed,kGreen,kYellow,kBlack};
                    pads[std::string("QPAD_")+*quantity]->cd();
                    pads[std::string("QPAD_")+*quantity]->SetLogx();
                    pads[std::string("RPAD_")+*quantity]->SetLogx();


                    TLegend* LH= new TLegend(0.72,0.68,0.95,0.9);
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



                                            fHMap[name]->SetTitle(Form(";;#frac{1}{#sigma}#frac{d#sigma}{d%s}",quantity->c_str()));
                                            fHMap[name]->Draw(hoption.c_str());

                                            fHMap[name]->GetYaxis()->SetTitleSize(0.08);
                                            fHMap[name]->GetYaxis()->SetTitleOffset(0.45);


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
                                            if (types[0]) if (quantity->find("JETR")!=std::string::npos) fHMap[name]->GetYaxis()->SetRangeUser(-0.1,1.35);
                                            if (quantity->find("JETR")!=std::string::npos) fHMap[name]->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                            fHMap[name]->SetLineColor(usecolors[color%4]);
                                            fHMap[name]->SetMarkerStyle(kFullCircle);
                                            fHMap[name]->SetMarkerSize(1.1);
                                            fHMap[name]->SetMarkerColor(usecolors[color%4]);

                                            LH->AddEntry(fHMap[name],(*quantity+" "+*generator).c_str(),"AP");
                                            if (fHMap.find(name+"_systematics")!=fHMap.end())
                                                LH->AddEntry(fHMap[name+"_systematics"],(*quantity+" "+*generator+"Systematics").c_str(),"AP");
                                            hoption="same";


                                            if (name!=name0)
                                                {
                                                    TH1D* temp=(TH1D*)fHMap[name]->Clone();
                                                    temp->Divide(fHMap[name0]);
                                                    pads[std::string("RPAD_")+*quantity]->cd();
                                                    temp->Draw(hoption.c_str());
                                                    temp->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                                    if (quantity->find("JETR")!=std::string::npos) temp->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                                    temp->GetYaxis()->SetRangeUser(0.05,1.95);
                                                    
                                                    
                                                 temp->GetYaxis()->SetLabelSize(0.09);
                                                temp->GetXaxis()->SetLabelSize(0.09);                                                
                                                temp->GetXaxis()->SetTitleSize(0.10);
                                                    
                                                temp->GetYaxis()->SetRangeUser(0.05,1.95);
                                                temp->GetXaxis()->SetTitle(quantity->c_str());
                                                temp->GetYaxis()->SetTitle();
                                                    

                                                    TF1 *fa1 = new TF1("fa1","1",0.000001*sqrt(10),100);
                                                    fa1->SetLineColor(usecolors[0]);
                                                    fa1->DrawClone("same+");
                                                    pads[std::string("QPAD_")+*quantity]->cd();
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
											printf("%s %s %i %i\n",name.c_str(),fGMap[name]->GetTitle(),types[0],types[1]);
                                             if (types[0]) fGMap[name]->SetTitle(";y_{cut};Fraction");
                                             if (types[1]) {fGMap[name]->SetTitle(";y_{cut};Counts");
                                            if (name.find("acceptance")!=std::string::npos) fGMap[name]->SetTitle(";y_{cut};Acceptance");
										              }  if (algorithm->find("siscone")!=std::string::npos) 
                                            {fGMap[name]->SetTitle(";E_{cut};Counts");
                                            if (name.find("acceptance")!=std::string::npos) fGMap[name]->SetTitle(";E_{cut};Acceptance");
										              }  
                                            
                                            
                                            printf("%s %s %i %i\n",name.c_str(),fGMap[name]->GetTitle(),types[0],types[1]);
                                            
                                            fGMap[name]->Draw(goption.c_str());
                                            fGMap[name]->GetHistogram()->GetYaxis()->SetTitleSize(0.08);
                                            fGMap[name]->GetHistogram()->GetYaxis()->SetTitleOffset(0.45);
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
                                            if (algorithm->find("siscone")!=std::string::npos)   fGMap[name]->GetHistogram()->GetXaxis()->SetRangeUser(1.0,100);
                                            if (algorithm->find("siscone")!=std::string::npos)  fGMap[name]->GetHistogram()->GetXaxis()->SetLimits(1.0,100);
                                            if (algorithm->find("siscone")!=std::string::npos)   fGMap[name]->GetXaxis()->SetRangeUser(1.0,100);
                                            if (algorithm->find("siscone")!=std::string::npos)  fGMap[name]->GetXaxis()->SetLimits(1.0,100);

                                            if (types[0]) fGMap[name]->GetYaxis()->SetRangeUser(-0.1,1.55);
                                            if (types[0])  if (*algorithm=="antikt") fGMap[name]->GetYaxis()->SetRangeUser(-0.1,1.95);
                                            fGMap[name]->SetLineColor(usecolors[color%5]);
                                            fGMap[name]->SetMarkerStyle(kFullCircle);
                                            fGMap[name]->SetMarkerSize(1.1);
                                            fGMap[name]->SetMarkerColor(usecolors[color%5]);
                                                                           

                                            {

                                                pads[std::string("RPAD_")+*quantity]->cd();
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
                                                   
                                                   
                                                temp->GetHistogram()->GetYaxis()->SetLabelSize(0.09);
                                                temp->GetHistogram()->GetXaxis()->SetLabelSize(0.09);                                                
                                                temp->GetHistogram()->GetXaxis()->SetTitleSize(0.10);
                                                
                                                temp->GetHistogram()->GetYaxis()->SetRangeUser(0.05,1.95);
                                                temp->GetHistogram()->GetXaxis()->SetTitle("y_{cut}");
                                                temp->GetHistogram()->GetYaxis()->SetTitle();
                                                if (algorithm->find("siscone")!=std::string::npos) { temp->GetHistogram()->GetXaxis()->SetLimits(1.0,100);  temp->GetHistogram()->GetXaxis()->SetTitle("E_{cut}");}
                                                if (algorithm->find("siscone")!=std::string::npos) { temp->GetHistogram()->GetXaxis()->SetRangeUser(1.0,100);  temp->GetHistogram()->GetXaxis()->SetTitle("E_{cut}");}

                                                if (name==name0)
                                                    {
                                                        temp->GetHistogram()->Draw("AXIS");


                                                        TF1 *fa1;

                                                        if (algorithm->find("siscone")!=std::string::npos) fa1 = new TF1("fa1","1",1.0,100);
                                                        else
                                                            fa1 = new TF1("fa1","1",0.000001*sqrt(10),1);
                                                        fa1->SetLineColor(usecolors[0]);
                                                        fa1->Draw("same+");
                                                    }
                                                else
                                                    temp->Draw("SAMELP");

                                                pads[std::string("QPAD_")+*quantity]->cd();


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

                   // icanH++;
                }
            CH->Write();
            CH->SaveAs(("output/plots_"+nick+"_"+energy+"_"+*algorithm+".pdf").c_str());
            CH->SaveAs(("output/plots_"+nick+"_"+energy+"_"+*algorithm+".png").c_str());
            CH->SaveAs(("output/plots_"+nick+"_"+energy+"_"+*algorithm+".root").c_str());
        }
    F->Close();
}
