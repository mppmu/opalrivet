#include "Helpers.h"



double chi2_TH1(TH1D* A, TH1D* B)
{
    double chi2=0;
    int N=0;
    for (int i=0; i<A->GetNbinsX(); i++)	if (pow(A->GetBinError(i),2)+pow(B->GetBinError(i),2)>0.000001)
            {N++; chi2+=pow(A->GetBinContent(i)-B->GetBinContent(i),2)/(pow(A->GetBinError(i),2)+pow(B->GetBinError(i),2));}
    return chi2/N;

}

double chi2_TG(TAdvancedGraph* A, TAdvancedGraph* B,double mi=-TMath::Infinity(),double ma=TMath::Infinity())
{
    double chi2=0;
    int N=0;
    for (int i=0; i<A->GetN(); i++)	if (A->GetX()[i]>mi&&A->GetX()[i]<ma)
            {
                if (A->GetY()[i]>B->GetY()[i]) if (pow(A->GetEYlow()[i],2)+pow(B->GetEYhigh()[i],2)>0.000001)
                        {
                            N++;
                            chi2+=pow(A->GetY()[i]-B->GetY()[i],2)/(pow(A->GetEYlow()[i],2)+pow(B->GetEYhigh()[i],2));

                            printf("1:   %f %f %f %f %f %f %f\n",A->GetX()[i],B->GetX()[i],pow(A->GetY()[i]-B->GetY()[i],2)/(pow(A->GetEYlow()[i],2)+pow(B->GetEYhigh()[i],2)),A->GetY()[i],B->GetY()[i],A->GetEYlow()[i],B->GetEYhigh()[i]);
                        }

                if (A->GetY()[i]<B->GetY()[i]) if (pow(A->GetEYhigh()[i],2)+pow(B->GetEYlow()[i],2)>0.000001)
                        {
                            N++;
                            chi2+=pow(A->GetY()[i]-B->GetY()[i],2)/(pow(A->GetEYhigh()[i],2)+pow(B->GetEYlow()[i],2));


                            printf("2:   %f %f %f %f %f %f %f\n",A->GetX()[i],B->GetX()[i],pow(A->GetY()[i]-B->GetY()[i],2)/(pow(A->GetEYhigh()[i],2)+pow(B->GetEYlow()[i],2)),A->GetY()[i],B->GetY()[i],A->GetEYhigh()[i],B->GetEYlow()[i]);


                        }

            }
    return chi2/N;

}

void ShiftPoints(TAdvancedGraph* B,double shift=0.05)
{
    for (int j=0; j<B->GetN(); j++)
        B->GetX()[j]=B->GetX()[j]+shift*(B->GetX()[j+1]-B->GetX()[j]);

}

void RemovePoints(TAdvancedGraph* B,int n)
{
    for (int j=0; j<n; j++)
        B->RemovePoint(j);

}



TAdvancedGraph* ExtendGraph2(TAdvancedGraph* A, TAdvancedGraph* B)
{

    double X[A->GetN()+B->GetN()];
    double Y[A->GetN()+B->GetN()];
    double Xel[A->GetN()+B->GetN()];
    double Yel[A->GetN()+B->GetN()];
    double Xeh[A->GetN()+B->GetN()];
    double Yeh[A->GetN()+B->GetN()];
    int ok=0;
    int q=0;
    int filled=0;
    for (int j=0; j<B->GetN(); j++)
        {
            ok=0;
            if (
                (B->GetX()[j]<A->GetX()[0]) ||
                (B->GetX()[j]>A->GetX()[A->GetN()-1])
            )
                {
                    ok=1;
                    X[q]=B->GetX()[j];
                    Xeh[q]=B->GetErrorXhigh(j);
                    Xel[q]=B->GetErrorXlow(j);
                    Y[q]=0;//B->GetY()[j];
                    Yel[q]=0;//B->GetYElow()[j];
                    Yeh[q]=0;//B->GetYEhigh()[j];
                    q++;
                }


            if (
                (B->GetX()[j]>A->GetX()[0]) &&
                (B->GetX()[j]<A->GetX()[A->GetN()-1])
            )
                {


                    if (!filled)
                        for (int i=0; i<A->GetN(); i++)
                            {
                                filled=1;
                                X[q]=A->GetX()[i];
                                //printf("%i %i %i\n", q, A->GetN(),B->GetN());
                                Xeh[q]=A->	GetErrorXhigh(i);
                                Xel[q]=A->GetErrorXlow(i);
                                Y[q]=A->GetY()[i];
                                Yel[q]=A->GetErrorYlow(i);
                                Yeh[q]=A->GetErrorYhigh(i);
                                q++;


                            }

                    for (int i=0; i<A->GetN(); i++) if (fabs(B->GetX()[j]-A->GetX()[i])<0.0000001) ok=1;



                }


            if (!ok) { puts("failed to extend!"); return NULL;}
        }

    TAdvancedGraph* C= new TAdvancedGraph(q,X,Y,Xel,Xeh,Yel,Yeh);
    return C;

}
bool myfunction(std::vector<double> a, std::vector<double> b)
{
    return (a[0]<b[0]);
}

