#include "Helpers.h"
#include "TSampleInfo.h"
void FillInfo(TSampleInfo* A,TMap* filestosamples,std::string prefix)
{

    std::vector<std::string> a;
    tokenize(A->fFiles," ",a);
    TH1F* TOTAL= new TH1F("TOTAL","TOTAL",20000,0,20000);
    for (std::vector<std::string>::iterator it=a.begin(); it!=a.end(); it++)
        {
            TChain* C= new TChain("h10");
            C->Add((prefix+*it).c_str());
            C->Draw("Irun>>RUNHIST(20000,0.0,20000.0)");
            TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
            TOTAL->Add(RUNHIST);
            // RUNHIST->SetName((*it+"_RUNHIST").c_str());
            //  RUNHIST->Write();
            filestosamples->Add(new TObjString(it->c_str()),new TObjString(A->GetName()));
        }
    A->fRunsBegin=0;
    A->fRunsEnd=20000-2;


    while (TOTAL->GetBinContent(A->fRunsBegin)<0.5) A->fRunsBegin++;
    while (TOTAL->GetBinContent(A->fRunsEnd)<0.5) A->fRunsEnd--;
    A->fEvents=TOTAL->GetEntries();
    TOTAL->Delete();
}



int main(int argc ,char** argv)
{
    if (argc<2) return 1;
    int i;

    TFile* F= new TFile(argv[1],"recreate");

    std::vector<TSampleInfo*>AIStruct;

    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_1","DATA","kLEP2","da136_95_200.root",-1,-1,-1,2.56,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_2","DATA","kLEP2","da136_97_200.root",-1,-1,-1,2.36,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_MCSI_1","MCSI","kLEP2","mc12163_1_200.root mc12163_2_200.root",-1,-1,-1,0.0,278.8,0.0));



//da1999_200.root mc11344_1_200.root mc11344_2_200.root mc11344_3_200.root mc11344_4_200.root mc5171_1_200.root mc5171_2_200.root mc5171_3_200.root mc5171_4_200.root mc9277_1_200.root mc9205_1_200.root mc9205_2_200.root mc9204_1_200.root mc9204_2_200.root


    /*
    #NT_VERSION 200
    #192 GeV
    #Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #                       		(pb)	(1/pb)
    #Data     	ALL       192	0	29.53	0	da1999
    #PYTHIA		(Z/g)*	11344	94.84	0.000	4	mc11344
    #HERWIG		(Z/g)*	5171	94.84	0.000	4	mc5171
    #*HERWIG   	(Z/g)*	11986	94.84	0.000	4	mc11986
    #*ist ARIADNE 4!
    #*GRC4F		 llqq	8750	8.997	0.000	2	mc8750
    #*GRC4F		 qqqq	8751	8.657	0.000	3	mc8751
    #GRC4F		 eeqq	9277	41.43	0.000	1	mc9277
    #GRC4F		 llqq	9205	8.997	0.000	2	mc9205
    #*ist KoralW ver.\\
    #GRC4F	         qqqq	9204	8.741	0.000	2	mc9204
    #*ist KoralW ver.\\
    */

    AIStruct.push_back(new TSampleInfo(192.0,"192_DATA_1",  "DATA","kLEP2","da1999_200.root",  -1,-1,-1,29.53,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_PYTHIA",  "MCSI","kLEP2","mc11344_1_200.root mc11344_2_200.root mc11344_3_200.root mc11344_4_200.root",-1,-1,-1,  0.0,94.84,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_HERWIG_1","MCSI","kLEP2","mc5171_1_200.root mc5171_2_200.root mc5171_3_200.root mc5171_4_200.root",    -1,-1,-1,  0.0,94.84,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_HERWIG_2","MCSI","kLEP2","mc11986_1_200.root mc11986_2_200.root mc11986_3_200.root mc11986_4_200.root",    -1,-1,-1,  0.0,94.84,0.0));

    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_1","MCBG","kLEP2","mc8750_1_200.root mc8750_2_200.root",    -1,-1,-1,  0.0,8.997,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_2","MCBG","kLEP2","mc8751_1_200.root mc8751_2_200.root mc8751_3_200.root",    -1,-1,-1,  0.0,8.657,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_3","MCBG","kLEP2","mc9277_1_200.root",    -1,-1,-1,  0.0,41.43,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_4","MCBG","kLEP2","mc9205_1_200.root mc9205_2_200.root",    -1,-1,-1,  0.0,8.997,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_5","MCBG","kLEP2","mc9204_1_200.root mc9204_2_200.root",    -1,-1,-1,  0.0,8.741,0.0));





/*
#NT_VERSION 200
#207 GeV						
#Generator	Process	Runno	Sigma	Lumi	Part	filestem
#                       			(pb)	(1/pb)		
#Data		ALL	0	0	137.14	0	da2000
#PYTHIA       	(Z/g)*	11352	79.38	0.000	15	mc11352
#HERWIG   	(Z/g)*	5179	79.38	0.000	4	mc5179
#*HERWIG   	(Z/g)*	11984	79.38	0.000	4	mc11984
#*ist ARIADNE 4						
#*GRC4F	        llqq	10781	9.417	0.000	2	mc10781
#*GRC4F		qqqq	10782	8.97	0.000	3	mc10782
#GRC4F		eeqq	11212	38.11	0.000	1	mc11212
#GRC4F		llll+llqq+qqqq	10788	21.87	0.000	4	mc10788
#*ist Koralw 			
*/

    AIStruct.push_back(new TSampleInfo(207.0,"207_DATA_1",  "DATA","kLEP2","da2000_200.root",  -1,-1,-1,137.14,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_PYTHIA",  "MCSI","kLEP2","mc11352_1_200.root mc11352_2_200.root mc11352_3_200.root mc11352_4_200.root  mc11352_5_200.root \
                                                                            mc11352_6_200.root mc11352_7_200.root mc11352_8_200.root mc11352_9_200.root  mc11352_10_200.root \
                                                                            mc11352_11_200.root mc11352_12_200.root mc11352_13_200.root mc11352_14_200.root  mc11352_15_200.root",-1,-1,-1,  0.0,79.38,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_HERWIG_1","MCSI","kLEP2","mc5179_1_200.root mc5179_2_200.root mc5179_3_200.root mc5179_4_200.root",        -1,-1,-1,  0.0,79.38,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_HERWIG_2","MCSI","kLEP2","mc11984_1_200.root mc11984_2_200.root mc11984_3_200.root mc11984_4_200.root",    -1,-1,-1,  0.0,79.38,0.0));

    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_1","MCBG","kLEP2","mc10781_1_200.root mc10781_2_200.root",    -1,-1,-1,  0.0,9.417,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_2","MCBG","kLEP2","mc10782_1_200.root mc10782_2_200.root mc10782_3_200.root",    -1,-1,-1,  0.0,8.97,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_3","MCBG","kLEP2","mc11212_1_200.root",    -1,-1,-1,  0.0,38.11,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_4","MCBG","kLEP2","mc10788_1_200.root mc10788_2_200.root mc10788_3_200.root mc10788_4_200.root",    -1,-1,-1,  0.0,21.87,0.0));
//    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_5","MCBG","kLEP2","mc9204_1_200.root mc9204_2_200.root",    -1,-1,-1,  0.0,8.741,0.0));







    std::string prefix=std::string(argv[2]);
    TMap* db= new TMap();
    for (std::vector<TSampleInfo*>::iterator it= AIStruct.begin(); it!=AIStruct.end(); it++)
        {
            FillInfo(*it,db,prefix);
            (*it)->Write();
        }
    db->Write("mymap",1);
    F->Close();
    return 0;
}
