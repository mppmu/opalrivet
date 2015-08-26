#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h"
#include "TAdvancedGraph.h"

TAdvancedGraph* GetSystematicsGraph(std::vector<TAdvancedGraph*> GG,std::string name)
{
    TAdvancedGraph* R= new TAdvancedGraph(GG[0]->GetN());
    R->SetName(name.c_str());
    for (int i=0; i<GG[0]->GetN(); i++)
        {
            double x,y;
            GG[0]->GetPoint(i,x,y);
//R->GetPoint(i,x,y);
            R->SetPoint(i,x,0);
            R->SetPointError(i,0,0,0,0);
            for (int j=1; j<GG.size(); j++)
                {
                    double xj,yj;
                    GG[j]->GetPoint(i,xj,yj);
                    R->SetPointError(i,0,0,std::max(R->GetErrorYlow(i),y-yj),std::max(R->GetErrorYhigh(i),yj-y));

//R->SetPoint(i,xj,R->GetErrorYlow(i));
//printf("%f %f\n",R->GetErrorYlow(i),R->GetErrorYhigh(i));
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





TH1D* GetSystematicsHisto(std::vector<TH1D*> HH,std::string name)
{
    TH1D* R= new TH1D();
    if (!HH[0]) printf("Strange %i\n",HH.size());
    else
        R= (TH1D*)(HH[0]->Clone());

    R->SetName(name.c_str());
    for (int i=0; i<HH[0]->GetNbinsX(); i++)
        {
            double x,y;
            y=HH[0]->GetBinContent(i);
//R->HetPoint(i,x,y);
//R->SetPoint(i,x,0);
            R->SetBinContent(i,0);
            for (int j=1; j<HH.size(); j++)
                {
                    double xj,yj;
                    yj=HH[j]->GetBinContent(i,yj);
                    R->SetBinError(i,std::max(R->GetBinError(i),y-yj),std::max(R->GetBinError(i),yj-y));

//R->SetPoint(i,xj,R->HetErrorYlow(i));
//printf("%f %f\n",R->HetErrorYlow(i),R->HetErrorYhigh(i));
                }
        }
    return R;
}


std::map<std::string,TH1D*> GetHistos(std::string file)
{
    std::map<std::string,TH1D*> f;

    TFile* type_fFile= new TFile(file.c_str(), "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();

            if ( obj->IsA()->InheritsFrom( "TH1" ) )
                {
                    f.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
                    f[std::string(key->GetName())]->SetDirectory(0);
                }
        }

    type_fFile->Close();


    return f;
}












int main(int argc, char* argv[])
{

    TFile* q=new TFile((std::string("output/opal_")+std::string(argv[1])+std::string(".root")).c_str(),"recreate");
    q->cd();



    std::map<std::string,std::map<std::string,TAdvancedGraph*> > fGMaps;



    for (int i=2; i<argc; i++)
        {
            std::vector<std::string> files=return_tokenize(argv[i],":");
            for (std::vector<std::string>::iterator it=files.begin(); it!=files.end(); it++)
                {
                    fGMaps.insert(std::pair<std::string,std::map<std::string,TAdvancedGraph*> >(*it,GetGraphs(std::string("output/opal_")+std::string(argv[1])+"_"+*it+std::string(".root"))));
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
                    for (std::vector<std::string>::iterator it=files.begin(); it!=files.end(); it++) GG.push_back(fGMaps[*it][G_it->first]);
                    fGMaps[Form("systematicsN%i",i)][G_it->first+"_systematics_"+std::string(argv[i])]=GetSystematicsGraph(GG,G_it->first+"_systematics_"+std::string(argv[i]));
                }

            for (std::map<std::string,TAdvancedGraph*>::iterator gG_it=fGMaps[Form("systematicsN%i",i)].begin(); gG_it!=fGMaps[Form("systematicsN%i",i)].end(); ++gG_it) {	q->cd(); gG_it->second->Write();}
        }

    int copiedg=0;
    for (int i=2; i<argc; i++)
        {
            if (std::string(argv[i])=="central") continue;

            if (!copiedg)
                {
                    fGMaps["systematics"]=fGMaps["central"];
                    for (std::map<std::string,TAdvancedGraph*>::iterator gG_it=fGMaps["systematics"].begin(); gG_it!=fGMaps["systematics"].end(); ++gG_it)
                        {
                            gG_it->second= fGMaps[Form("systematicsN%i",i)][gG_it->first+"_systematics_"+std::string(argv[i])];
                            gG_it->second->SetName((gG_it->first+"_systematics").c_str());
                        }
                }
            else
                {
                    for (std::map<std::string,TAdvancedGraph*>::iterator gG_it=fGMaps["systematics"].begin(); gG_it!=fGMaps["systematics"].end(); ++gG_it)
                        gG_it->second->Add(gG_it->second,fGMaps[Form("systematicsN%i",i)][gG_it->first],1.0,1.0);
                }
        }


    for (std::map<std::string,TAdvancedGraph*>::iterator gG_it=fGMaps["central"].begin(); gG_it!=fGMaps["central"].end(); ++gG_it)        {	q->cd();  gG_it->second->Write(); }
    for (std::map<std::string,TAdvancedGraph*>::iterator gG_it=fGMaps["systematics"].begin(); gG_it!=fGMaps["systematics"].end(); ++gG_it) {	q->cd();  gG_it->second->Write(); }







    std::map<std::string,std::map<std::string,TH1D*> > fHMaps;












    for (int i=2; i<argc; i++)
        {
            std::vector<std::string> files=return_tokenize(argv[i],":");
            for (std::vector<std::string>::iterator it=files.begin(); it!=files.end(); it++)
                {
                    fHMaps.insert(std::pair<std::string,std::map<std::string,TH1D*> >(*it,GetHistos(std::string("output/opal_")+std::string(argv[1])+"_"+*it+std::string(".root"))));
                }
        }

    for (int i=2; i<argc; i++)
        {
            if (std::string(argv[i])=="central") continue;

            std::vector<std::string> files=return_tokenize(argv[i],":");

            for (std::map<std::string,TH1D*>::iterator H_it=fHMaps["central"].begin(); H_it!=fHMaps["central"].end(); H_it++)
                {
                    std::vector<TH1D*> HH;
                    HH.push_back(H_it->second);
                    for (std::vector<std::string>::iterator it=files.begin(); it!=files.end(); it++) HH.push_back(fHMaps[*it][H_it->first]);
                    fHMaps[Form("systematicsN%i",i)][H_it->first+"_systematics_"+std::string(argv[i])]=GetSystematicsHisto(HH,H_it->first+"_systematics_"+std::string(argv[i]));
                }

            for (std::map<std::string,TH1D*>::iterator gH_it=fHMaps[Form("systematicsN%i",i)].begin(); gH_it!=fHMaps[Form("systematicsN%i",i)].end(); ++gH_it) {	q->cd(); gH_it->second->Write();}
        }

    int copiedh=0;
    for (int i=2; i<argc; i++)
        {
            if (std::string(argv[i])=="central") continue;

            if (!copiedh)
                {
                    fHMaps["systematics"]=fHMaps["central"];
                    for (std::map<std::string,TH1D*>::iterator gH_it=fHMaps["systematics"].begin(); gH_it!=fHMaps["systematics"].end(); ++gH_it)
                        {
                            gH_it->second= fHMaps[Form("systematicsN%i",i)][gH_it->first+"_systematics_"+std::string(argv[i])];
                            gH_it->second->SetName((gH_it->first+"_systematics").c_str());
                        }
                }
            else
                {
                    for (std::map<std::string,TH1D*>::iterator gH_it=fHMaps["systematics"].begin(); gH_it!=fHMaps["systematics"].end(); ++gH_it)
                        gH_it->second->Add(gH_it->second,fHMaps[Form("systematicsN%i",i)][gH_it->first],1.0,1.0);
                }
        }


    for (std::map<std::string,TH1D*>::iterator gH_it=fHMaps["central"].begin(); gH_it!=fHMaps["central"].end(); ++gH_it)        {	q->cd();  gH_it->second->Write(); }
    for (std::map<std::string,TH1D*>::iterator gH_it=fHMaps["systematics"].begin(); gH_it!=fHMaps["systematics"].end(); ++gH_it) {	q->cd();  gH_it->second->Write(); }



















    q->Close();













}
