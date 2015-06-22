#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
#include "TAdvancedGraph.h"
int main(int argc, char** argv)
{
	
	    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;

for (int i=2;i<argc;i++)
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



TFile* fFile= new TFile(argv[1], "RECREATE");
fFile->cd();


for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
{
	std::string name(H_it->first);
	if (name.find("h986")!=std::string::npos)
	{ 
		
		replace_all(name,"h986","H_corrected_data_antikt_192GeV_");
		replace_all(name,"0000","1-T");
		replace_all(name,"0001","T-Min");
		replace_all(name,"0002","T-Maj");
		replace_all(name,"0003","A");
		H_it->second->SetName(name.c_str());
		
	}
//if (==)	
	
}	


    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) {H_it->second->SetDirectory(fFile); H_it->second->Write(0,TObject::kWriteDelete); }
    
printf("%i\n",fHMap.size());
printf("%i\n",fGMap.size());
fFile->Close();

}
