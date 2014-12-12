


#include "TFastJet.h" 
#include "TApplication.h"
#include <iostream>
#include <string>
#include <vector>

#include "TH1F.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "NtupleReader.h"


using namespace std;

void printy23( Int_t ievnt=100, const char* filename="da130_95_200.root" ) {

  //  gROOT->LoadMacro("libNtupleReaderDict.so");
  //  gROOT->LoadMacro("/home/iwsatlas1/skluth/qcd/fastjet/TFastJet/libTFastJetDict.so");

  NtupleReader ntr( filename );
  ntr.GetEvent( ievnt );
  vector<TLorentzVector> vtlv= ntr.GetLorentzVectors( "mt" );
  TFastJet tfj( vtlv, "eekt" );
  cout << "y23 values " << tfj.ymerge(2) << " " << ntr.dmt_ymerge(2) << endl;
  return;

}



void makeplot( const char* filename="mc5025_1_200.root", Int_t maxevt=1000 ) {

  // Load libs in root before loading this macro
  //  gROOT->LoadMacro("libNtupleReaderDict.so");
  //  gROOT->LoadMacro("/home/iwsatlas1/skluth/qcd/fastjet/TFastJet/libTFastJetDict.so");

  NtupleReader* ntr= new NtupleReader( filename );
  Int_t nevnt= ntr->GetNumberEntries();
  Int_t nsel= 0;
  
  TH1F* y23mt= new TH1F( "y23mt", "y23 D det mt", 10, 0.0, 5.0 );
  TH1F* y23mtnr= new TH1F( "y23mtnr", "y23 D det mt non-rad", 10, 0.0, 5.0 );
  TH1F* y23had= new TH1F( "y23had", "y23 D had", 10, 0.0, 5.0 );
  TH1F* y23hadsel= new TH1F( "y23hadsel", "y23 D had sel", 10, 0.0, 5.0 );
  TH2F* y23mthad= new TH2F( "y23mthad", "y23 D mt vs had non-rad", 10, 0.0, 5.0, 10, 0.0, 5.0 );

  for( Int_t ievnt= 0; ievnt < TMath::Min( nevnt, maxevt ); ievnt++ ) {
    ntr->GetEvent( ievnt );
    Float_t y23mtfastjet= -1.0;
    if( ntr->LEP1Selection() ) {
      nsel++;
      vector<TLorentzVector> vtlvmt= ntr->GetLorentzVectors( "mt" );
      TFastJet tfjmt( vtlvmt, "eekt" );
      y23mtfastjet= tfjmt.ymerge(2);
      y23mt->Fill( -TMath::Log10( y23mtfastjet ) );
      //      Float_t y23old= ntr->dmt_ymerge(2);
      // Get jet 4-vectors:
      // vector<TLorentzVector> jets= tfjmt.exclusive_jets( 4 );
      // cout << "excl. jets " << ievnt<< " " << jets.size() << endl;
      // for( Int_t i= 0; i < 4; i++ ) {
      // 	jets[i].Print();
      // }
    }
    Float_t y23hadfastjet= -1.0;
    if( ntr->MCNonRad() ) {
      vector<TLorentzVector> vtlvhad= ntr->GetLorentzVectors( "h" );
      TFastJet tfjhad( vtlvhad, "eekt" );
      y23hadfastjet= tfjhad.ymerge(2);
      y23had->Fill( -TMath::Log10( y23hadfastjet ) );
    }
    if( ntr->LEP1Selection() && ntr->MCNonRad() ) {
      y23mthad->Fill( -TMath::Log10( y23hadfastjet ), -TMath::Log10( y23mtfastjet ) );
      y23hadsel->Fill( -TMath::Log10( y23hadfastjet ) );
      y23mtnr->Fill( -TMath::Log10( y23mtfastjet ) );
    }
  }
  cout << "Selected events " << nsel << endl;

  TCanvas* canv= new TCanvas( "canv", "y23 D plots", 900, 900 );
  canv->Divide( 2, 2 );
  canv->cd( 1 );
  y23mt->Draw();
  canv->cd( 2 );
  y23hadsel->Draw();
  canv->cd( 3 );
  y23mtnr->Draw();
  canv->cd( 4 );
  y23mthad->Draw( "box" );

  // canv->Print( "plot.pdf" );
    
  return;

}
int main(int argc, char* argv[]) {

	
	   TApplication* theApp = new  TApplication("App",&argc,argv);
   
   
	
//if (argc<2) return 1;
	puts(argv[0]);
	puts(argv[1]);
	makeplot("mc5025_1_200.root",100000);
	theApp->Run();

}	
