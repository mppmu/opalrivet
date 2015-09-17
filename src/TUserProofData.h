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
#ifndef TUSERPROOFDATA_H
#define TUSERPROOFDATA_H
#include <TROOT.h>
#include <TChain.h>
#include <TObject.h>
class TNtuple;
class TProofOutputFile;
class TEntryList;
class TH1F;
class TH1D;
class TAdvancedGraph;
class TGraphAsymmErrors;
class TFile;
class TSampleInfo;
class TUserProofData
{
public :
    std::vector<std::string> fAlgorithms;
    std::map<std::string,TAdvancedGraph*> fGMap;
    std::map<std::string,TH1D*> fHMap;
    TProofOutputFile *fProofFile;
    TSampleInfo *fSampleInfo;
    TFile *fFile;
    TUserProofData();
    ~TUserProofData();

    ClassDef(TUserProofData,0);
};
#endif
