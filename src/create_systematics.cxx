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
	TAdvancedGraph* R(GG[0]);
for (int i=0;i<GG[0]->GetN();i++)	
{
double x,y;
R->GetPoint(i,x,y);
R->SetPoint(i,x,0);
for (int j=1;j<GG.size();i++)	
{
double xj,yj;
GG[j]->GetPoint(i,xj,yj);
R->SetPointError(i,0,std::max(R->GetPointErrorY(i),std::abs(y-yj)));
}
}	
return R;
}	


std::map<std::string,TAdvancedGraph*> GetGraphs(std::string file)
{
std::map<std::string,TAdvancedGraph*> f;	
	



return f;	
}	




int main(int argc, char* argv[])
{
    //TApplication* theApp = new TApplication("App", &argc, argv);
    std::map<std::string,std::map<std::string,TH1D*> > fHMaps;
    std::map<std::string,std::map<std::string,TAdvancedGraph*> > fGMaps;





for (int i=1; i<argc; i++)
{
std::vector files=return_tokenize(argv[i],":");
for (std::vector<std::string>::iterator it=files.begin();it!=files.end();it++)
{
fGMaps.insert(std::map<std::string,std::map<std::string,TAdvancedGraph*> >(*it,GetGraphs(std:string("output/opal_")+*it+std::string(".root"))));
//fHMaps.insert(std::map<std::string,std::map<std::string,TH1D*> >(*it,GetHistos(std:string("output/opal_")+*it+std::string(".root"))));	
}	
}	


for (int i=1; i<argc; i++)
{
if (std::string(argv[i])=="central") continue;

std::vector files=return_tokenize(argv[i],":");

for (std::map<std::string,TAdvancedGraph*>:itearator G_it=fGMaps["central"].begin(); G_it!=fGMaps["central"].end(); G_it++)
{
std::vector<TAdvancedGraph*> GG;
GG.push_back(G_it->second)
for (std::vector<std::string>::iterator it=files.begin();it!=files.end();it++) GG.push_back(fGMaps[*it][G_it->first]);
fGMaps[Form("systematicsN%i",i).Data()][G_it->first]=GetSystematicsGraph(GG);
}
}








}
