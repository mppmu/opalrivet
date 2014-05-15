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
            if (type==0)
                {
                    TProfile* P= (TProfile*)(obj);
                    YODA::Profile1D* dps = TProfiletoProfile1D(P,_filename);
                    aos.push_back(dps);
                }
            if (type==11||type==12)
                {
                    /*
                    The mapping is TH? <-> Histo?D, TProfile <-> Profile1D, TGraph <-> Scatter2D.
                    */

                    if (type==11)
                        {
                            TH1F* HHF= (TH1F*)(obj);
                            YODA::Histo1D* dps=YODA::TH1toHisto1D(HHF,_filename);
                            aos.push_back(dps);
                        }
                    if (type==12)
                        {
                            TH1D* HHD= (TH1D*)(obj);
                            YODA::Histo1D* dps=YODA::TH1toHisto1D(HHD);
                            aos.push_back(dps);
                        }
                }
            if (type==2)   printf("<W> Object %s has unsupported type TH2\n",obj->GetName()) ;
            if (type==31||type==32||type==33)
                {
                    TGraphAsymmErrors* G=(TGraphAsymmErrors*)obj;
                    Scatter2D* dps = YODA::TGraphtoScatter2D(G,_filename);
                    aos.push_back(dps);
                }
        }
    fin->Close();
}

}
