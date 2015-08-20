#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h"
#include "TAdvancedGraph.h"

TAdvancedGraph* GetSystematicsGraph(std::vector<TAdvancedGraph*> GG)
{
	TAdvancedGraph* R= new TAdvancedGraph(GG[0]->GetN());
for (int i=0;i<GG[0]->GetN();i++)	
{
double x,y;
GG[0]->GetPoint(i,x,y);
//R->GetPoint(i,x,y);
R->SetPoint(i,x,0);
R->SetPointError(i,0,0,0,0);
for (int j=1;j<GG.size();j++)	
{
double xj,yj;
GG[j]->GetPoint(i,xj,yj);
R->SetPointError(i,0,0,std::max(R->GetErrorYlow(i),y-yj),std::max(R->GetErrorYhigh(i),yj-y));
printf("%f %f\n",R->GetErrorYlow(i),R->GetErrorYhigh(i));
}
}	
return R;
}	


std::map<std::string,TAdvancedGraph*> GetGraphs(std::string file)
{
std::map<std::string,TAdvancedGraph*> f;	
	
TFile* type_fFile= new TFile(file.c_str(), "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            
            if ( obj->IsA()->InheritsFrom( "TGraph" ) )
                {
                    f.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
                }
        }

    type_fFile->Close();


return f;	
}	




int main(int argc, char* argv[])
{
    //TApplication* theApp = new TApplication("App", &argc, argv);
    std::map<std::string,std::map<std::string,TH1D*> > fHMaps;
    std::map<std::string,std::map<std::string,TAdvancedGraph*> > fGMaps;





for (int i=2; i<argc; i++)
{
std::vector<std::string> files=return_tokenize(argv[i],":");
for (std::vector<std::string>::iterator it=files.begin();it!=files.end();it++)
{
fGMaps.insert(std::pair<std::string,std::map<std::string,TAdvancedGraph*> >(*it,GetGraphs(std::string("output/opal_")+std::string(argv[1])+"_"+*it+std::string(".root"))));
//fHMaps.insert(std::map<std::string,std::map<std::string,TH1D*> >(*it,GetHistos(std:string("output/opal_")+*it+std::string(".root"))));	
}	
}	


for (int i=2; i<argc; i++)
{
if (std::string(argv[i])=="central") continue;

std::vector<std::string> files=return_tokenize(argv[i],":");

for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMaps["central"].begin(); G_it!=fGMaps["central"].end(); G_it++)
{
std::vector<TAdvancedGraph*> GG;
GG.push_back(G_it->second);
for (std::vector<std::string>::iterator it=files.begin();it!=files.end();it++) GG.push_back(fGMaps[*it][G_it->first]);
fGMaps[Form("systematicsN%i",i)][G_it->first]=GetSystematicsGraph(GG);
printf("OK %i  %s\n",i,G_it->first.c_str());
}
}


TCanvas * q= new TCanvas();
q->cd();
fGMaps["systematicsN3"]["G_data_durham_161GeV_1-T"]->Draw("APL");
q->SaveAs("q.root");





}
