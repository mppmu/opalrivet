// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#include "YODA/ReaderROOT.h"
#include "YODA/Utils/StringUtils.h"
#include "YODA/Exceptions.h"

#include <iostream>

#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"

using namespace std;

namespace YODA {
  ReaderROOT::histo1d ReaderROOT::_histo1d;
  ReaderROOT::profile1d ReaderROOT::_profile1d;
  ReaderROOT::scatter2d ReaderROOT::_scatter2d;
  std::map<std::string, std::string> ReaderROOT::_annotations;
  

  void ReaderROOT::_readDoc(std::istream& stream, vector<AnalysisObject*>& aos) {

std::string streama("1.root");
TFile* fin = new TFile(streama.c_str()) ;
  if (!fin->IsOpen()) {
    printf("<E> Cannot open input file %s\n",streama.c_str()) ;
    exit(1) ;
  }
  
  TList* list = fin->GetListOfKeys() ;
  if (!list) { printf("<E> No keys found in file\n") ; exit(1) ; }
  
  TIter next(list) ;
  TKey* key ;
  TObject* obj ;
      
  while ( key = (TKey*)next() ) {
    obj = key->ReadObj() ;
    int type=-1;
    
//cdef _toTH1D(cyoda.Histo1D* h1d):
//cdef _toTProfile(cyoda.Profile1D* p1d):
//cdef _toTGraphAsymmErrors(cyoda.Scatter2D* s2d):
    
    
    if (strcmp(obj->IsA()->GetName(),"TProfile")==0) type=0;
    if (obj->InheritsFrom("TH1")) type=1;
    if (obj->InheritsFrom("TH2")) type=2;
    if (obj->InheritsFrom("TGraph")) 
    {
	type=30;
        if (strcmp(obj->IsA()->GetName(),"TGraph")==0)type=31;
            if (strcmp(obj->IsA()->GetName(),"TGraphErrors")==0) type=32;
                if (strcmp(obj->IsA()->GetName(),"TGraphAsymmErrors")==0)type=33;
    }
    
    
    if (type==-1)  printf("<W> Object %s is not 1D or 2D histogram : will not be converted\n",obj->GetName()) ;
    if (type==0)   printf("<W> Object %s has unsupported type TProfile\n",obj->GetName()) ; 
    if (type==1)
    {
            char a[255];
            TH1F* HH= (TH1F*)(obj); 
            //_histo1d.dbn_tot=HH->GetNbinsX();
            sprintf(a,"/%s/%s",streama.c_str(),obj->GetName());
     YODA::Histo1D* dps = new YODA::Histo1D();//_histo1d.bins, _histo1d.dbn_tot, _histo1d.dbn_uflow, _histo1d.dbn_oflow);
          
	        int i;
	        
	        if (HH->GetNbinsX()>0){
	        for (i=1;i<HH->GetNbinsX();i++)
	        {
		     dps->addBin(HH->GetBinLowEdge(i),HH->GetBinLowEdge(i)+ HH->GetBinWidth(i));
		     }
            dps->setAnnotation("Title", obj->GetTitle());
            dps->setAnnotation("TitleX", HH->GetXaxis()->GetTitle());
            dps->setAnnotation("TitleY", HH->GetYaxis()->GetTitle());
	        for (i=1;i<HH->GetNbinsX();i++)
	        {
//				printf("%f\t%f\t%i\n",i,HH->GetBinLowEdge(i),HH->GetBinLowEdge(i)+ HH->GetBinWidth(i));
		     dps->fill(HH->GetBinCenter(i), HH->GetBinContent(i));
		     }
           
            aos.push_back(dps);
            
		 }cleanup();

          
          
          
           
    }
    if (type==2)   printf("<W> Object %s has unsupported type TH2\n",obj->GetName()) ; 
    if (type/10==3)
    {
            char a[255];
            sprintf(a,"/%s/%s",streama.c_str(),obj->GetName());
	        Scatter2D* dps = new Scatter2D(a);
	        int i;
	        TGraphAsymmErrors* HH=(TGraphAsymmErrors*)obj;

	        for (i=0;i<HH->GetN()-1;i++)
	        {
	        double x,y;
	        HH->GetPoint(i,x,y);
	        dps->addPoint(x, y,
	        HH->GetErrorXlow(i),
	        HH->GetErrorXhigh(i),
	        HH->GetErrorYlow(i),
	        HH->GetErrorYhigh(i)
	        );
		    }
            dps->setAnnotation("Title", obj->GetTitle());
            dps->setAnnotation("TitleX", HH->GetXaxis()->GetTitle());
            dps->setAnnotation("TitleY", HH->GetYaxis()->GetTitle());
            aos.push_back(dps);
            cleanup();
		     }



  }
fin->Close();
}


}
