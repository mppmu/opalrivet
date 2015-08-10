#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h" 
#include "TAdvancedGraph.h"
#include "TH1D.h"
int main(int argc, char** argv)
{
	
	    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;
TFile* type_fFile= new TFile(argv[3], "READ");
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



TFile* fFile= new TFile(argv[1], "RECREATE");
fFile->cd();

//printf("vvvv %i\n",fHMap.size());

for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it)
{
	std::string name(H_it->first);
	//if ((name.find("h986")!=std::string::npos)||(name.find("h186")!=std::string::npos))
//"/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i
/*
      int offset = 0;
      switch (int(sqrtS()/GeV + 0.5)) {
      case 35: offset = 7; break;
      case 44: offset = 8; break;
      case 91: offset = 9; break;
      case 133: offset = 10; break;
      case 161: offset = 11; break;
      case 172: offset = 12; break;
      case 183: offset = 13; break;
      case 189: offset = 14; break;
      default: break;
      }
      for (size_t i = 0; i < 5; ++i) {
        _h_R_Jade[i] = bookHisto1D(offset, 1, i+1);
        _h_R_Durham[i] = bookHisto1D(offset+9, 1, i+1);
        if (i < 4) _h_y_Durham[i] = bookHisto1D(offset+17, 1, i+1);
      }
    }

*/


		
		replace_all(name,"/REF/JADE_OPAL_2000_S4300807a","H_olddata");
		int offsets[]={9,10,11,12,13,14};
		int energies[]={91,133,161,172,183,189};
		for (size_t i = 0; i < 5; i++) 
		for (size_t j = 0; j < 5; j++) 
		{
		replace_all(name,Form("/d%02d-x01-y%02d",offsets[j],  i+1),Form("_jade_%dGeV_JETR%d",  energies[j],i+2));
	    replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]+9,i+1),Form("_durham_%dGeV_JETR%d",energies[j],i+2));
	    }
/*
		replace_all(name,"0000","1-T");
		replace_all(name,"0001","T-Min");
		replace_all(name,"0002","T-Maj");
		replace_all(name,"0003","A");
		replace_all(name,"0004","CP");
		replace_all(name,"0005","MH");		
		replace_all(name,"0006","S");
		replace_all(name,"0007","O");
		replace_all(name,"0008","BT");
		replace_all(name,"0009","BW");
		replace_all(name,"0010","D2");
		replace_all(name,"0011","T");
		replace_all(name,"0012","MH2");
		replace_all(name,"0013","JTE0");		
		replace_all(name,"0014","DP");
		replace_all(name,"0015","JETR2");
		replace_all(name,"0016","JETR3");
		replace_all(name,"0017","JETR4");
		replace_all(name,"0018","JETR5");
		replace_all(name,"0019","JETR6");
		replace_all(name,"0020","ML");
		replace_all(name,"0021","BN");											
*/
puts(name.c_str());
		H_it->second->SetName(name.c_str());
		
}	


for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it)
{
	    std::string name(G_it->first);
		replace_all(name,"/REF/JADE_OPAL_2000_S4300807a","olddata");
		int offsets[]={9,10,11,12,13,14};
		int energies[]={91,133,161,172,183,189};
		for (size_t i = 0; i < 5; i++) 
		for (size_t j = 0; j < 5; j++) 
		{
		replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]  ,i+1),Form("_jade_%dGeV_JETR%d",  energies[j],i+2));
	    replace_all(name,Form("/d%02d-x01-y%02d",offsets[j]+9,i+1),Form("_durham_%dGeV_JETR%d",energies[j],i+2));
	    }
puts(name.c_str());
		G_it->second->SetName(("G_"+name).c_str());
		fHMap.insert(std::pair<std::string,TH1D*> (std::string("H_")+name, G_it->second->ToTH1D(std::string("H_")+name,0)));
		fHMap[std::string("H_")+name]->Scale(0.01);
}	









fFile->cd();

    for (std::map<std::string,TAdvancedGraph*>::iterator G_it=fGMap.begin(); G_it!=fGMap.end(); ++G_it) 	G_it->second->Write(0,TObject::kWriteDelete);
    for (std::map<std::string,TH1D*>::iterator H_it=fHMap.begin(); H_it!=fHMap.end(); ++H_it) 
    if (std::string(H_it->second->GetName()).find("H_olddata_")!=std::string::npos) 
    {H_it->second->SetDirectory(fFile); H_it->second->Write(0,TObject::kWriteDelete); }
    
printf("%i\n",fHMap.size());
printf("%i\n",fGMap.size());
fFile->Close();

}
