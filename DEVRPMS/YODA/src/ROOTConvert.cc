// -*- C++ -*-
//
// This file is part of YODA -- Yet more Objects for Data Analysis
// Copyright (C) 2008-2013 The YODA collaboration (see AUTHORS for details)
//
#ifndef YODA_ROOTCnv_h
#define YODA_ROOTCnv_h

#include "YODA/ROOTConvert.h"
#include "YODA/Histo1D.h"
#include "YODA/Histo2D.h"
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

Histo1D* TH1toHisto1D(const TH1* th1, std::string fname)
{
    std::vector<HistoBin1D> bins;
    const TArrayD* sumw2s = th1->GetSumw2();
    Dbn1D dbn_uflow, dbn_oflow;
    double sumWtot=0, sumW2tot=0;
    for (int i = 0; i <= th1->GetNbinsX()+1; ++i)
        {
            Dbn1D dbn(static_cast<unsigned long>(th1->GetBinContent(i)), th1->GetBinContent(i), sumw2s->GetAt(i) 
                      , 0, 0);
            //th1->GetBinContent(i)*th1->GetBinCenter(i), th1->GetBinContent(i)*sqr(th1->GetBinCenter(i)));
            if (i == 0) dbn_uflow = dbn;
            else if (i == th1->GetNbinsX()+1) dbn_oflow = dbn;
            else bins.push_back(HistoBin1D(std::make_pair(th1->GetBinLowEdge(i), th1->GetBinLowEdge(i+1)), dbn));
            sumWtot += th1->GetBinContent(i);
            sumW2tot +=   sumw2s->GetAt(i);
        }
    Dbn1D dbn_tot(static_cast<unsigned long>(th1->GetEntries()), sumWtot, sumW2tot, 0, 0);

    Histo1D* rtn =new Histo1D(bins, dbn_tot, dbn_uflow, dbn_oflow,std::string("/")+fname+std::string("/")+th1->GetName(), th1->GetTitle());
    rtn->setAnnotation("XLabel", th1->GetXaxis()->GetTitle());
    rtn->setAnnotation("YLabel", th1->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+th1->GetTitle());
    return rtn;
}

Scatter2D* TH1toScatter2D(const TH1* th1, std::string fname)
{
    Scatter2D* rtn = new Scatter2D(std::string("/")+fname+std::string("/")+th1->GetName());
    for (int i = 1; i <= th1->GetNbinsX(); ++i)
        {
            const double x = th1->GetBinCenter(i);
            const double exminus = x - th1->GetBinLowEdge(i);
            const double explus = th1->GetBinLowEdge(i+1) - x;
            const double width = exminus + explus;
            rtn->addPoint(x, th1->GetBinContent(i)/width,
                          exminus, explus,
                          th1->GetBinErrorLow(i)/width, th1->GetBinErrorUp(i)/width);
        }
    rtn->setAnnotation("XLabel", th1->GetXaxis()->GetTitle());
    rtn->setAnnotation("YLabel", th1->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+th1->GetTitle());
    return rtn;
}




Profile1D*         TProfiletoProfile1D(const TProfile* p, std::string fname)
{


    Profile1D* rtn = new Profile1D(std::string("/")+fname+std::string("/")+p->GetName());
    for (int i = 1; i <= p->GetNbinsX(); ++i)
        {
            const double x = p->GetBinCenter(i);
            const double exminus = x - p->GetBinLowEdge(i);
            const double explus = p->GetBinLowEdge(i+1) - x;
            const double width = exminus + explus;
//FIXME      rtn->addPoint(x, p->GetBinContent(i)/width, exminus, explus,  p->GetBinErrorLow(i)/width, p->GetBinErrorUp(i)/width);
        }
    rtn->setAnnotation("XLabel", p->GetXaxis()->GetTitle());
    rtn->setAnnotation("YLabel", p->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+p->GetTitle());
    return rtn;

}


Scatter2D* TGraphtoScatter2D(const TGraph* g, std::string fname)
{
    Scatter2D* rtn = new Scatter2D(std::string("/")+fname+std::string("/")+g->GetName());
    int i;
    for (i=0; i<g->GetN()-1; i++)
        {
            double x,y;
            g->GetPoint(i,x,y);
            rtn->addPoint(x, y,
                          g->GetErrorXlow(i),
                          g->GetErrorXhigh(i),
                          g->GetErrorYlow(i),
                          g->GetErrorYhigh(i)
                         );
        }
    rtn->addAnnotation("XLabel", g->GetXaxis()->GetTitle());
    rtn->addAnnotation("YLabel", g->GetYaxis()->GetTitle());
    rtn->setAnnotation("Title", std::string("/")+g->GetTitle());
    return rtn;
}



