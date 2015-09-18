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
#ifndef HELPERS_CXX
#define HELPERS_CXX  
#include "Helpers.h"


void DivideByBinWidth(TH1D& H)
{
    double y,ye,w;
    for (int i=1; i<H.GetNbinsX(); i++)
        {
            y=H.GetBinContent(i);
            ye=H.GetBinError(i);
            w=H.GetBinWidth(i);
            H.SetBinContent(i,y/w);
            H.SetBinError(i,ye/w);
        }

}


//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
std::vector<std::string> return_tokenize(const std::string& str, const std::string& delimiters )
{
    std::vector<std::string> tokens;
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
    return tokens;
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



void create_sample_info(sample_info& A,std::string prefix,char* Es,double El,double Eh,const char* name,const char* type,const char* procs,const char* pr,const char* files,int ev,int rb,int re,
                        double lum,double sig ,double w)
{
    A.fEl=El;
    A.fEh=Eh;
    A.fEh=0.5*(Eh+El);
    A.fName=std::string(name);
    A.fPeriod=std::string(pr);
    A.fProcesses=std::string(procs);
    A.fType=std::string(type);
    A.fEvents=ev;
    A.fRunsBegin=rb;
    A.fRunsEnd=re;
    A.fSigma=sig;
    A.fLuminocity=lum;
    A.fWeight=w;
    A.fGenerator=std::string("opal");
    A.fFiles=return_tokenize(files," ");
    //char a[20];
    //sprintf(a,"%i",(int)(A.fE + 0.5));
    A.fEnergyString=std::string(Es);
    if (prefix!=std::string(""))
        {
            TH1F* TOTAL= new TH1F("TOTAL","TOTAL",20000,0,20000);
            TChain* C= new TChain("h10");
            for (std::vector<std::string>::iterator it=A.fFiles.begin(); it!=A.fFiles.end(); it++)
                C->Add((prefix+*it).c_str());
            C->Draw("Irun>>RUNHIST(20000,0.0,20000.0)",Form("(Ebeam>%f)&&(Ebeam<%f)",0.5*(A.fEl),0.5*(A.fEh)));
            TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
            TOTAL->Add(RUNHIST);
            A.fRunsBegin=TOTAL->FindFirstBinAbove(0);
            A.fRunsEnd=TOTAL->FindLastBinAbove(0);
            if (A.fRunsEnd<A.fRunsBegin) puts("Wrong run numbers of energy");
            A.fEvents=TOTAL->GetEntries();
            C->Draw("Ebeam>>EBEAMHIST(10000,40.0,140.0)",Form("(Ebeam>%f)&&(Ebeam<%f)",0.5*(A.fEl),0.5*(A.fEh)));
            TH1F* EBEAMHIST=(TH1F*)gDirectory->Get("EBEAMHIST");
            A.fEa=2.0*EBEAMHIST->GetMean();
            A.fEl=2.0*EBEAMHIST->GetBinCenter(EBEAMHIST->FindFirstBinAbove(0));
            A.fEh=2.0*EBEAMHIST->GetBinCenter(EBEAMHIST->FindLastBinAbove(0));
            TOTAL->Delete();
        }
}


#ifndef SIMPLE_HELPERS_ONLY


void FillWithLabel(TH1D* H,std::string l,double weight)
{
    for (int i=0; i<H->GetNbinsX(); i++) if (std::string(H->GetXaxis()->GetBinLabel(i))==l) H->Fill(H->GetBinCenter(i),weight);
}


void H_inserter(std::map<std::string,TH1D*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TH1D*>( t,new TH1D(t.c_str(),t.c_str(),s,a)));
    for (int b = 0; b < A[t]->GetNbinsX(); b++)
        {
            A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b));
            A[t]->SetBinContent(b,0);

        }
}

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
#endif
#endif
