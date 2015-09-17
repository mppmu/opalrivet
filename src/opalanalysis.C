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
#define opalanalysis_cxx
#include  "opalanalysis.h"
#include  "OPALJet.h"
#include  "TSampleInfo.h"
#include  "Helpers.h"
#include  "Cuts.h"
#ifndef YEARSUFFIX
#define YEARSUFFIX ""
#endif
void opalanalysis::Begin(__attribute__ ((unused))TTree *tree) {}
void opalanalysis::SlaveBegin(TTree * tree)
{
    fSampleInfo=0;
    TFile* TDB=new TFile("./opalanalysis/DB.root","update");
    std::vector<std::string> S=return_tokenize(SAMPLES, ":");
    std::map<std::string,std::pair<double,double> > proc;
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (!R) {printf("No such sample %s\n",it->c_str());  exit(1);}
            else
                {
                    if (proc.find(R->fProcesses)==proc.end()) proc.insert(std::pair<std::string,std::pair<double,double> >(R->fProcesses,std::pair<double,double>(0.0,0.0)));
                    proc[R->fProcesses].first+=R->fLuminocity;
                    proc[R->fProcesses].second+=R->fEvents;   ///Sum the luminocity and number of events for all processes.
                    if (!fSampleInfo) {fSampleInfo=new TSampleInfo(*R); fSampleInfo->SetName("sampleinfo");} /// Only the energy and name is needed in fact.
                    else if (R->fEnergyString!=fSampleInfo->fEnergyString) {printf("Mixing samples!"); exit(2);} ///Check all requested samples have same energy string.
                }
        }
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++) ///Update the DB and set weights for this execution. If there would be nmore files one can write a new DB.
        {
            TSampleInfo* R=(TSampleInfo*)TDB->Get(it->c_str());
            if (R->fType=="MCBG"||R->fType=="MCSI") R->fWeight=proc["ALL"].first/proc[R->fProcesses].first/proc["ALL"].second*proc[R->fProcesses].second; ///Set proper weight to the MC
            else R->fWeight=1.0;
            R->Write();
        }
    TDB->Close();
    fSampleInfo->fGenerator="opal";
    fOutput->Add(fSampleInfo);
    fProofFile = new TProofOutputFile(Form("./output/%s_%s%s_%s.root",fSampleInfo->fGenerator.c_str(),fSampleInfo->fEnergyString.c_str(),YEARSUFFIX,CUTS), "M");
    TDirectory *savedir = gDirectory;
    fFile = fProofFile->OpenFile("RECREATE");
    savedir->cd();
    tokenize(ALGORITHMS,":",fAlgorithms);
    std::vector<std::string> datatypes;
    tokenize("mcbackgr:mcsignal:mcall:data:truesignal:truesignalp:truebackgr:acceptancesignal:acceptancebackgr:corrected",":",datatypes);
    for (unsigned int i=0; i<fAlgorithms.size(); i++)for (unsigned int j=0; j<datatypes.size(); j++) BookHistograms(this,fSampleInfo->fPeriod,Form("%s_%s_%sGeV_",datatypes.at(j).c_str(),fAlgorithms.at(i).c_str(),fSampleInfo->fEnergyString.c_str()));
}
Bool_t opalanalysis::Process(Long64_t gentry)
{
    Int_t entry;
    entry=fChain->LoadTree(gentry);
    fChain->GetEntry(entry);
    bool passed[2];
    passed[0]=true;
    passed[1]=true;
    if (2*this->Ebeam<fSampleInfo->fEl||2*this->Ebeam>fSampleInfo->fEh) return kFALSE;
    fHMap["weight_before_selection"]->Fill((fSampleInfo->fType+"_"+fSampleInfo->fProcesses).c_str(),fSampleInfo->fWeight);
    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
    if (fSampleInfo->fType==std::string("MCSI")||fSampleInfo->fType==std::string("MCBG")) if (2.0*this->Ebeam-TLorentzVector(Pisr[0],Pisr[1],Pisr[2],Pisr[3]).M()> 1.0)  passed[1]=kFALSE;
    if( this->Ntkd02 < int(mycuts[CUTS]["Ntkd02"]) )  passed[0]=kFALSE;
    if( std::abs(this->Tvectc[2])> mycuts[CUTS]["costt"] )  passed[0]=kFALSE;
    if( this->Lwqqqq>mycuts[CUTS]["wqqqq"] )  passed[0]=kFALSE;
    if( this->Lwqqln>mycuts[CUTS]["wqqln"] )  passed[0]=kFALSE;
    if( this->Il2mh!=int(mycuts[CUTS]["Il2mh"]))   passed[0]=kFALSE;
    if( this->Icjst!=int(mycuts[CUTS]["Icjst"]))   passed[0]=kFALSE;
    if( this->Iebst!=int(mycuts[CUTS]["Iebst"]))   passed[0]=kFALSE;
    double SP;
    if (int(mycuts[CUTS]["sprimalgo"])==1) SP=TLorentzVector(Pspr[0],Pspr[1],Pspr[2],Pspr[3]).M();
    if (int(mycuts[CUTS]["sprimalgo"])==2) SP=TLorentzVector(Pspri[0],Pspri[1],Pspri[2],Pspri[3]).M();

    if (fSampleInfo->fType==std::string("DATA"))  if( 2.0*this->Ebeam-SP > mycuts[CUTS]["sprimedata"] ) passed[0]=kFALSE;
    if (fSampleInfo->fType==std::string("MCSI"))  if( 2.0*this->Ebeam-SP > mycuts[CUTS]["sprimemc"] )   {passed[0]=kFALSE;  passed[1]=kFALSE;}
    if (fSampleInfo->fType==std::string("MCBG"))  if( 2.0*this->Ebeam-SP > mycuts[CUTS]["sprimemc"] )   passed[0]=kFALSE;
    std::vector<std::string> datatypes;
    std::vector<std::string> options;
    std::string objects="mt";
    if (int(mycuts[CUTS]["objects"])==2) objects="tc";
    if (fSampleInfo->fType==std::string("DATA")) { tokenize("data",":",datatypes);                tokenize(objects,":",options);   }
    if (fSampleInfo->fType==std::string("MCSI")) { tokenize("mcsignal:truesignal:mcall:truesignalp",":",datatypes); tokenize(objects+":h:mt:p",":",options); }//
    if (fSampleInfo->fType==std::string("MCBG")) { tokenize("mcbackgr:truebackgr:mcall",":",datatypes); tokenize(objects+":h:mt",":",options); }//add syst
    for (unsigned int j=0; j<datatypes.size(); j++)
        if (passed[j%2])
            {
                std::vector<TLorentzVector> vtlv= GetLorentzVectors( this,options.at(j) );
                for (std::vector<std::string>::iterator it=fAlgorithms.begin(); it!=fAlgorithms.end(); it++)
                    {
                        bool dbg=false;
                        OPALJet* tfj =new OPALJet( vtlv,*it,mycuts[*it], NULL,dbg);
                        OPALAnalysis(this, tfj,fSampleInfo->fWeight,*it,Form("%s_%s_%sGeV_",datatypes.at(j).c_str(),it->c_str(),fSampleInfo->fEnergyString.c_str()));
                        if (*it=="durham")
                            {
                                if (j==1) if (passed[0]) printf("OPALR:TRUE: %i %05d\n",Irun,Ievnt);
                                if (j==0) printf("OPALR:MCDA: %i %05d\n",Irun,Ievnt);
                            }
                    }
            }
    if (passed[0]) fHMap["weight_reco"]->Fill((fSampleInfo->fType+"_"+fSampleInfo->fProcesses).c_str(),fSampleInfo->fWeight);
    if (passed[1]) fHMap["weight_true"]->Fill((fSampleInfo->fType+"_"+fSampleInfo->fProcesses).c_str(),fSampleInfo->fWeight);
    return kTRUE;
}
void opalanalysis::SlaveTerminate()
{
    TDirectory *savedir = gDirectory;
    fFile->cd();
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Sumw2();  H_it->second->Write(); H_it->second->SetDirectory(0);      }
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) {  G_it->second->Write();}
    fProofFile->Print();
    fOutput->Add(fProofFile);
    gDirectory = savedir;
    fFile->Close();
}
void opalanalysis::Terminate()
{
    TSampleInfo *out = (TSampleInfo *) fOutput->FindObject("sampleinfo");
    if (!out)  { printf("No TSampleInfo\n"); fSampleInfo=new TSampleInfo();}
    else        fSampleInfo=out;
    fSampleInfo->fGenerator="opal";
    printf("opening ./output/%s_%s.root",fSampleInfo->fGenerator.c_str(),fSampleInfo->fEnergyString.c_str());
    TFile* type_fFile= new TFile(Form("./output/%s_%s%s_%s.root",fSampleInfo->fGenerator.c_str(),fSampleInfo->fEnergyString.c_str(),YEARSUFFIX,CUTS), "UPDATE");
    if (!type_fFile) {printf("No such file\n"); return;}
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
        }
    std::map<std::string,std::map<std::string,double> > mycuts=InitCuts();
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
        {
            if (H_it->first.find("H_acceptancesignal_")!=std::string::npos)
                {
                    std::string name=H_it->first.substr(std::string("H_acceptancesignal_").length());
                    H_it->second->Add(fHMap[std::string("H_mcsignal_")+name]);
                    H_it->second->Divide(fHMap[std::string("H_truesignal_")+name]);
                    fHMap[std::string("H_corrected_")+name]->Add(fHMap[std::string("H_data_")+name],fHMap[std::string("H_mcbackgr_")+name],1.0,-mycuts[CUTS]["backgroundscale"]);
                    fHMap[std::string("H_corrected_")+name]->Divide(fHMap[std::string("H_acceptancesignal_")+name]);
                    double H_scale=fHMap[std::string("H_corrected_")+name]->GetBinContent(0);
                    if   (H_it->first.find("JETR")!=std::string::npos)
                        { fHMap[std::string("H_corrected_")+name]->Scale(1.0/H_scale); fHMap[std::string("H_corrected_")+name]->SetBinContent(0,H_scale);}
                    else if (std::abs(fHMap[std::string("H_corrected_")+name]->Integral())>0.0001)
                        fHMap[std::string("H_corrected_")+name]->Scale(1.0/fHMap[std::string("H_corrected_")+name]->Integral());

                }
            if (H_it->first.find("H_acceptancebackgr_")!=std::string::npos)
                {
                    std::string name=H_it->first.substr(std::string("H_acceptancebackgr_").length());
                    H_it->second->Add(fHMap[std::string("H_mcbackgr_")+name]);
                    H_it->second->Divide(fHMap[std::string("H_truebackgr_")+name]);
                }
        }
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) { H_it->second->Write(0,TObject::kWriteDelete); H_it->second->SetDirectory(0);}
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)
        {
            if (G_it->first.find("G_acceptancesignal_")!=std::string::npos)
                {
                    std::string name=G_it->first.substr(std::string("G_acceptancesignal_").length());
                    G_it->second->Add(NULL,fGMap[std::string("G_mcsignal_")+name]);
                    G_it->second->Divide(fGMap[std::string("G_mcsignal_")+name],fGMap[std::string("G_truesignal_")+name]);
                    fGMap[std::string("G_corrected_")+name]->Add(fGMap[std::string("G_data_")+name],fGMap[std::string("G_mcbackgr_")+name],1,-mycuts[CUTS]["backgroundscale"]);
                    fGMap[std::string("G_corrected_")+name]->Divide(fGMap[std::string("G_corrected_")+name],fGMap[std::string("G_acceptancesignal_")+name]);

                    if   (G_it->first.find("JETR")!=std::string::npos)
                        fGMap[std::string("G_corrected_")+name]->Scale(1.0/fHMap[std::string("H_corrected_")+name]->GetBinContent(0));//WOW!
                    else if (std::abs(fGMap[std::string("G_corrected_")+name]->Integral())>0.0001)
                        fGMap[std::string("G_corrected_")+name]->Scale(1.0/fGMap[std::string("G_corrected_")+name]->Integral());
                }
            if (G_it->first.find("G_acceptancebackgr_")!=std::string::npos)
                {
                    std::string name=G_it->first.substr(std::string("G_acceptancebackgr_").length());
                    G_it->second->Add(NULL,fGMap[std::string("G_mcbackgr_")+name]);
                    G_it->second->Divide(fGMap[std::string("G_mcbackgr_")+name],fGMap[std::string("G_truebackgr_")+name]);
                }
        }
    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    type_fFile->Close();
}
Bool_t opalanalysis::Notify()
{
    TString currentfile=gSystem->BaseName(fChain->GetCurrentFile()->GetName());
    TFile* theDB=new TFile("./opalanalysis/DB.root","r");
    std::vector<std::string> S=return_tokenize(SAMPLES, ":");
    for (std::vector<std::string>::iterator it=S.begin(); it!=S.end(); it++)
        {
            TSampleInfo* R=(TSampleInfo*)theDB->Get(it->c_str());
            if (!R) {printf("No such sample %s\n",it->c_str());  exit(1);}
            else if ((fSampleInfo->fEnergyString==R->fEnergyString)&&( std::find(R->fFiles.begin(), R->fFiles.end(), std::string(currentfile.Data()))!=R->fFiles.end() ))
                {
                    printf("Found file %s in sample %s with energy %s\n",std::string(currentfile.Data()).c_str(),R->GetName(),R->fEnergyString.c_str());
                    fSampleInfo=new TSampleInfo(*R);
                }
        }
    theDB->Close();
    return kTRUE;
}
