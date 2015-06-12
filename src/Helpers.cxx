#include "Helpers.h"


void set_my_style()
{
    gStyle->SetFrameFillColor(kWhite);
    gStyle->SetPadColor(kWhite);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetStatColor(kWhite);
    gStyle->SetTitleFillColor(kWhite);
    gStyle->SetCanvasDefH(768);
    gStyle->SetCanvasDefW(1024);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetMarkerColor(kBlue);
    gStyle->SetMarkerSize(15);
    gStyle->SetHistFillColor(kYellow);
    gStyle->SetOptStat(kFALSE);

    gStyle->SetLegendBorderSize(0);

    gStyle->SetStatColor(kWhite);

    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);

    gStyle->SetTitleFillColor(kWhite);


}



//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
void tokenize(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
}
//http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string
void replace_all(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
}

void H_inserter(std::map<std::string,TH1D*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TH1D*>( t,new TH1D(t.c_str(),t.c_str(),s,a)));
    for (int b = 0; b < A[t]->GetNbinsX(); b++) A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b));
    //A[t]->SetBinErrorOption( TH1::EBinErrorOpt::kPoisson);
}
/*
void G_inserter(std::map<std::string,TGraphAsymmErrors*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TGraphAsymmErrors*>( t,new TGraphAsymmErrors(s)));
    for (int b = 0; b < s; b++) { A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b)); A[t]->SetPoint(b,a[b],0.0); }
    A[t]->SetDrawOption("APL");
    A[t]->SetTitle(t.c_str());
    A[t]->SetName(t.c_str());
    //gDirectory->Append(A[t]);

}
*/


void G_inserter(std::map<std::string,TAdvancedGraph*> &A,std::string t, Int_t s, const Double_t a[])
{
    TAdvancedGraph* Q= new TAdvancedGraph(Int_t(s));
    A.insert(std::pair<std::string,TAdvancedGraph*>( t,Q));
    for (int b = 0; b < s; b++) { A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b)); A[t]->SetPoint(b,a[b],0.0); }
    A[t]->SetDrawOption("APL");
    A[t]->SetTitle(t.c_str());
    A[t]->SetName(t.c_str());
    //gDirectory->Append(A[t]);

}





#ifndef SIMPLE_HELPERS_ONLY

std::string ROOT_to_YODA_name(std::string a)//FIXME. Random so far
{

    std::vector<std::string> tokens;
    tokenize(a,"_",tokens);
    if (tokens.size()<4) return a;

    int i_d=100000;
    int i_x=100000;
    int i_y=100000;

    int iconv=0;

    int energy;
    char alg[256];




    sscanf(tokens.at(1).c_str(),"%s",alg);
    sscanf(tokens.at(2).c_str(),"%iGeV",&energy);
    std::string sname;
    unsigned int i;
    for (i=3; i<tokens.size(); i++) {sname+=tokens.at(i); if (i!=tokens.size()-1)sname+="_";}

    int i_energy=100000;

    switch (energy)
        {
        case 35:
            i_energy = 7;
            iconv++;
            break;
        case 44:
            i_energy = 8;
            iconv++;
            break;
        case 91:
            i_energy = 9;
            iconv++;
            break;
        case 133:
            i_energy = 10;
            iconv++;
            break;
        case 161:
            i_energy = 11;
            iconv++;
            break;
        case 172:
            i_energy = 12;
            iconv++;
            break;
        case 183:
            i_energy = 13;
            iconv++;
            break;
        case 189:
            i_energy = 14;
            iconv++;
            break;
        default:
            break;
        }

    std::string salg(alg);
    if (salg=="jade")   {iconv++; i_d=i_energy; }
    if (salg=="durham") {iconv++; i_d=9+i_energy;}


    if (sname=="JETR2") {iconv++; i_x=1; i_y=1;}
    if (sname=="JETR3") {iconv++; i_x=1; i_y=2;}
    if (sname=="JETR4") {iconv++; i_x=1; i_y=3;}
    if (sname=="JETR5") {iconv++; i_x=1; i_y=4;}
    if (sname=="JETR6") {iconv++; i_x=1; i_y=5;}



    std::stringstream axisCode;
    axisCode << "d";
    if (i_d < 10) axisCode << 0;
    axisCode << i_d;//datasetId;
    axisCode << "-x";
    if (i_x < 10) axisCode << 0;
    axisCode << i_x;//xAxisId;
    axisCode << "-y";
    if (i_y < 10) axisCode << 0;
    axisCode << i_y;//yAxisId;
    if (iconv==3) return axisCode.str();
    else return a;


}



void Count(TChain* C, TAnalysisInfo& A)
{
    for (int i=0; i<MAX_RUNS; i++) if (A.fNames[i]!="") A.fEvents[i]= C->Draw("Irun",Form("(%i<Irun)&&(Irun<%i)",A.fRunsBegin[i],A.fRunsEnd[i]));

}


int  Match(int run, TAnalysisInfo& Z, TH1F* H)
{
    for (int i=0; i<MAX_RUNS; i++)
        Z.fEvents[i]= H->Integral(Z.fRunsBegin[i],Z.fRunsEnd[i]);
    for (int i=0; i<MAX_RUNS; i++) if ((Z.fRunsBegin[i]<run)&& (run<Z.fRunsEnd[i])) return i;
    return -1;
}

#endif
