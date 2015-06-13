#include "Helpers.h"

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
#ifndef SIMPLE_HELPERS_ONLY

void H_inserter(std::map<std::string,TH1D*> &A,std::string t, Int_t s, const Double_t a[])
{
    A.insert(std::pair<std::string,TH1D*>( t,new TH1D(t.c_str(),t.c_str(),s,a)));
    for (int b = 0; b < A[t]->GetNbinsX(); b++) A[t]->GetXaxis()->SetBinLabel(b+1,Form("%i",b));
    //A[t]->SetBinErrorOption( TH1::EBinErrorOpt::kPoisson);
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
