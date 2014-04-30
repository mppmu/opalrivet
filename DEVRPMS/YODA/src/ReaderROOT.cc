// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//

#include "YODA/ReaderROOT.h"
#include "YODA/Utils/StringUtils.h"
#include "YODA/Exceptions.h"

#include <iostream>



using namespace std;

namespace YODA
{
ReaderROOT::histo1d ReaderROOT::_histo1d;
ReaderROOT::profile1d ReaderROOT::_profile1d;
ReaderROOT::scatter2d ReaderROOT::_scatter2d;
std::map<std::string, std::string> ReaderROOT::_annotations;




void ReaderROOT::_readDoc(std::istream& stream, vector<AnalysisObject*>& aos)
{

    std::string streama=_filename; //Ugly trick;
    TFile* fin = new TFile(streama.c_str()) ;
    if (!fin->IsOpen())
        {
            printf("Cannot open input file %s\n",streama.c_str()) ;
            exit(1) ;
        }

    TList* list = fin->GetListOfKeys() ;
    if (!list) { printf("No keys found in file %s\n",streama.c_str()) ; exit(1) ; }

    TIter next(list) ;
    TKey* key ;
    TObject* obj ;

    while ( key = (TKey*)next() )
        {
            obj = key->ReadObj() ;
            int type=-1;




            if (strcmp(obj->IsA()->GetName(),"TProfile")==0) type=0;
            if (strcmp(obj->IsA()->GetName(),"TH1F")==0)type=11;
            if (strcmp(obj->IsA()->GetName(),"TH1D")==0) type=12;
            if (obj->InheritsFrom("TH2")) type=2;
            if (strcmp(obj->IsA()->GetName(),"TGraph")==0)type=31;
            if (strcmp(obj->IsA()->GetName(),"TGraphErrors")==0) type=32;
            if (strcmp(obj->IsA()->GetName(),"TGraphAsymmErrors")==0)type=33;
            if (type==-1)  printf("Object %s  has unsupported type %s and will not be converted\n",obj->GetName(),obj->IsA()->GetName()) ;
            if (type==0)   printf("Object %s has unsupported type TProfile\n",obj->GetName()) ;
            if (type==11||type==12)
                {

#define TH1_IS_SCATTER2D

#ifdef TH1_IS_SCATTER2D
                    char a[255];
                    sprintf(a,"/%s/%s",streama.c_str(),obj->GetName());
                    Scatter2D* dps = new Scatter2D(a);

                    TH1* HH= (TH1*)(obj);

                    for (int i = 1; i <= HH->GetNbinsX(); ++i)
                        {
                            const double x = HH->GetBinCenter(i);
                            const double exminus = x - HH->GetBinLowEdge(i);
                            const double explus = HH->GetBinLowEdge(i+1) - x;
                            const double width = exminus + explus;
                            dps->addPoint(x, HH->GetBinContent(i),
                                          exminus, explus,
                                          HH->GetBinErrorLow(i), HH->GetBinErrorUp(i));
                        }
                    dps->setAnnotation("Title", obj->GetTitle());
                    dps->setAnnotation("XLabel", HH->GetXaxis()->GetTitle());
                    dps->setAnnotation("YLabel", HH->GetYaxis()->GetTitle());
                    aos.push_back(dps);
#else
                    char a[255];
                    sprintf(a,"/%s/%s",streama.c_str(),obj->GetName());
                    YODA::Histo1D* dps = new YODA::Histo1D(a);//_histo1d.bins, _histo1d.dbn_tot, _histo1d.dbn_uflow, _histo1d.dbn_oflow);
                    int i;

                    if (type==11)
                        {
                            TH1F* HHF= (TH1F*)(obj);
                            if (HHF->GetNbinsX()>0)
                                {
                                    for (i=1; i<HHF->GetNbinsX(); i++)
                                        dps->addBin(HHF->GetBinLowEdge(i),HHF->GetBinLowEdge(i)+ HHF->GetBinWidth(i));
                                    dps->setAnnotation("Title", obj->GetTitle());
                                    dps->setAnnotation("TitleX", HHF->GetXaxis()->GetTitle());
                                    dps->setAnnotation("TitleY", HHF->GetYaxis()->GetTitle());
                                    for (i=1; i<HHF->GetNbinsX(); i++) dps->fill(HHF->GetBinCenter(i), HHF->GetBinContent(i));
                                }
                            aos.push_back(dps);
                        }

                    if (type==12)
                        {
                            TH1D* HHD= (TH1D*)(obj);
                            if (HHD->GetNbinsX()>0)
                                {
                                    for (i=1; i<HHD->GetNbinsX(); i++)
                                        dps->addBin(HHD->GetBinLowEdge(i),HHD->GetBinLowEdge(i)+ HHD->GetBinWidth(i));
                                    dps->setAnnotation("Title", obj->GetTitle());
                                    dps->setAnnotation("TitleX", HHD->GetXaxis()->GetTitle());
                                    dps->setAnnotation("TitleY", HHD->GetYaxis()->GetTitle());
                                    for (i=1; i<HHD->GetNbinsX(); i++) dps->fill(HHD->GetBinCenter(i), HHD->GetBinContent(i));
                                }
                            aos.push_back(dps);
                        }


#endif
                    cleanup();
                }
            if (type==2)   printf("<W> Object %s has unsupported type TH2\n",obj->GetName()) ;
            if (type==31||type==32||type==33)
                {
                    char a[255];
                    sprintf(a,"/%s/%s",streama.c_str(),obj->GetName());
                    Scatter2D* dps = new Scatter2D(a);
                    int i;
                    TGraphAsymmErrors* HH=(TGraphAsymmErrors*)obj;

                    for (i=0; i<HH->GetN()-1; i++)
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
