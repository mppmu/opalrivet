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
#include "Helpers.h"
#include "Cuts.h"
#include "OPALJet.h"
#include "TAdvancedGraph.h"


void PrintTG(std::map<std::string,TAdvancedGraph*> fGMap, FILE* f,std::string nick, std::string command)
{
    if (fGMap.size()==0) return;


    puts(fGMap.begin()->first.c_str());
    std::vector<std::string> na;
    std::string newcommand="";
    tokenize(fGMap.begin()->first,"_",na);
    for (unsigned int i=2; i<na.size(); i++) newcommand+=na[i];
    if (command==std::string("")) command="TABG"+nick+newcommand;


    puts(fGMap.begin()->first.c_str());
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
    replace_all(command,"GeV","");
    replace_all(command,"_","");
    replace_all(command,".","dot");



    if (f==0) f= stdout;

    TAdvancedGraph* Z = new TAdvancedGraph(0);
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        Z->Add(Z,C->second,0.0,0.0)	;
    int N=Z->GetN();
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        C->second->Add(C->second,Z,1.0,0.0);

    puts(fGMap.begin()->first.c_str());

    puts(command.c_str());
    fprintf(f,"\\newcommand{\\%s}[2]{\n",command.c_str());
    fprintf(f,"\\begin{table}\\centering\\TABGFONTSIZE\n\\begin{tabular}{|c|");
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        if (C->first.find("systematics")==std::string::npos)        fprintf(f,"c|");
    fprintf(f,"}\\hline\n");


    fprintf(f,"#1");
    std::map<std::string,int> capmap;
    for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
        if (C->first.find("systematics")==std::string::npos)
            {
                na.clear();
                tokenize(C->first,"_",na);
                capmap.insert(std::pair<std::string,int>(na[1],0));
                capmap[na[1]]++;
                //if (capmap[na[1]]>1)
                fprintf(f,"&\\TABGCAPTION%s(%i)",na[1].c_str(),capmap[na[1]]);
//else
//fprintf(f,"&\\%s",na[1].c_str());

            }
    fprintf(f,"\\\\\\hline\\hline\n");

    for (int i=0; i<N; i++)
        {
            int firstc=1;
            for (std::map<std::string,TAdvancedGraph*>::iterator C=fGMap.begin(); C!=fGMap.end(); C++)
                {
                    if (C->first.find("systematics")!=std::string::npos) continue;
                    double x,y;
                    C->second->GetPoint(i,x,y);
                    y=std::abs(y);
                    if (firstc) { fprintf(f,"$%f$",x); firstc=0;}
                    fprintf(f,"&$%3.3f^{+%3.3f}_{-%3.3f}",y,C->second->GetErrorYhigh(i),C->second->GetErrorYlow(i));
                    if (fGMap.find(C->first+"_systematics")!=fGMap.end())
                        {
                            fprintf(f,"{}^{+%3.3f}_{-%3.3f}",fGMap[C->first+"_systematics"]->GetErrorYhigh(i),
                                    fGMap[C->first+"_systematics"]->GetErrorYlow(i));


                        }
                    fprintf(f,"$");

                }
            fprintf(f,"\\\\\n");
        }
    fprintf(f,"\\hline\\end{tabular}\\caption{#2}\n\\end{table}}\n");

}



