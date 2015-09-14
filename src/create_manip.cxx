#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h"
#include "TAdvancedGraph.h"
int main(int argc, char** argv)
{

    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
    for (int k=3;k<argc;k++)
    {
    TFile* type_fFile= new TFile(argv[k], "READ");
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

    TFile* fFile= new TFile(argv[1], "RECREATE");
    fFile->cd();


    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        {
            std::string name(H_it->first);
            if ((name.find("h986")!=std::string::npos)
                    ||(name.find("h1860")!=std::string::npos)
                    ||(name.find("h1900")!=std::string::npos)
                    ||(name.find("h9860")!=std::string::npos)
                    ||(name.find("h8860")!=std::string::npos)
                    ||(name.find("h7860")!=std::string::npos)
                    ||(name.find("h6860")!=std::string::npos)
                    ||(name.find("h5860")!=std::string::npos)
                    ||(name.find("h4860")!=std::string::npos)
                    ||(name.find("h3860")!=std::string::npos)
                    ||(name.find("h3000")!=std::string::npos)
                    ||(name.find("h3110")!=std::string::npos)
                    ||(name.find("h3119")!=std::string::npos)
                    //||(name.find("h3318")!=std::string::npos)
                    ||(name.find("h2860")!=std::string::npos)
                    ||(name.find("h2860")!=std::string::npos)///FIXME!
               )
                {

                    replace_all(name,"h9860","H_manipcorrected_"+std::string(argv[2])+"_205GeV_");
                    //replace_all(name,"h1900","H_manipcorrected_"+std::string(argv[2])+"_205GeV_");
                    //replace_all(name,"h9","H_manipcorrected_"+std::string(argv[2])+"_202GeV_");
                    replace_all(name,"h8860","H_manipcorrected_"+std::string(argv[2])+"_196GeV_");
                    replace_all(name,"h7860","H_manipcorrected_"+std::string(argv[2])+"_192GeV_");
                    replace_all(name,"h6860","H_manipcorrected_"+std::string(argv[2])+"_189GeV_");
                    replace_all(name,"h5860","H_manipcorrected_"+std::string(argv[2])+"_183GeV_");
                    replace_all(name,"h4860","H_manipcorrected_"+std::string(argv[2])+"_172GeV_");
                    
                    replace_all(name,"h3860","H_manipcorrected_"+std::string(argv[2])+"_161GeV_");
                    replace_all(name,"h3000","H_manipdata_"+std::string(argv[2])+"_161GeV_");
                    replace_all(name,"h3110","H_manipmcsignal_"+std::string(argv[2])+"_161GeV_");
                    replace_all(name,"h3119","H_manipmcsignaltrue_"+std::string(argv[2])+"_161GeV_");
                    //replace_all(name,"h3310","H_manipmcbackgr_"+std::string(argv[2])+"_161GeV_");
                    
                    replace_all(name,"h2860","H_manipcorrected_"+std::string(argv[2])+"_136GeV_");
                    
                    replace_all(name,"h2000","H_manipcorrected_"+std::string(argv[2])+"_130GeV_");

                    replace_all(name,"h1860","H_manipcorrected_"+std::string(argv[2])+"_91GeV_");

                    /*

                                        replace_all(name,"00000","1-T");
                                        replace_all(name,"00001","T-Min");
                                        replace_all(name,"00002","T-Maj");
                                        replace_all(name,"00003","A");
                                        replace_all(name,"00004","CP");
                                        replace_all(name,"00005","MH");
                                        replace_all(name,"00006","S");
                                        replace_all(name,"00007","O");
                                        replace_all(name,"00008","BT");
                                        replace_all(name,"00009","BW");
                                        replace_all(name,"00010","D2");
                                        replace_all(name,"00011","T");
                                        replace_all(name,"00012","MH2");
                                        replace_all(name,"00013","JTE0");
                                        replace_all(name,"00014","DP");
                                        replace_all(name,"00015","JETR2");
                                        replace_all(name,"00016","JETR3");
                                        replace_all(name,"00017","JETR4");
                                        replace_all(name,"00018","JETR5");
                                        replace_all(name,"00019","JETR6");
                                        replace_all(name,"00020","ML");
                                        replace_all(name,"00021","BN");
                    */

                    //replace_all(name,"9999","admin");
                    replace_all(name,"000","1-T");
                    replace_all(name,"001","T-Min");
                    replace_all(name,"002","T-Maj");
                    replace_all(name,"003","A");
                    replace_all(name,"004","CP");
                    replace_all(name,"005","MH");
                    replace_all(name,"006","S");
                    replace_all(name,"007","O");
                    replace_all(name,"008","BT");
                    replace_all(name,"009","BW");
                    replace_all(name,"010","D2");
                    replace_all(name,"011","T");
                    replace_all(name,"012","MH2");
                    replace_all(name,"013","JTE0");
                    replace_all(name,"014","DP");
                    replace_all(name,"015","JETR2");
                    replace_all(name,"016","JETR3");
                    replace_all(name,"017","JETR4");
                    replace_all(name,"018","JETR5");
                    replace_all(name,"019","JETR6");
                    replace_all(name,"020","ML");
                    replace_all(name,"021","BN");
                    
                    
                    
                    
                    
                    
                    //if (name.find("JETR")==std::string::npos) H_it->second->Scale(0.01);

                    H_it->second->SetName(name.c_str());
                    std::string gname=name;
                    replace_all(gname,"H_","G_");
                    //std::map<std::string,TAdvancedGraph*>
                    fGMap.insert(std::pair<std::string,TAdvancedGraph*>(gname,new TAdvancedGraph(H_it->second)));
                    fGMap[gname]->SetName(gname.c_str());
                }
        }
    fFile->cd();

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        if (
             (std::string(H_it->second->GetName()).find("H_manipdata_")!=std::string::npos)||
             (std::string(H_it->second->GetName()).find("H_manipcorrected_")!=std::string::npos)||
            (std::string(H_it->second->GetName()).find("H_manipmc")!=std::string::npos)
            )
            {H_it->second->SetDirectory(fFile); H_it->second->Write(0,TObject::kWriteDelete); }

    printf("%i\n",fHMap.size());
    printf("%i\n",fGMap.size());
    fFile->Close();

}
