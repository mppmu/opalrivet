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
#ifndef UBACKGROUND_H
#define UBACKGROUND_H

#include "TGraphAsymmErrors.h"
#include "TH1D.h"
class TAdvancedGraph: public TGraphAsymmErrors
{
public:
    TAdvancedGraph();
    TAdvancedGraph(Int_t n, const Double_t* x, const Double_t* y, const Double_t* exl = 0, const Double_t* exh = 0, const Double_t* eyl = 0, const Double_t* eyh = 0);
    TAdvancedGraph(TH1D* a);
    TAdvancedGraph(Int_t n);
    int Merge(TCollection *hlist);
    Bool_t Add( TAdvancedGraph* h,  TAdvancedGraph* h2, Double_t c1 = 1, Double_t c2 = 1);
    void Divide(TAdvancedGraph* A,  TAdvancedGraph* B, bool keepconsistent=true);
    void Scale(double k);
    TH1D* ToTH1D(std::string n,int l);
    ClassDef(TAdvancedGraph,0)
};
#endif