void PrintTH(std::map<std::string,TH1D*> fHMap, FILE* f,std::string nick, std::string command)
{
    if (fHMap.size()==0) return;
    std::vector<std::string> na;
    std::string newcommand="";
    tokenize(fHMap.begin()->first,"_",na);
    for (unsigned int i=2; i<na.size(); i++) newcommand+=na[i];
    if (command==std::string("")) command="TABH"+nick+newcommand;


    replace_all(command,"_","");
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
    replace_all(command,"GeV","");
    replace_all(command,".","dot");




    if (f==0) f= stdout;
    int N=fHMap.begin()->second->GetNbinsX();
    fprintf(f,"\\newcommand{\\%s}[2]{\n",command.c_str());
    fprintf(f,"\\begin{table}\\centering\n\\begin{tabular}{|c|");
    for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
        if (C->first.find("systematics")==std::string::npos)
            fprintf(f,"c|");
    fprintf(f,"}\\hline\n");


    fprintf(f,"#1");
    for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
        if (C->first.find("systematics")==std::string::npos)
            {
                na.clear();
                tokenize(C->first,"_",na);
                fprintf(f,"&\\%s",na[1].c_str());

            }
    fprintf(f,"\\\\\\hline\\hline\n");

    for (int i=1; i<N+1; i++)
        {
            int firstc=1;
            for (std::map<std::string,TH1D*>::iterator C=fHMap.begin(); C!=fHMap.end(); C++)
                {
                    if (C->first.find("systematics")!=std::string::npos) continue;
                    double y;
                    y=C->second->GetBinContent(i);
                    y=std::abs(y);
                    if (firstc) { fprintf(f,"$%f:%f$",C->second->GetBinLowEdge(i),C->second->GetBinLowEdge(i)+C->second->GetBinWidth(i)); firstc=0;}
                    fprintf(f,"&$%3.3f^{+%3.3f}_{-%3.3f}",y,C->second->GetBinError(i),C->second->GetBinError(i));

                    if (fHMap.find(C->first+"_systematics")!=fHMap.end())
                        {
                            fprintf(f,"{}^{+%3.3f}_{-%3.3f}",fHMap[C->first+"_systematics"]->GetBinError(i),
                                    fHMap[C->first+"_systematics"]->GetBinError(i));


                        }
                    fprintf(f,"$");


                }
            fprintf(f,"\\\\\n");
        }
    fprintf(f,"\\hline\\end{tabular}\\caption{#2}\n\\end{table}}\n");

}


void PrintTC(std::map<std::string,TCanvas*> fCMap, FILE* f, std::string nick,std::string command)
{
    if (fCMap.size()==0) return;



    if (f==0) f= stdout;

    for (std::map<std::string,TCanvas*>::iterator C=fCMap.begin(); C!=fCMap.end(); C++)
        {

            TObject *objx;
            C->second->Print();

            for (int i=0; i<C->second->GetListOfPrimitives()->GetSize(); i++)
                {
                    objx=C->second->GetListOfPrimitives()->At(i);
                    if (objx==NULL) { puts("bad"); continue;}
                    if (!objx->InheritsFrom(TVirtualPad::Class())) continue;
                    std::string qname= std::string(objx->GetName());
                    if (qname.find("QPAD")==std::string::npos) continue;
                    TCanvas *Q= new TCanvas(("Q"+qname+"Z").c_str(),"Q",1024,1024);
                    Q->cd();


                    std::string rname=qname;
                    replace_all(rname,"QPAD","RPAD");


                    TPad* A1=(TPad*)(C->second->GetListOfPrimitives()->FindObject(qname.c_str())->Clone("1"));
                    TPad* A2=(TPad*)(C->second->GetListOfPrimitives()->FindObject(rname.c_str())->Clone("2"));
                    //TPad* A1=(TPad*)(((TPad*)C->second->GetListOfPrimitives()->At(2*i))->Clone("1"));
                    //TPad* A2=(TPad*)(((TPad*)C->second->GetListOfPrimitives()->At(2*i+1))->Clone("2"));



                    //TPad* A1=(TPad*)(C->second->GetListOfPrimitives()->At(2*i));
                    //TPad* A2=(TPad*)(C->second->GetListOfPrimitives()->At(2*i+1));


                    TObject *obj2;
                    int no=0;
                    TIter next2(A2->GetListOfPrimitives());
                    while ((obj2=next2()))
                        {
                            //printf("%s\n",obj2->GetName());
                            if (obj2->InheritsFrom("TH1")) no++;
                            if ( obj2->IsA()->InheritsFrom( "TGraph" ) )  no++;
                            //if ( obj2->InheritsFrom( "TGraph" ) ) { puts("yes3");}
                        }


                    double h1=A1->GetAbsHNDC();
                    double h2=A2->GetAbsHNDC();

                    //printf("no=%i\n",no);
                    if (no>1)
                        {
                            A2->SetPad(0.0,0.0,1.0,h2/(h1+h2));
                            A1->SetPad(0.0,h2/(h1+h2),1.0,1.0);
                            A1->Draw();
                            A2->Draw();

                        }
                    else
                        {

                            A1->SetPad(0.0,0,1.0,1.0);
                            A1->SetBottomMargin(0.1);
                            A1->Draw();



                        }

                    std::string pname=C->first+A1->GetTitle();
                    if (command!="") pname=command;

                    pname=nick+pname;

                    replace_all(pname,"1","one");
                    replace_all(pname,"2","two");
                    replace_all(pname,"3","three");
                    replace_all(pname,"4","four");
                    replace_all(pname,"5","five");
                    replace_all(pname,"6","six");
                    replace_all(pname,"7","seven");
                    replace_all(pname,"8","eight");
                    replace_all(pname,"9","nine");
                    replace_all(pname,"0","zero");
                    replace_all(pname,"-","minus");
                    replace_all(pname,"+","plus");
                    replace_all(pname,".","dot");
                    replace_all(pname,"_","");
                    Q->SaveAs((std::string("output/")+pname+".eps").c_str());
//Q->Delete();


                    fprintf(f,"\\newcommand{\\FIG%s}[1]{\\begin{figure}\n\\includegraphics[width=\\textwidth]{../../output/%s}\\caption{#1}\\end{figure}}\n",
                            pname.c_str(),pname.c_str());



                }
        }
}









