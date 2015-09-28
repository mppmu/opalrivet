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
            if (0    

                    ||(name.find("h200000")!=std::string::npos)
                    ||(name.find("h201100")!=std::string::npos)
                    ||(name.find("h201180")!=std::string::npos)
                    ||(name.find("h201190")!=std::string::npos)
                    ||(name.find("h208600")!=std::string::npos)

                    ||(name.find("h210000")!=std::string::npos)
                    ||(name.find("h211100")!=std::string::npos)
                    ||(name.find("h211180")!=std::string::npos)
                    ||(name.find("h211190")!=std::string::npos)
                    ||(name.find("h218600")!=std::string::npos)

                    ||(name.find("h220000")!=std::string::npos)
                    ||(name.find("h221100")!=std::string::npos)
                    ||(name.find("h221180")!=std::string::npos)
                    ||(name.find("h221190")!=std::string::npos)
                    ||(name.find("h228600")!=std::string::npos)



                    ||(name.find("h300000")!=std::string::npos)
                    ||(name.find("h301100")!=std::string::npos)
                    ||(name.find("h301180")!=std::string::npos)
                    ||(name.find("h301190")!=std::string::npos)
                    ||(name.find("h308600")!=std::string::npos)


                    ||(name.find("h400000")!=std::string::npos)
                    ||(name.find("h401100")!=std::string::npos)
                    ||(name.find("h401180")!=std::string::npos)
                    ||(name.find("h401190")!=std::string::npos)
                    ||(name.find("h408600")!=std::string::npos)


                    ||(name.find("h500000")!=std::string::npos)
                    ||(name.find("h501100")!=std::string::npos)
                    ||(name.find("h501180")!=std::string::npos)
                    ||(name.find("h501190")!=std::string::npos)
                    ||(name.find("h508600")!=std::string::npos)



                    ||(name.find("h600000")!=std::string::npos)
                    ||(name.find("h601100")!=std::string::npos)
                    ||(name.find("h601180")!=std::string::npos)
                    ||(name.find("h601190")!=std::string::npos)
                    ||(name.find("h608600")!=std::string::npos)



                    ||(name.find("h700000")!=std::string::npos)
                    ||(name.find("h701100")!=std::string::npos)
                    ||(name.find("h701180")!=std::string::npos)
                    ||(name.find("h701190")!=std::string::npos)
                    ||(name.find("h708600")!=std::string::npos)



                    ||(name.find("h800000")!=std::string::npos)
                    ||(name.find("h801100")!=std::string::npos)
                    ||(name.find("h801180")!=std::string::npos)
                    ||(name.find("h801190")!=std::string::npos)
                    ||(name.find("h808600")!=std::string::npos)



                    ||(name.find("h900000")!=std::string::npos)
                    ||(name.find("h901100")!=std::string::npos)
                    ||(name.find("h901180")!=std::string::npos)
                    ||(name.find("h901190")!=std::string::npos)
                    ||(name.find("h908600")!=std::string::npos)



                    ||(name.find("h910000")!=std::string::npos)
                    ||(name.find("h911100")!=std::string::npos)
                    ||(name.find("h911180")!=std::string::npos)
                    ||(name.find("h911190")!=std::string::npos)
                    ||(name.find("h918600")!=std::string::npos)



                    ||(name.find("h920000")!=std::string::npos)
                    ||(name.find("h921100")!=std::string::npos)
                    ||(name.find("h921180")!=std::string::npos)
                    ||(name.find("h921190")!=std::string::npos)
                    ||(name.find("h928600")!=std::string::npos)



                    ||(name.find("h930000")!=std::string::npos)
                    ||(name.find("h931100")!=std::string::npos)
                    ||(name.find("h931180")!=std::string::npos)
                    ||(name.find("h931190")!=std::string::npos)
                    ||(name.find("h938600")!=std::string::npos)


                    ||(name.find("h940000")!=std::string::npos)
                    ||(name.find("h941100")!=std::string::npos)
                    ||(name.find("h941180")!=std::string::npos)
                    ||(name.find("h941190")!=std::string::npos)
                    ||(name.find("h948600")!=std::string::npos)








               )
                {


                    replace_all(name,"h200000","H_manipdata_"+std::string(argv[2])+"_136GeV|_");
                    replace_all(name,"h201100","H_manipmcsignal_"+std::string(argv[2])+"_136GeV|_");
                    replace_all(name,"h201180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_136GeV|_"); //PARTON!
                    replace_all(name,"h201190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_136GeV|_"); //HADRON!
                    replace_all(name,"h208600","H_manipcorrected_"+std::string(argv[2])+"_136GeV|_");



                    replace_all(name,"h210000","H_manipdata_"+std::string(argv[2])+"_130GeV|_");
                    replace_all(name,"h211100","H_manipmcsignal_"+std::string(argv[2])+"_130GeV|_");
                    replace_all(name,"h211180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_130GeV|_"); //PARTON!
                    replace_all(name,"h211190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_130GeV|_"); //HADRON!
                    replace_all(name,"h218600","H_manipcorrected_"+std::string(argv[2])+"_130GeV|_");

                    replace_all(name,"h220000","H_manipdata_"+std::string(argv[2])+"_133GeV|_");
                    replace_all(name,"h221100","H_manipmcsignal_"+std::string(argv[2])+"_133GeV|_");
                    replace_all(name,"h221180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_133GeV|_"); //PARTON!
                    replace_all(name,"h221190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_133GeV|_"); //HADRON!
                    replace_all(name,"h228600","H_manipcorrected_"+std::string(argv[2])+"_133GeV|_");



                    replace_all(name,"h300000","H_manipdata_"+std::string(argv[2])+"_161GeV|_");
                    replace_all(name,"h301100","H_manipmcsignal_"+std::string(argv[2])+"_161GeV|_");
                    replace_all(name,"h301180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_161GeV|_"); //PARTON!
                    replace_all(name,"h301190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_161GeV|_"); //HADRON!
                    replace_all(name,"h308600","H_manipcorrected_"+std::string(argv[2])+"_161GeV|_");

                    replace_all(name,"h400000","H_manipdata_"+std::string(argv[2])+"_172GeV|_");
                    replace_all(name,"h401100","H_manipmcsignal_"+std::string(argv[2])+"_172GeV|_");
                    replace_all(name,"h401180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_172GeV|_"); //PARTON!
                    replace_all(name,"h401190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_172GeV|_"); //HADRON!
                    replace_all(name,"h408600","H_manipcorrected_"+std::string(argv[2])+"_172GeV|_");

                    replace_all(name,"h500000","H_manipdata_"+std::string(argv[2])+"_183GeV|_");
                    replace_all(name,"h501100","H_manipmcsignal_"+std::string(argv[2])+"_183GeV|_");
                    replace_all(name,"h501180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_183GeV|_"); //PARTON!
                    replace_all(name,"h501190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_183GeV|_"); //HADRON!
                    replace_all(name,"h508600","H_manipcorrected_"+std::string(argv[2])+"_183GeV|_");


                    replace_all(name,"h600000","H_manipdata_"+std::string(argv[2])+"_189GeV|_");
                    replace_all(name,"h601100","H_manipmcsignal_"+std::string(argv[2])+"_189GeV|_");
                    replace_all(name,"h601180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_189GeV|_"); //PARTON!
                    replace_all(name,"h601190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_189GeV|_"); //HADRON!
                    replace_all(name,"h608600","H_manipcorrected_"+std::string(argv[2])+"_189GeV|_");


                    replace_all(name,"h700000","H_manipdata_"+std::string(argv[2])+"_192GeV|_");
                    replace_all(name,"h701100","H_manipmcsignal_"+std::string(argv[2])+"_192GeV|_");
                    replace_all(name,"h701180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_192GeV|_"); //PARTON!
                    replace_all(name,"h701190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_192GeV|_"); //HADRON!
                    replace_all(name,"h708600","H_manipcorrected_"+std::string(argv[2])+"_192GeV|_");



                    replace_all(name,"h800000","H_manipdata_"+std::string(argv[2])+"_196GeV|_");
                    replace_all(name,"h801100","H_manipmcsignal_"+std::string(argv[2])+"_196GeV|_");
                    replace_all(name,"h801180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_196GeV|_"); //PARTON!
                    replace_all(name,"h801190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_196GeV|_"); //HADRON!
                    replace_all(name,"h808600","H_manipcorrected_"+std::string(argv[2])+"_196GeV|_");



                    replace_all(name,"h910000","H_manipdata_"+std::string(argv[2])+"_200GeV|_");
                    replace_all(name,"h911100","H_manipmcsignal_"+std::string(argv[2])+"_200GeV|_");
                    replace_all(name,"h911180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_200GeV|_"); //PARTON!
                    replace_all(name,"h911190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_200GeV|_"); //HADRON!
                    replace_all(name,"h918600","H_manipcorrected_"+std::string(argv[2])+"_200GeV|_");


                    replace_all(name,"h920000","H_manipdata_"+std::string(argv[2])+"_202GeV|_");
                    replace_all(name,"h921100","H_manipmcsignal_"+std::string(argv[2])+"_202GeV|_");
                    replace_all(name,"h921180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_202GeV|_"); //PARTON!
                    replace_all(name,"h921190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_202GeV|_"); //HADRON!
                    replace_all(name,"h928600","H_manipcorrected_"+std::string(argv[2])+"_202GeV|_");


                    replace_all(name,"h930000","H_manipdata_"+std::string(argv[2])+"_205GeV|_");
                    replace_all(name,"h931100","H_manipmcsignal_"+std::string(argv[2])+"_205GeV|_");
                    replace_all(name,"h931180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_205GeV|_"); //PARTON!
                    replace_all(name,"h931190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_205GeV|_"); //HADRON!
                    replace_all(name,"h938600","H_manipcorrected_"+std::string(argv[2])+"_205GeV|_");


                    replace_all(name,"h940000","H_manipdata_"+std::string(argv[2])+"_206GeV|_");
                    replace_all(name,"h941100","H_manipmcsignal_"+std::string(argv[2])+"_206GeV|_");
                    replace_all(name,"h941180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_206GeV|_"); //PARTON!
                    replace_all(name,"h941190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_206GeV|_"); //HADRON!
                    replace_all(name,"h948600","H_manipcorrected_"+std::string(argv[2])+"_206GeV|_");



                    replace_all(name,"h900000","H_manipdata_"+std::string(argv[2])+"_207GeV|_");
                    replace_all(name,"h901100","H_manipmcsignal_"+std::string(argv[2])+"_207GeV|_");
                    replace_all(name,"h901180","H_manipmcsignaltrueparton_"+std::string(argv[2])+"_207GeV|_"); //PARTON!
                    replace_all(name,"h901190","H_manipmcsignaltruehadron_"+std::string(argv[2])+"_207GeV|_"); //HADRON!
                    replace_all(name,"h908600","H_manipcorrected_"+std::string(argv[2])+"_207GeV|_");

















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

    printf("%lu\n",fHMap.size());
    printf("%lu\n",fGMap.size());
    fFile->Close();

}
