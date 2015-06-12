#ifndef ZROOT_H
#define ZROOT_H
#include <cassert>
#include <cmath>
#include <iostream>
#include <iostream>
#include <math.h>
#include <TApplication.h>
#include <TArrow.h>
#include <TBufferFile.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TDatime.h>
#include <TDSet.h>
#include <TEllipse.h>
#include <TEntryList.h>
#include <TEnv.h>
#include <TEventList.h>
#include <TF1.h>
#include <TF2.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TKey.h>
#include <TLine.h>
#include <TLorentzVector.h>
#include <TMap.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TProof.h>
#include <TProofOutputFile.h>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TTree.h>
#include <TVector3.h>
#include <vector>
#endif
#include "Helpers.h"

int main(int argc ,char** argv)
{

   int i=1;
   TFile* F= new TFile("DB.root","recreate");
   
   for (i=1;i<argc;i++)
   {
   printf("Processing %s\n",argv[i]);
   TChain* C= new TChain("h10");
   C->Add(argv[i]);
   C->Draw("Irun>>RUNHIST(20000,0.0,20000.0)");
   TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
   RUNHIST->SetName((std::string(argv[i])+"_RUNHIST").c_str());
   RUNHIST->Write();
   }
   
   F->Close();   
   };
