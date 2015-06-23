/*
 * ROOTConvert.h
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
 * Part of the code was taken from YODA
 * YODA -- Yet more Objects for Data Analysis
 * Copyright (C) 2008-2013 The YODA collaboration 
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
#ifndef YODA_ROOTConvert_h
#define YODA_ROOTConvert_h

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

namespace YODA
{

Histo1D*           TH1toHisto1D  (const TH1* th1, std::string fname="");
TH1D*              Histo1DtoTH1D(const Histo1D* h) ;

Profile1D*         TProfiletoProfile1D(const TProfile*  p, std::string fname="") ;
TProfile*          Profile1DtoTProfile(const Profile1D* p) ;

Scatter2D*         TGraphtoScatter2D(const TGraph* g, std::string fname="") ;
TGraphAsymmErrors* Scatter2DtoTGraphAsymmErrors(const Scatter2D* s) ;

}

#endif
