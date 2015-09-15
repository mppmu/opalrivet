#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include "Helpers.h"
#include "Cuts.h"
#include "TFastJet.h"
#include "TAdvancedGraph.h"


void PrintTG(std::map<std::string,TAdvancedGraph*> fGMap, FILE* f, std::string command)
{
    if (fGMap.size()==0) return;


    puts(fGMap.begin()->first.c_str());
    std::vector<std::string> na;
    std::string newcommand="G";
    tokenize(fGMap.begin()->first,"_",na);
    for (int i=2; i<na.size(); i++) newcommand+=na[i];
    if (command==std::string("")) command=newcommand;


    replace_all(command,"1","one");
    replace_all(command,"2","two");
    replace_all(command,"3","three");
    replace_all(command,"4","four");
    replace_all(command,"5","five");
    replace_all(command,"6","six");
    replace_all(command,"7","seven");
    replace_all(command,"8","eight");
    replace_all(command,"9","nine");
    replace_all(command,"0","zero");
    replace_all(command,"-","minus");
    replace_all(command,"+","plus");




    if (f==0) f= stdout;

    TAdvancedGraph* Z = new TAdvancedGraph(0);
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        Z->Add(Z,C->second,0.0,0.0)	;
    int N=Z->GetN();
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        C->second->Add(C->second,Z,1.0,0.0);

    fprintf(f,"\\newcommand{\\%s}[2]{\n",command.c_str());
    fprintf(f,"\\begin{table}\n\\begin{tabular}{|c|");
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        fprintf(f,"c|");
    fprintf(f,"}\\hline\n");


    fprintf(f,"#1");
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        {
            na.clear();
            tokenize(C->first,"_",na);
            fprintf(f,"&\\%s",na[1].c_str());

        }
    fprintf(f,"\\\\\\hline\\hline\n");

    for (int i=0; i<N; i++)
        {
            int firstc=1;
            for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
                {
                    double x,y;
                    C->second->GetPoint(i,x,y);
                    y=std::abs(y);
                    if (firstc) { fprintf(f,"$%f$",x); firstc=0;}
                    fprintf(f,"&$%3.3f^{+%3.3f}_{-%3.3f}$",y,C->second->GetErrorYhigh(i),C->second->GetErrorYlow(i));
                }
            fprintf(f,"\\\\\n");
        }
    fprintf(f,"\\hline\\end{tabular}\\caption{#2}\n\\end{table}}\n");

}



void PrintTH(std::map<std::string,TH1D*> fHMap, FILE* f, std::string command)
{
    if (fHMap.size()==0) return;



//	      puts(fGMap.begin()->first.c_str());
    std::vector<std::string> na;
    std::string newcommand="H";
    tokenize(fHMap.begin()->first,"_",na);
    for (int i=2; i<na.size(); i++) newcommand+=na[i];
    if (command==std::string("")) command=newcommand;

    replace_all(command,"1","one");
    replace_all(command,"2","two");
    replace_all(command,"3","three");
    replace_all(command,"4","four");
    replace_all(command,"5","five");
    replace_all(command,"6","six");
    replace_all(command,"7","seven");
    replace_all(command,"8","eight");
    replace_all(command,"9","nine");
    replace_all(command,"0","zero");
    replace_all(command,"-","minus");
    replace_all(command,"+","plus");



    if (f==0) f= stdout;

    //TH1D* Z = new TH1D(0);
    //for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
    //Z->Add(Z,C->second,0.0,0.0)	;
    int N=fHMap.begin()->second->GetNbinsX();
    //for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
    //C->second->Add(C->second,Z,1.0,0.0);

    fprintf(f,"\\newcommand{\\%s}[2]{\n",command.c_str());
    fprintf(f,"\\begin{table}\n\\begin{tabular}{|c|");
    for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
        fprintf(f,"c|");
    fprintf(f,"}\\hline\n");


    fprintf(f,"#1");
    for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
        {
            na.clear();
            tokenize(C->first,"_",na);
            fprintf(f,"&\\%s",na[1].c_str());

        }
    fprintf(f,"\\\\\\hline\\hline\n");

    for (int i=0; i<N; i++)
        {
            int firstc=1;
            for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
                {
                    double x,y;
                    y=C->second->GetBinContent(i);
                    y=std::abs(y);
                    if (firstc) { fprintf(f,"$%f:%f$",C->second->GetBinLowEdge(i),C->second->GetBinLowEdge(i)+C->second->GetBinWidth(i)); firstc=0;}
                    fprintf(f,"&$%3.3f^{+%3.3f}_{-%3.3f}$",y,C->second->GetBinError(i),C->second->GetBinError(i));
                }
            fprintf(f,"\\\\\n");
        }
    fprintf(f,"\\hline\\end{tabular}\\caption{#2}\n\\end{table}}\n");

}







int main(int argc, char* argv[])
{

    FILE * FF;
    FF= fopen(argv[2],"w");

    std::map<std::string,TCanvas*> fCMap;
    TFile* type_fFile= new TFile(argv[1], "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();

            if ( obj->IsA()->InheritsFrom( "TCanvas"    ) )
                {
                    fCMap.insert(std::pair<std::string,TCanvas*> (std::string(key->GetName()) ,(TCanvas*)obj  ) );
                    //fCMap[std::string(key->GetName())]->SetDirectory(0);
                }

            //if ( obj->IsA()->InheritsFrom( "TH1"    ) ) { fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj  ) );  fHMap[std::string(key->GetName())]->SetDirectory(0); }
            //if ( obj->IsA()->InheritsFrom( "TGraph" ) )
            //  {
            //    fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
            //}
        }
    type_fFile->Close();

    std::vector<std::string> algorithms=return_tokenize(ALGORITHMS,":");



    for (std::map<std::string,TCanvas*>::iterator C=fCMap.begin(); C!=fCMap.end(); C++)
        {
            //puts(C->first.c_str());

            //TVirtualPad* c1;
            int i=1;
            //C->second->ls();
            for (i=0; i<C->second->GetListOfPrimitives()->GetSize(); i++)
                {
                    if (i%2==1) continue;
                    //;

                    //puts("OK");
                    std::map<std::string,TH1D*> fHMap;
                    std::map<std::string,TAdvancedGraph*> fGMap;
                    TObject *obj2;
                    TIter next2(((TPad*)C->second->GetListOfPrimitives()->At(i))->GetListOfPrimitives());
                    while ((obj2=next2()))
                        {
                            //       cout << "Reading: " << obj->GetName() << endl;
                            if (obj2->InheritsFrom("TH1D"))
                                {
                                    TH1D* z= (TH1D*)obj2;
                                    fHMap.insert(std::pair<std::string,TH1D*> (std::string(z->GetName()) , z ) );

                                }

                            if ( obj2->IsA()->InheritsFrom( "TGraph" ) )
                                {
                                    TAdvancedGraph* z= (TAdvancedGraph*)obj2;
                                    fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(z->GetName()) , z ) );
                                }


//	   cout << "histo: " << obj->GetName() << endl;
                        }



                    //   printf("Pad %i: %i %i\n",i,fGMap.size(),fHMap.size());
                    PrintTG(fGMap,FF,"");
                    PrintTH(fHMap,FF,"");





                }




        }

    fclose(FF);
    for (std::vector<std::string>::iterator algorithm=algorithms.begin(); algorithm!=algorithms.end(); algorithm++)
        {


        }

}
