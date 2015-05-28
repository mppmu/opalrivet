
#ifdef USE_RIVET



//#include "YODA/ROOTConvert.h"
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
#include "TH1D.h"
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



}

#endif

