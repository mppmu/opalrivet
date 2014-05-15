// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#ifndef YODA_ROOTCnv_h
#define YODA_ROOTCnv_h

#include "YODA/Histo1D.h"
#include "YODA/Histo2D.h"
#include "YODA/Profile1D.h"
#include "YODA/Histo1D.h"
#include "YODA/Profile1D.h"
#include "YODA/Scatter2D.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TVectorF.h"
#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TClass.h"
#include "TH1F.h"
#include <string>

namespace YODA {
//Scatter2D*         TH1toScatter2D(const TH1* th1) ;




Histo1D*           TH1toHisto1D  (const TH1* th1, std::string fname="");
TH1D*              Histo1DtoTH1D(const Histo1D* h) ;

Profile1D*         TProfiletoProfile1D(const TProfile*  p, std::string fname="") ;
TProfile*          Profile1DtoTProfile(const Profile1D* p) ;

Scatter2D*         TGraphtoScatter2D(const TGraph* g, std::string fname="") ;
TGraphAsymmErrors* Scatter2DtoTGraphAsymmErrors(const Scatter2D* s) ;

}

#endif
