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
    for (int k=3; k<argc; k++)
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
            if ((name.find("h98600")!=std::string::npos)
                    ||(name.find("h18600")!=std::string::npos)
                    ||(name.find("h19000")!=std::string::npos)
                    ||(name.find("h98600")!=std::string::npos)
                    ||(name.find("h88600")!=std::string::npos)
                    ||(name.find("h78600")!=std::string::npos)
                    ||(name.find("h68600")!=std::string::npos)
                    ||(name.find("h58600")!=std::string::npos)
                    ||(name.find("h48600")!=std::string::npos)
                    ||(name.find("h38600")!=std::string::npos)
                    ||(name.find("h30000")!=std::string::npos)
                    ||(name.find("h31100")!=std::string::npos)
                    ||(name.find("h31180")!=std::string::npos)
                    ||(name.find("h31190")!=std::string::npos)
                    //||(name.find("h3318")!=std::string::npos)
                    ||(name.find("h28600")!=std::string::npos)
                    ||(name.find("h28600")!=std::string::npos)///FIXME!
               )
                {
					
					/* 
  KEY: TH1F	h3118000;1	1-T	Parton	PYTHIA	(Z/g)*	sptrue 
  KEY: TH1F	h3118050;1	1-T	Parton	PYTHIA	(Z/g)*	sptrue moments 
  KEY: TH1F	h3119000;1	1-T	Hadron	PYTHIA	(Z/g)*	sptrue 
  KEY: TH1F	h3119050;1	1-T	Hadron	PYTHIA	(Z/g)*	sptrue moments 
  KEY: TH1F	h3118100;1	1-T	Parton	PYTHIA	(Z/g)*	sptpre 
  KEY: TH1F	h3118150;1	1-T	Parton	PYTHIA	(Z/g)*	sptpre moments 
  KEY: TH1F	h3118200;1	1-T	Parton	PYTHIA	(Z/g)*	sptisr 
  KEY: TH1F	h3118250;1	1-T	Parton	PYTHIA	(Z/g)*	sptisr moments 
  KEY: TH1F	h3118300;1	1-T	Parton	PYTHIA	(Z/g)*	sptsta 
  KEY: TH1F	h3118350;1	1-T	Parton	PYTHIA	(Z/g)*	sptsta moments 
					
					*/

                    replace_all(name,"h98600","H_manipcorrected_"+std::string(argv[2])+"_205GeV|_");
                    //replace_all(name,"h1900","H_manipcorrected_"+std::string(argv[2])+"_205GeV|_");
                    //replace_all(name,"h9","H_manipcorrected_"+std::string(argv[2])+"_202GeV|_");
                    replace_all(name,"h88600","H_manipcorrected_"+std::string(argv[2])+"_196GeV|_");
                    replace_all(name,"h78600","H_manipcorrected_"+std::string(argv[2])+"_192GeV|_");
                    replace_all(name,"h68600","H_manipcorrected_"+std::string(argv[2])+"_189GeV|_");
                    replace_all(name,"h58600","H_manipcorrected_"+std::string(argv[2])+"_183GeV|_");
                    replace_all(name,"h48600","H_manipcorrected_"+std::string(argv[2])+"_172GeV|_");

                    replace_all(name,"h38600","H_manipcorrected_"+std::string(argv[2])+"_161GeV|_");
                    replace_all(name,"h30000","H_manipdata_"+std::string(argv[2])+"_161GeV|_");
                    replace_all(name,"h31100","H_manipmcsignal_"+std::string(argv[2])+"_161GeV|_");
                    replace_all(name,"h31180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_161GeV|_"); //PARTON!
                    replace_all(name,"h31190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_161GeV|_"); //HADRON!
 
 
 

                    replace_all(name,"h28600","H_manipcorrected_"+std::string(argv[2])+"_136GeV|_");

                    replace_all(name,"h20000","H_manipcorrected_"+std::string(argv[2])+"_130GeV|_");

                    replace_all(name,"h18600","H_manipcorrected_"+std::string(argv[2])+"_91GeV|_");



                    //replace_all(name,"9999","admin");
                    replace_all(name,"|_00","_1-T");
                    replace_all(name,"|_01","_T-Min");
                    replace_all(name,"|_02","_T-Maj");
                    replace_all(name,"|_03","_A");
                    replace_all(name,"|_04","_CP");
                    replace_all(name,"|_05","_MH");
                    replace_all(name,"|_06","_S");
                    replace_all(name,"|_07","_O");
                    replace_all(name,"|_08","_BT");
                    replace_all(name,"|_09","_BW");
                    replace_all(name,"|_10","_D2");
                    replace_all(name,"|_11","_T");
                    replace_all(name,"|_12","_MH2");
                    replace_all(name,"|_13","_JTE0");
                    replace_all(name,"|_14","_DP");
                    replace_all(name,"|_15","_JETR2");
                    replace_all(name,"|_16","_JETR3");
                    replace_all(name,"|_17","_JETR4");
                    replace_all(name,"|_18","_JETR5");
                    replace_all(name,"|_19","_JETR6");
                    replace_all(name,"|_20","_ML");
                    replace_all(name,"|_21","_BN");






                    

                    H_it->second->SetName(name.c_str());
                    std::string gname=name;
                    replace_all(gname,"H_","G_");
                    
                    fGMap.insert(std::pair<std::string,TAdvancedGraph*>(gname,new TAdvancedGraph(H_it->second)));
                    fGMap[gname]->SetName(gname.c_str());
                }
        }
    fFile->cd();

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        if (std::string(H_it->second->GetName()).find("H_")!=std::string::npos)
            {H_it->second->SetDirectory(fFile); H_it->second->Write(0,TObject::kWriteDelete); }

    printf("%i\n",fHMap.size());
    printf("%i\n",fGMap.size());
    fFile->Close();

}