TAdvancedGraph* ExtendGraph(TAdvancedGraph* A, TAdvancedGraph* B,double margin)
{

    std::vector< std::vector<double> > Z;
    for (int i=0; i<A->GetN(); i++)
        {
            std::vector<double> z;
            z.push_back(A->GetX()[i]);
            z.push_back(A->GetY()[i]);
            z.push_back(A->GetErrorXlow(i));
            z.push_back(A->GetErrorXhigh(i));
            z.push_back(A->GetErrorYlow(i));
            z.push_back(A->GetErrorYhigh(i));
            z.push_back(1);
            Z.push_back(z);
        }

    for (int i=0; i<B->GetN(); i++)
        {
            std::vector<double> z;
            z.push_back(B->GetX()[i]);
            z.push_back(B->GetY()[i]);
            z.push_back(B->GetErrorXlow(i));
            z.push_back(B->GetErrorXhigh(i));
            z.push_back(B->GetErrorYlow(i));
            z.push_back(B->GetErrorYhigh(i));
            z.push_back(-1);
            Z.push_back(z);
        }

    std::sort (Z.begin(), Z.end(), myfunction);
    std::vector< std::vector<double> > Z2;

    Z2.push_back(Z.at(0));
    for (int i=1; i<Z.size(); i++) if (!TMath::AreEqualRel(Z2.back()[0], Z.at(i)[0], margin)) Z2.push_back(Z.at(i));
        else if (Z2.back()[6]<0) Z2[Z2.size()-1]=Z.at(i);


    TAdvancedGraph* C= new TAdvancedGraph(Z2.size());
    for (int j=0; j<Z2.size(); j++)
        {

            C->SetPoint(j,Z2.at(j)[0],Z2.at(j)[1]);
            C->SetPointEXlow(j,Z2.at(j)[2]);
            C->SetPointEXhigh(j,Z2.at(j)[3]);
            C->SetPointEYlow(j,Z2.at(j)[4]);
            C->SetPointEYhigh(j,Z2.at(j)[5]);

        }
    return C;
}



/*
TH1D*  TAdvancedGraph_to_TH1D(const char* name,TAdvancedGraph* A)
{

	double* X= new double[A->GetN()+1];
	//X[0]=A->GetX()[0]-A->GetEXlow()[0];
	for (int i=0;i<A->GetN();i++)
	X[i]=A->GetX()[i]-A->GetEXlow()[i];
		X[A->GetN()]=A->GetX()[A->GetN()-1]+A->GetEXhigh()[A->GetN()-1];


		for (int i=0;i<A->GetN()+1;i++) X[i]=X[i]*pow(10.0,-0.25/2);

	TH1D* Q= 	new TH1D(name,"",  A->GetN(), X);
	for (int i=0;i<A->GetN();i++)
	{
	Q->SetBinError(i+1,A->GetEYlow()[i]);
	Q->SetBinContent(i+1,A->GetY()[i]);
      }
	return Q;

}
*/
TH1D*  TAdvancedGraph_to_TH1D_template(const char* name,TAdvancedGraph* A,TH1D* B,int offset=0)//STUPID YODA!
{

    TH1D* Q= 	(TH1D*)B->Clone(name);
    for (int i=1; i<A->GetN()+1; i++)
        {
            Q->SetBinError(i+1+offset,A->GetEYlow()[i]);
            Q->SetBinContent(i+1+offset,A->GetY()[i]);
        }
    return Q;

}




