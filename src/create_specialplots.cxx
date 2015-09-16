#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h"
#include "TAdvancedGraph.h"





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













//////////////




  TCanvas* CH=new TCanvas("specialplots","specialplots",4*1024,4*768);
            int M=2;//sqrt(quantities.size())+1;
            TPad *pads[2*M*M];
            for (int z=0; z<M*M; z++)
                {
                    int i=z%M;
                    int j=z/M;
                    pads[2*z]=new TPad("q1","q2",1.0*i/M,(j+0.0)/M,(i+1.0)/M,(j+1.0)/M);
                    //pads[2*z]->SetBottomMargin(0);
                    pads[2*z]->Draw();
                    //pads[2*z+1]=new TPad("r1","r2",1.0*i/M,(j+0.0)/M,(i+1.0)/M,(j+0.3)/M);
                    //pads[2*z+1]->SetTopMargin(0);
                    //pads[2*z+1]->Draw();
                }


            int icanH=0;
std::vector<std::string> names[5];

names[0].push_back(std::string("H_truesignalp_durham_161GeV_1-T"));

names[1].push_back(std::string("H_pythia8_durham_161GeV_1-T"));
names[2].push_back(std::string("H_mcall_durham_161GeV_1-T"));
names[2].push_back(std::string("H_data_durham_161GeV_1-T"));
names[3].push_back(std::string("H_acceptancesignal_durham_161GeV_1-T"));



            gStyle->SetOptStat(0);
      //      for (std::vector<std::string>::iterator quantity=quantities.begin(); quantity!=quantities.end(); quantity++)
             for( icanH=0;icanH<4;icanH++)   
             {
					std::string *quantity=new std::string("1-T");
					std::string *algorithm=new std::string("durham");
					std::string *generator=new std::string("corrected");
					//std::string energy=std::string("161");
					
                    int color=0;
                    std::string hoption="";
                    std::string goption="APLE";
                    Color_t usecolors[5]= {kBlue,kRed,kGreen,kYellow,kBlack};
                    pads[2*icanH]->cd();
                    pads[2*icanH]->SetLogx();
                    //pads[2*icanH+1]->SetLogx();


                    TLegend* LH= new TLegend(0.75,0.68,0.95,0.9);
                    color=0;


                                
                                    //std::string name=names[icanH];//	"H_"+*generator+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    
                                    std::string name0=	"H_"+generators[0]+"_"+*algorithm+"_"+energy+"GeV_"+*quantity;
                                    
                                    for (std::vector<std::string>::iterator name=names[icanH].begin(); name!=names[icanH].end();name++)
                                    {
                                    if (fHMap.find(*name)!=fHMap.end())
                                        {
                                                  if (name->find("acceptan")==std::string::npos)  DivideByBinWidth(*fHMap[*name]);
                                            fHMap[*name]->SetTitle(";;Fraction");
                                            fHMap[*name]->Draw(hoption.c_str());
                                            fHMap[*name]->Draw("ASAME");
                                            fHMap[*name]->GetXaxis()->SetRangeUser(0.000001*sqrt(10),1);
                                            fHMap[*name]->SetLineColor(usecolors[color%4]);
                                            fHMap[*name]->SetMarkerStyle(kFullCircle);
                                            fHMap[*name]->SetMarkerSize(1.1);
                                            fHMap[*name]->SetMarkerColor(usecolors[color%4]);
                                            LH->AddEntry(fHMap[*name],name->c_str(),"AP");
                                            hoption="same";




                                        }
                                    else printf("Not Found histo: %s\n",name->c_str());
                                    
                                    color++;
								}
                        LH->DrawClone();        
                       } 

CH->SaveAs("1.png");
CH->SaveAs("1.root");

    F->Close();
}