int main(int argc, char* argv[])
{

    std::string nick=std::string(argv[1]);
    FILE * FF;
    FF= fopen(argv[3],"w");

    std::map<std::string,TCanvas*> fCMap;
    TFile* type_fFile= new TFile(argv[2], "READ");
    type_fFile->cd();
    TIter next(type_fFile->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next()))
        {
            TObject *obj = key->ReadObj();
            if (!obj) continue;
            if ( obj->IsA()->InheritsFrom( "TCanvas"    ) )
                {
                    fCMap.insert(std::pair<std::string,TCanvas*> (std::string(key->GetName()) ,(TCanvas*)obj  ) );
                    //fCMap[std::string(key->GetName())]->SetDirectory(0);
                }

        }
    type_fFile->Close();
    std::map<std::string,TCanvas*> fCMap2;
    fCMap2.insert(fCMap.begin(),fCMap.end());

    PrintTC(fCMap2,FF,nick,"");

    for (std::map<std::string,TCanvas*>::iterator C=fCMap.begin(); C!=fCMap.end(); C++)
        {

            std::map<std::string,TH1D*> allfHMap;
            std::map<std::string,TAdvancedGraph*> allfGMap;
            int i=1;
            for (i=0; i<C->second->GetListOfPrimitives()->GetSize(); i++)
                {
                    std::map<std::string,TH1D*> fHMap;
                    std::map<std::string,TAdvancedGraph*> fGMap;
                    std::string padname=std::string(((TPad*)(C->second->GetListOfPrimitives()->At(i)))->GetName());

                    if (padname.find("QPAD")==std::string::npos) continue;

                    TObject *obj2;
                    TIter next2(((TPad*)C->second->GetListOfPrimitives()->At(i))->GetListOfPrimitives());
                    while ((obj2=next2()))
                        {

                            if (obj2->InheritsFrom("TH1"))
                                {
                                    TH1D* z= (TH1D*)obj2;
                                    fHMap.insert(std::pair<std::string,TH1D*> (std::string(z->GetName()) , z ) );

                                }

                            if ( obj2->IsA()->InheritsFrom( "TGraph" ) )
                                {
                                    TAdvancedGraph* z= (TAdvancedGraph*)obj2;
                                    fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(z->GetName()) , z ) );
                                }

                        }



                    PrintTG(fGMap,FF,nick,"");

                    PrintTH(fHMap,FF,nick,"");
                    if (fGMap.size())
                        //if (fGMap.begin()->first.find("corrected")!=std::string::npos)
                        if (fGMap.begin()->first.find("JETR")!=std::string::npos)
                            {
                                for ( std::map<std::string,TAdvancedGraph*>::iterator it=fGMap.begin(); it!=fGMap.end(); it++)
                                    if (it->first.find("corrected")!=std::string::npos) allfGMap.insert(*it);
                                for ( std::map<std::string,TH1D*>::iterator it=fHMap.begin(); it!=fHMap.end(); it++)
                                    if (it->first.find("corrected")!=std::string::npos) allfHMap.insert(*it);

                            }

                }

            PrintTG(allfGMap,FF,"","TABG"+nick+C->first+"_JETRall");

        }

    fclose(FF);
}