#ifndef __CINT__
int main(int argc, char** argv)
{
#else
int plots()
{
    int arg=2;
    char* argv[2]= {"","189"};
#endif

    std::map<std::string,TH1D*> fHMap;
    std::map<std::string,TAdvancedGraph*> fGMap;

    std::vector<std::string> generators;
    std::vector<std::string> algorithms;
//    tokenize("pythia8:sherpa:herwig++",":",generators);

    tokenize("pythia8",":",generators);
//    tokenize("durham:jade:antikt",":",algorithms);
    tokenize("durham",":",algorithms);

    if (argc<2) {printf("Not enough arguments\n"); exit(1);}


    int ENERGY;

    sscanf(argv[1],"%i",&ENERGY);
//=189;
    //  ENERGY=130;

    std::map<std::pair<float,std::string>,int> yodaconv;
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(91.0,"durham"),18));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(130.0,"durham"),19));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(161.0,"durham"),20));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(172.0,"durham"),21));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(183.0,"durham"),22));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(189.0,"durham"),23));

    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(91.0,"jade"),9));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(130.0,"jade"),10));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(161.0,"jade"),11));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(172.0,"jade"),12));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(183.0,"jade"),13));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(189.0,"jade"),14));

    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(91.0,"antikt"),9));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(130.0,"antikt"),10));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(161.0,"antikt"),11));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(172.0,"antikt"),12));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(183.0,"antikt"),13));
    yodaconv.insert(std::pair<std::pair<float,std::string>,int>(std::pair<float,std::string>(189.0,"antikt"),14));


    std::vector < std::string > ofiles;
    for (int j=0; j<generators.size(); j++) ofiles.push_back(std::string(TString(Form("output/prediction%s_%i.root",generators[j].c_str(),ENERGY)).Data()));
    ofiles.push_back(std::string(TString(Form("output/OPAL_%i.root",ENERGY)).Data()));
    //>???????????? //ofiles.push_back(std::string(TString("output/JADE_OPAL_2000_S4300807a.root").Data()));

    for (int j=0; j<ofiles.size(); j++)
        {
            TFile* F = new TFile(ofiles.at(j).c_str());
            puts(ofiles.at(j).c_str());
            TIter next(F->GetListOfKeys());
            TKey *key;
            while ((key = (TKey*)next()))
                {
                    TObject *obj = key->ReadObj();
                    if ( obj->IsA()->InheritsFrom( "TH1"    ) )
                        {
                            fHMap.insert(std::pair<std::string,TH1D*> (std::string(key->GetName()) ,(TH1D*)obj)   );
                            if (fHMap.find(std::string(key->GetName()))!=fHMap.end()) if (fHMap.at(std::string(key->GetName())))  fHMap[std::string(key->GetName())]->SetDirectory(0);
                        }
                    if ( obj->IsA()->InheritsFrom( "TGraph" ) )
                        {
                            fGMap.insert(std::pair<std::string,TAdvancedGraph*> (std::string(key->GetName()) ,(TAdvancedGraph*)obj)   );
                            //fGMap[std::string(key->GetName())]->SetDirectory(0);
                        }
                    if(key) puts(key->GetName());
                }
            F->Close();
        }

    set_my_style();
    system("mkdir -p plots");
    for (int r=0; r<algorithms.size(); r++)
        {
            std::string ALGORITHM=algorithms[r];
            std::string algorithm=algorithms[r];
            std::string Algorithm=algorithms[r];
            puts(algorithm.c_str());
            for (int j=0; j<generators.size(); j++)
                {
                    std::string generator=generators[j];
                    std::string GENERATOR=generators[j];
                    puts(generator.c_str());
                    TCanvas* D= new TCanvas("D","D",1024*2,768*2);
                    D->cd(1);
                    D->SetLogy();


                    fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->Draw();
                    fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->SetLineColor(kRed);
                    fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())]->GetXaxis()->SetRangeUser(0.001,0.3);
                    fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_1-T",generator.c_str(),algorithm.c_str(),ENERGY)).Data())]->Draw("same");
                    TLegend* A0= new TLegend(0.1,0.9,0.30,0.75);
                    A0->AddEntry(fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY)).Data())],"Data, reanalysis (prel.)");
                    A0->AddEntry(fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_1-T",generator.c_str(),algorithm.c_str(),ENERGY)).Data())],Form("%s prediction",GENERATOR.c_str()));
                    A0->Draw();
                    D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
                    D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
                    D->SaveAs(Form("plots/H_corrected_%s_%iGeV_1-T_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));

                    D->Delete();





#define SAME 0


                    TCanvas* C= new TCanvas(Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY),Form("H_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY),1024*2,768*2);
                    C->SetLogx();

                    TMultiGraph *mg = new TMultiGraph();


                    if (!SAME) C->Divide(2,3,0.01,0.01);
                    for (int i=0; i<5; i++)
                        {
                            if (!SAME) { C->cd(i+1); gPad->SetLogx();     gPad->SetRightMargin(0.01);}

                            if (i==4) fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetTitle(Form("Integrated %i+-jet rate with %s algorithm (%iGeV);y_{cut};Rate",i+2,ALGORITHM.c_str(),ENERGY));
                            else       fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetTitle(Form("Integrated %i-jet rate with %s algorithm (%iGeV);y_{cut};Rate",i+2,ALGORITHM.c_str(),ENERGY));

                            std::string option="APEL";

                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->Draw(option.c_str());
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineColor(kRed);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetRangeUser(0.00001,1);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetRangeUser(0,1.6);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetTitleSize(0.05);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetTitleSize(0.05);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetLabelSize(0.045);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetLabelSize(0.045);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerColor(kRed);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerStyle(kFullCircle);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerSize(1.2);
                            fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineWidth(1.0);
                            if (i<4) mg->Add(fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],"PEL");

                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Draw("SAMEPE");
                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineColor(kBlue);
                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerColor(kBlue);
                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerStyle(kOpenSquare);
                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerSize(1.1);
                            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineWidth(1.0);

                            if (i<4) mg->Add(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],"PE");

                            puts(std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data()).c_str());
                            if (j==0) fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Scale(0.01);
                            fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("SAMEPE");
                            fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->SetMarkerColor(kBlack);
                            fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->SetMarkerStyle(kFullCircle);
                            fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->SetMarkerSize(1.0);
                            fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->SetLineWidth(1.0);

                            if (i<4)if (algorithm!="antikt")  mg->Add(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"PE");

                            TLegend* A= new TLegend(0.13,0.87,0.40,0.60);
                            A->AddEntry(fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],"Data, reanalysis (prel.)","P");
                            if (algorithm!="antikt") A->AddEntry(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"Data, EPJ C17 19-51 (2000)","P");
                            A->AddEntry(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],Form("%s prediction",GENERATOR.c_str()),"P");
                            A->SetTextSize(0.04);
                            A->Draw();
                            double c2=
