#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
#include "TAdvancedGraph.h"
int main(int argc, char* argv[])
{
	  //TApplication* theApp = new TApplication("App", &argc, argv);
	    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
for (int i=1;i<argc;i++)
{
TFile* type_fFile= new TFile(argv[i], "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj  ) );  fHMap[std::string(key->GetName())]->SetDirectory(0); }
            if ( obj->IsA()->InheritsFrom( "TGraph" ) ) { fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   ); 
				}
        }

type_fFile->Close();
}




std::string algorithm="durham";
std::vector<std::string> generators=return_tokenize("corrected:pythia8",":");
std::string energy="207GeV";
std::vector<std::string>  quantities=return_tokenize("JETR2:JETR3:JETR4:JETR5:JETR6",":");

TCanvas* C=new TCanvas(algorithm.c_str());
C->Divide(sqrt(quantities.size())+1,sqrt(quantities.size())+1);
int ican=1;
gStyle->SetOptStat(0);
for (std::vector<std::string>::iterator quantity=quantities.begin();quantity!=quantities.end();quantity++)
{

C->cd(ican);
//C->SetLogx();
 gPad->SetLogx();
ican++;
TLegend* L= new TLegend(0.75,0.7,0.95,0.9);
std::string option="";
for (std::vector<std::string>::iterator generator=generators.begin();generator!=generators.end();generator++)
{
	
std::string name=	"H_"+*generator+"_"+algorithm+"_"+energy+"_"+*quantity;
if (fHMap.find(name)!=fHMap.end()) 
{
fHMap[name]->SetTitle(";;Fraction");	
fHMap[name]->Draw(option.c_str());
fHMap[name]->Draw("ASAME");

    fHMap[name]->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
    fHMap[name]->GetYaxis()->SetRangeUser(0,1.25);

L->AddEntry(fHMap[name],(*quantity+" "+*generator).c_str(),"P");



option="same";
}
else puts("Not Found");


}
L->Draw();

}

C->SaveAs(("output/plots_"+energy+".root").c_str());
C->SaveAs(("output/plots_"+energy+".pdf").c_str());


printf("%i\n",fHMap.size());
for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
{
	std::string name(H_it->first);
	//puts(name.c_str());
	if ((name.find("h986")!=std::string::npos)||(name.find("h186")!=std::string::npos))
	{ 
		
	}
}	
//theApp->Run();
}