TH1D* Histo1DtoTH1D(const Histo1D* h)
{
    // Work out bin edges first
    std::vector<double> edges;
    edges.reserve(h->numBins()+1);
    edges.push_back(h->bin(0).lowEdge());
    for (size_t i = 0; i < h->numBins(); ++i)
        {
            const HistoBin1D& b = h->bin(i);
            if (!fuzzyEquals(edges.back(), b.lowEdge())) edges.push_back(b.lowEdge());
            if (!fuzzyEquals(edges.back(), b.highEdge())) edges.push_back(b.highEdge());
        }
    // Book ROOT histogram
    TH1D* rtn= new TH1D(h->path().c_str(), h->title().c_str(), edges.size()-1, &edges[0]);
    rtn->Sumw2();
    TArrayD* sumw2s = new TArrayD(*(rtn->GetSumw2()));
    for (int i = 1; i <= rtn->GetNbinsX(); ++i)
        {
            try
                {
                    const HistoBin1D& b = h->binAt(rtn->GetBinCenter(i)); // throws if in a gap
                    rtn->SetBinContent(i, b.sumW());
                    //FIXME sumw2s[i] = b.sumW2();
                }
            catch (const Exception& e) {  }
        }
    // Overflows
    rtn->SetBinContent(0, h->underflow().sumW());
    rtn->SetBinContent(rtn->GetNbinsX()+1, h->overflow().sumW());
    //FIXME  sumw2s[0] = h->underflow().sumW2();
    //FIXME  sumw2s[rtn->GetNbinsX()+1] = h->overflow().sumW2();
    // Labels
    if (h->hasAnnotation("XLabel")) rtn->SetXTitle(h->annotation("XLabel").c_str());
    if (h->hasAnnotation("YLabel")) rtn->SetYTitle(h->annotation("YLabel").c_str());

    return rtn;
}


TProfile* Profile1DtoTProfile(const Profile1D* p)
{
    // Work out bin edges first
    std::vector<double> edges;
    edges.reserve(p->numBins()+1);
    edges.push_back(p->bin(0).lowEdge());
    for (size_t i = 0; i < p->numBins(); ++i)
        {
            const ProfileBin1D& b = p->bin(i);
            if (!fuzzyEquals(edges.back(), b.lowEdge())) edges.push_back(b.lowEdge());
            if (!fuzzyEquals(edges.back(), b.highEdge())) edges.push_back(b.highEdge());
        }
    // Book ROOT histogram
    TProfile *rtn =new TProfile(p->path().c_str(), p->title().c_str(), edges.size()-1, &edges[0]);
    rtn->Sumw2();
    TArrayD* sumw2s = new TArrayD(*(rtn->GetSumw2()));
    for (int i = 1; i <= rtn->GetNbinsX(); ++i)
        {
            try
                {
                    const ProfileBin1D& b = p->binAt(rtn->GetBinCenter(i)); // throws if in a gap
                    /// @todo This part is probably wrong -- also need to do something with GetW,
                    ///   GetW2, GetB, GetB2, and/or GetBinSumw2? ROOT docs are 100% useless...
                    rtn->SetBinContent(i, b.sumW());
                    //FIXME  sumw2s[i] = b.sumW2();
                }
            catch (const Exception& e) {  }
        }
    // Overflows
    rtn->SetBinContent(0, p->underflow().sumW());
    rtn->SetBinContent(rtn->GetNbinsX()+1, p->overflow().sumW());
    //FIXME  sumw2s[0] = p->underflow().sumW2();
    //FIXME  sumw2s[rtn->GetNbinsX()+1] = p->overflow().sumW2();
    // Labels
    if (p->hasAnnotation("XLabel")) rtn->SetXTitle(p->annotation("XLabel").c_str());
    if (p->hasAnnotation("YLabel")) rtn->SetYTitle(p->annotation("YLabel").c_str());
    return rtn;
}



TGraphAsymmErrors* Scatter2DtoTGraphAsymmErrors(const Scatter2D* s)
{
    TVectorF xs(s->numPoints()), ys(s->numPoints());
    TVectorF exls(s->numPoints()), exhs(s->numPoints());
    TVectorF eyls(s->numPoints()), eyhs(s->numPoints());
    for (size_t i = 0; i < s->numPoints(); ++i)
        {
            const Point2D& p = s->point(i);
            xs[i] = p.x();
            ys[i] = p.y();
            exls[i] = p.xErrMinus();
            exhs[i] = p.xErrPlus();
            eyls[i] = p.yErrMinus();
            eyhs[i] = p.yErrPlus();
        }
    // Make the ROOT object... mm, the constructors don't take name+title, unlike all this histos!
    TGraphAsymmErrors* rtn= new TGraphAsymmErrors(xs, ys, exls, exhs, eyls, eyhs);
    rtn->SetName(s->path().c_str());
    rtn->SetTitle(s->title().c_str());
    // Labels
    if (s->hasAnnotation("XLabel")) rtn->GetXaxis()->SetTitle(s->annotation("XLabel").c_str());
    if (s->hasAnnotation("YLabel")) rtn->GetYaxis()->SetTitle(s->annotation("YLabel").c_str());
    return rtn;
}

//@}


}

#endif