//chi2_TH1(
                                chi2_TG(
                                    fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],
                                    fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]
                                );




                            printf("%f\n",c2);
                        }
                    C->SaveAs(Form("plots/G_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
                    C->SaveAs(Form("plots/G_corrected_%s_%iGeV_JETR_%s.eps",algorithm.c_str(),ENERGY,generator.c_str()));
                    C->SaveAs(Form("plots/G_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
                    C->SaveAs(Form("plots/G_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
                    C->Delete();




                    TCanvas* C2= new TCanvas(Form("Hfff_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY),Form("Hff_corrected_%s_%iGeV_1-T",algorithm.c_str(),ENERGY),1024*2*3/4,768*2);
                    C2->SetLogx();
                    C2->cd();
                    mg->SetTitle(Form("Integrated 2,3,4,5-jet rates with %s algorithm at OPAL (91GeV);y_{cut};Rates",Algorithm.c_str()));
                    mg->Draw("ae");
//mg->SetTitleSize(0.05);
                    mg->GetXaxis()->SetRangeUser(0.0001,1);
                    mg->GetYaxis()->SetRangeUser(0,1.4);
                    mg->GetYaxis()->SetTitleOffset(1.0);
                    mg->GetYaxis()->SetTitleSize(0.05);
                    mg->GetYaxis()->SetTitleOffset(0.95);
                    mg->GetYaxis()->SetTitleSize(0.05);

//mg->GetYaxis()->SetTitle("Rates");
//mg->GetXaxis()->SetTitle("y_{cut}");
                    TLegend* A2= new TLegend(0.13,0.87,0.45,0.60);
                    int i=0;
                    A2->AddEntry(fGMap[std::string(TString(Form("G_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())],"Data, reanalysis (prel.)","P");
                    if (algorithm!="antikt")A2->AddEntry(fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%02d-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],"Data, EPJ C17 19-51 (2000)","P");
                    A2->AddEntry(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],Form("%s prediction",GENERATOR.c_str()),"P");
                    A2->SetTextSize(0.03);
                    A2->Draw();
                    TPaveText *title = (TPaveText*)gPad->GetPrimitive("title");
                    //title->SetX2NDC(0.9);
                    title->SetTextSize(0.03);
                    gPad->Modified();
                    C2->SaveAs(Form("plots/2G_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
                    C2->SaveAs(Form("plots/2G_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
                    C2->SaveAs(Form("plots/2G_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
                    C2->SaveAs(Form("plots/2G_corrected_%s_%iGeV_JETR_%s.eps",algorithm.c_str(),ENERGY,generator.c_str()));
                }
        }

    std::string algorithm="durham";
    std::string generator,GENERATOR;


    int i=0;



    TCanvas* E= new TCanvas("E","E",1024,1024);
    TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,0.95,kWhite,0,0);
    TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2,kWhite,0,0);
    pad1->SetRightMargin(0.05);
    pad1->SetTopMargin(0.11);
    pad1->SetBottomMargin(0.04);

    pad1->Draw();
    pad2->Draw();

    EColor Colors[10]= {kBlack,kRed, kBlue, kGreen};

    EMarkerStyle Markers[10]= {kOpenCircle,kFullCircle,kFullSquare,kFullTriangleUp};
    double LineWidths[10]= {3,2,2,2};
    double MarkerSize[10]= {1.3,1.2,1.2,1.2};

    pad1->cd();
    pad1->SetTopMargin(0.08);
    pad1->SetBottomMargin(0.08);
    pad1->SetLogx();
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->Draw("ALPE");
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->GetXaxis()->SetRangeUser(0.000001,1);
//fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())]->GetYaxis()->SetRangeUser(0,1.25);

    TMultiGraph *mg2 = new TMultiGraph();
    TMultiGraph *mg3 = new TMultiGraph();
    TAdvancedGraph* HJ[generators.size()];
    /*
    TH1D* H=  TAdvancedGraph_to_TH1D_template("HH",fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",
    yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())],
    fHMap[std::string(TString(Form("H_prediction%s_%s_%iGeV_JETR%i",generators[0].c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],0);
    //H->SetTitle("Integrated 2-jet rate with Durham algorithm in OPAL e^{+}e^{-} collisions for #sqrt{s}=189GeV;x;1/#sigma d#sigma/dx");
    */
    TAdvancedGraph* H=fGMap[std::string(TString(Form("/REF/JADE_OPAL_2000_S4300807a/d%i-x01-y0%i",yodaconv[std::pair<float,std::string>(ENERGY*1.0,algorithm)],i+1)).Data())];
    H->SetTitle(Form("Integrated 2-jet rate with Durham algorithm at OPAL (%iGeV);y_{cut};Rate",ENERGY));

//H->Draw("AP");
//RemovePoints(H,9);
    mg2->Add(H,"AP");



    H->SetLineColor(Colors[0]);
    H->SetMarkerColor(Colors[0]);
    H->SetMarkerStyle(Markers[0]);
    H->SetMarkerSize(MarkerSize[0]);
    H->GetYaxis()->SetTitleOffset(0.9);
    H->GetXaxis()->SetLabelSize(0.04);

    H->SetLineWidth(LineWidths[0]);

    H->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
    H->GetYaxis()->SetRangeUser(0,1.25);
//H->GetXaxis()->SetTitleSize(0.10);
//H->GetXaxis()->SetLabelSize(0.14);


    TLegend* L= new TLegend(0.13,0.87,0.45,0.65);
    L->AddEntry(H,"Data, EPJ C17 19-51 (2000)","P");

    for (int j=0; j<generators.size(); j++)
        {
            generator=generators[j];
            GENERATOR=generators[j];

//fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->Draw("SAME");
//RemovePoints(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],9);
            mg2->Add(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],"PE");
            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineColor(Colors[j+1]);
            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerColor(Colors[j+1]);
            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerStyle(Markers[j+1]);
            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetMarkerSize(MarkerSize[j+1]);
            fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]->SetLineWidth(LineWidths[j+1]);
//fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetXaxis()->SetRangeUser(0.00001,1);
//fHMap[std::string(TString(Form("H_corrected_%s_%iGeV_JETR%i",algorithm.c_str(),ENERGY,i+2)).Data())]->GetYaxis()->SetRangeUser(0,1.3);
            pad2->cd();
            pad2->SetLogx();

            pad2->SetRightMargin(0.05);

            pad2->SetBottomMargin(0.04);

//HJ[j]=TAdvancedGraph(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())]);//->Clone(Form("H%i",j));

//HJ[j]->DivideBayesis(H);

            TAdvancedGraph *Q=fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())];
            Q=ExtendGraph(Q,H,0.000001);
            H=ExtendGraph(H,Q,0.000001);
            HJ[j]->Divide(Q,H);
            HJ[j]->SetTitle(";y_{cut};Data/MC;");

            HJ[j]->SetLineColor(Colors[j+1]);
            HJ[j]->SetMarkerColor(Colors[j+1]);
            HJ[j]->SetMarkerStyle(Markers[j+1]);
            HJ[j]->SetMarkerSize(0.8*MarkerSize[j+1]);
            HJ[j]->SetLineWidth(LineWidths[j+1]);

            ShiftPoints(HJ[j],0.1*j);
            //RemovePoints(HJ[j],9);
            mg3->Add(HJ[j],"PE");
            if (j==0)    //HJ[j]->Draw("AP");
                {


                    HJ[j]->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
                    HJ[j]->GetYaxis()->SetRangeUser(0.9,1.1);
                    HJ[j]->GetYaxis()->SetTitleOffset(0.4);
                    HJ[j]->GetYaxis()->SetTitleSize(0.10);


                    HJ[j]->GetYaxis()->SetLabelSize(0.13);
//HJ[j]->GetXaxis()->SetLabelFont(42);
                    HJ[j]->GetXaxis()->SetLabelSize(0.035);
                    HJ[j]->GetXaxis()->SetTitleSize(0.0);
                    HJ[j]->GetXaxis()->SetLabelSize(0.0);
//   HJ[j]->GetXaxis()->SetTitleFont(42);
                    HJ[j]->GetYaxis()->SetLabelFont(42);
                    //HJ[j]->GetYaxis()->SetLabelSize(0.035);
                    //HJ[j]->GetYaxis()->SetTitleSize(0.035);
//   HJ[j]->GetYaxis()->SetTitleFont(42);


                }
            else   //HJ[j]->Draw("SAME");
                {
                }
            pad1->cd();
            pad1->SetLogx();

            mg2->Draw("A");
            mg2->SetTitle(Form("Integrated 2-jet rate with Durham algorithm at OPAL (%iGeV);y_{cut};Rate",ENERGY));
            mg2->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
            mg2->GetYaxis()->SetRangeUser(0,1.25);
            mg2->GetYaxis()->SetTitleOffset(0.9);
            mg2->GetXaxis()->SetLabelSize(0.04);

            L->AddEntry(fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],
                        Form("%s prediction,   #chi^{2}/ndof=%3.2f",GENERATOR.c_str(),
                             chi2_TG(
                                 fGMap[std::string(TString(Form("G_prediction%s_%s_%iGeV_JETR%i",generator.c_str(),algorithm.c_str(),ENERGY,i+2)).Data())],
                                 H,0.0001,1.0)


                            ),"P");

        }
    L->SetTextSize(0.03);
    L->Draw();



    pad2->cd();
    mg3->Draw("A");
    mg3->SetTitle(";y_{cut};Data/MC;");
    mg3->GetXaxis()->SetRangeUser(0.0001*sqrt(10),1);
    mg3->GetYaxis()->SetRangeUser(0.8,1.2);
    mg3->GetYaxis()->SetTitleOffset(0.4);
    mg3->GetYaxis()->SetTitleSize(0.10);
    mg3->GetYaxis()->SetLabelSize(0.13);
    mg3->GetXaxis()->SetLabelSize(0.035);
    mg3->GetXaxis()->SetTitleSize(0.0);
    mg3->GetXaxis()->SetLabelSize(0.0);
    mg3->GetYaxis()->SetLabelFont(42);



    TF1* one= new TF1("1","1",0,1);
    one->SetLineColor(kBlack);
    one->SetLineWidth(2);
//one->GetXaxis()->SetNdivisions(57);
    one->Draw("SAME");

    pad1->SetTitle("");
    pad2->SetTitle("");

    generator="all";



    E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.png",algorithm.c_str(),ENERGY,generator.c_str()));
    E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.eps",algorithm.c_str(),ENERGY,generator.c_str()));
    E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.root",algorithm.c_str(),ENERGY,generator.c_str()));
    E->SaveAs(Form("plots/EH_corrected_%s_%iGeV_JETR_%s.pdf",algorithm.c_str(),ENERGY,generator.c_str()));
    E->Delete();




}
