#include "Helpers.h"
#include "Cuts.h"
#include "TSampleInfo.h"
void FillInfo(TSampleInfo* A,TMap* filestosamples,std::string prefix)
{
    A->Print();
    std::vector<std::string> a;
    tokenize(A->fFiles," ",a);
    TH1F* TOTAL= new TH1F("TOTAL","TOTAL",20000,0,20000);
    for (std::vector<std::string>::iterator it=a.begin(); it!=a.end(); it++)
        {
            TChain* C= new TChain("h10");
            C->Add((prefix+*it).c_str());
            C->Draw("Irun>>RUNHIST(20000,0.0,20000.0)",Form("(Ebeam>%f)&&(Ebeam<%f)",0.5*(A->fE-ENERGYTOLERANCE),0.5*(A->fE+ENERGYTOLERANCE)));
            TH1F* RUNHIST=(TH1F*)gDirectory->Get("RUNHIST");
            TOTAL->Add(RUNHIST);
            // RUNHIST->SetName((*it+"_RUNHIST").c_str());
            //  RUNHIST->Write();
            filestosamples->Add(new TObjString(Form("%s_%s", it->c_str(),A->fEnergyString.c_str())),new TObjString(A->GetName()));
        }
    A->fRunsBegin=0;
    A->fRunsEnd=20000-2;


    while (TOTAL->GetBinContent(A->fRunsBegin)<0.5&&A->fRunsEnd>=A->fRunsBegin) A->fRunsBegin++;
    while (TOTAL->GetBinContent(A->fRunsEnd)<0.5&&A->fRunsEnd>=A->fRunsBegin) A->fRunsEnd--;
    if (A->fRunsEnd<A->fRunsBegin) puts("Wrong run numbers of energy");
    A->fEvents=TOTAL->GetEntries();
    A->Print();
    TOTAL->Delete();
}



int main(int argc ,char** argv)
{
    if (argc<2) return 1;
    int i;

    TFile* F= new TFile(argv[1],"recreate");

    std::vector<TSampleInfo*>AIStruct;
    /*
    #FIX RUNS
    # NT_VERSION 200

    #Generator       Process   Runno    Sigma    Lumi  Part    File

    #130 GeV

    #Data            ALL         130        0   2.70     0    da130_95
    #Data            ALL         130        0   2.61     0    da130_97
    #PYTHIA          (Z/g)*    12162    335.9   0.0      2    mc12162
    #HERWIG          (Z/g)*    11925    334.9   0.0      2    mc11925
    */




    AIStruct.push_back(new TSampleInfo(130.0,"130_DATA_1",  "DATA","ALL","kLEP1","da130_95_200.root",-1,-1,-1,2.70,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(130.0,"130_DATA_2",  "DATA","ALL","kLEP2","da130_97_200.root",-1,-1,-1,2.61,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(130.0,"130_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12162_1_200.root mc12162_2_200.root",-1,-1,-1,0.0,335.9,0.0));
    AIStruct.push_back(new TSampleInfo(130.0,"130_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc11925_1_200.root mc11925_2_200.root",-1,-1,-1,0.0,334.9,0.0));






    /*
    #NT_VERSION 200
    #
    #    Generator       Process   Runno    Sigma    Lumi  Part    File
    #
    #    136 GeV
    #
    #    Data            ALL         136        0    2.59    0    da136_95
    #    Data            ALL         136        0    3.36    0    da136_97
    #    PYTHIA          (Z/g)*    12163    278.8      0.0   2    mc12163
    #    HERWIG          (Z/g)*    11926    278.5      0.0   2    mc11926
    #

    */


    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_1",  "DATA","ALL","kLEP1","da136_95_200.root",-1,-1,-1,2.56,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_DATA_2",  "DATA","ALL","kLEP2","da136_97_200.root",-1,-1,-1,2.36,0.0,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12163_1_200.root mc12163_2_200.root",-1,-1,-1,0.0,278.8,0.0));
    AIStruct.push_back(new TSampleInfo(136.0,"136_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc11926_1_200.root mc11926_2_200.root",-1,-1,-1,0.0,278.5,0.0));


    /*
    #
    #    Generator       Process   Runno    Sigma    Lumi  Part    File
    #
    #    161 GeV
    #
    #    Data            ALL         161        0    10.06   0    da161
    #    PYTHIA          (Z/g)*    12164    156.2     0.0    4    mc12164
    #    HERWIG          (Z/g)*    11927    155.6     0.0    5    mc11927
    #    GRC4F           llqq       4513    2.648     0.0    1    mc4513
    #    GRC4F           qqqq       4544    2.064     0.0    1    mc4544
    #    GRC4F           eeqq       4741    5.161     0.0    1    mc4741
    #
    */



    AIStruct.push_back(new TSampleInfo(161.0,"161_DATA_1",  "DATA","ALL","kLEP2","da161_200.root",  -1,-1,-1,10.06,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(161.0,"161_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc12164_1_200.root mc12164_2_200.root mc12164_3_200.root mc12164_4_200.root",-1,-1,-1,  0.0,156.2,0.0));
    AIStruct.push_back(new TSampleInfo(161.0,"161_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc11927_1_200.root mc11927_2_200.root mc11927_3_200.root mc11927_4_200.root mc11927_5_200.root",    -1,-1,-1,  0.0,155.6,0.0));

    AIStruct.push_back(new TSampleInfo(161.0,"161_GRC4F_1","MCBG","llqq","kLEP2","mc4513_1_200.root",    -1,-1,-1,  0.0,2.648,0.0));
    AIStruct.push_back(new TSampleInfo(161.0,"161_GRC4F_2","MCBG","qqqq","kLEP2","mc4544_1_200.root",    -1,-1,-1,  0.0,2.064,0.0));
    AIStruct.push_back(new TSampleInfo(161.0,"161_GRC4F_3","MCBG","eeqq","kLEP2","mc4741_1_200.root",    -1,-1,-1,  0.0,5.161,0.0));

    /*
    #NT_VERSION 200
    #
    #    Generator       Process   Runno    Sigma    Lumi  Part    File
    #
    #    172 GeV
    #
    #    Data            ALL         172        0     10.38   0    da172
    #    PYTHIA          (Z/g)*    12165    128.6      0.0    4    mc12165
    #    HERWIG          (Z/g)*    11928    128.3      0.0    5    mc11928
    #    GRC4F           llqq       4743    6.284      0.0    1    mc4743
    #    GRC4F           qqqq       4744    6.061      0.0    1    mc4744
    #    GRC4F           eeqq       4745    4.730      0.0    1    mc4745
    #

    ########################
    #    PYTHIA          (Z/g)*    12165    128.6      0.0    4    mc12165
    #    HERWIG          (Z/g)*    11928    128.3      0.0    5    mc11928
    #    GRC4F           llqq       4743    6.284      0.0    1    mc4743
    #    GRC4F           qqqq       4744    6.061      0.0    1    mc4744
    #    GRC4F           eeqq       4745    4.730      0.0    1    mc4745

    */

    AIStruct.push_back(new TSampleInfo(172.0,"172_DATA_1",  "DATA","ALL","kLEP2","da172_200.root",  -1,-1,-1,10.06,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(172.0,"172_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12165_1_200.root mc12165_2_200.root mc12165_3_200.root mc12165_4_200.root",-1,-1,-1,  0.0,128.6,0.0));
    AIStruct.push_back(new TSampleInfo(172.0,"172_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc11928_1_200.root mc11928_2_200.root mc11928_3_200.root mc11928_4_200.root mc11928_5_200.root",    -1,-1,-1,  0.0,128.3,0.0));

    AIStruct.push_back(new TSampleInfo(172.0,"172_GRC4F_1", "MCBG","llqq","kLEP2","mc4743_1_200.root",    -1,-1,-1,  0.0,6.284,0.0));
    AIStruct.push_back(new TSampleInfo(172.0,"172_GRC4F_2", "MCBG","qqqq","kLEP2","mc4744_1_200.root",    -1,-1,-1,  0.0,6.061,0.0));
    AIStruct.push_back(new TSampleInfo(172.0,"172_GRC4F_3", "MCBG","eeqq","kLEP2","mc4745_1_200.root",    -1,-1,-1,  0.0,4.730,0.0));


    /*
    #NT_VERSION 200
    #
    #    Generator       Process   Runno    Sigma    Lumi  Part    File
    #
    #    183 GeV
    #
    #    Data            ALL         183        0     57.72   0    da183
    #    PYTHIA          (Z/g)*    11341    109.0      0.0    4    mc11341
    #    HERWIG          (Z/g)*     5168    109.0      0.0    5    mc5168  ->AV _5_ does not exist!
    #    GRC4F           llqq       8056    8.113      0.0    2    mc8056
    #    GRC4F           qqqq       7051    7.862      0.0    3    mc7051
    #    GRC4F           eeqq       7055    26.74      0.0    1    mc7055

    */

    AIStruct.push_back(new TSampleInfo(183.0,"183_DATA_1",  "DATA","ALL","kLEP2","da183_200.root",  -1,-1,-1,57.72,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(183.0,"183_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc11341_1_200.root mc11341_2_200.root mc11341_3_200.root mc11341_4_200.root",-1,-1,-1,  0.0,109.0,0.0));
    AIStruct.push_back(new TSampleInfo(183.0,"183_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5168_1_200.root mc5168_2_200.root mc5168_3_200.root mc5168_4_200.root",    -1,-1,-1,  0.0,109.0,0.0));

    AIStruct.push_back(new TSampleInfo(183.0,"183_GRC4F_1", "MCBG","llqq","kLEP2","mc8056_1_200.root mc8056_2_200.root",    -1,-1,-1,  0.0,8.113,0.0));
    AIStruct.push_back(new TSampleInfo(183.0,"183_GRC4F_2", "MCBG","qqqq","kLEP2","mc7051_1_200.root mc7051_2_200.root mc7051_3_200.root",    -1,-1,-1,  0.0,7.862,0.0));
    AIStruct.push_back(new TSampleInfo(183.0,"183_GRC4F_3", "MCBG","eeqq","kLEP2","mc7055_1_200.root",    -1,-1,-1,  0.0,26.74,0.0));

    /*
    #NT_VERSION 200
    #189 GeV
    #Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #                       		(pb)	(1/pb)
    #Data    	ALL     189	        0	185.2	0	da189
    #PYTHIA		(Z/g)*	11342	99.36	0.000	10	mc11342
    #PYTHIA		(Z/g)*	11343	8.574	0.000	10	mc11343
    #HERWIG		(Z/g)*	5169	99.36	0.000	10	mc5169
    #*HERWIG		(Z/g)*	11981	99.36	0.000	4	mc11981
    #*ist ARIADNE 4!
    #*GRC4F	        llqq	8055	8.679	0.000	2	mc8055
    #*GRC4F		qqqq	7846	8.418	0.000	3	mc7846
    #GRC4F		eeqq	7849	25.52	0.000	1	mc7849
    #GRC4F		llqq	8637	8.679	0.000	2	mc8637
    #*ist KoralW !
    #GRC4F		qqqq	8636	8.418	0.000	2	mc8636
    #*ist KoralW !
    */



    AIStruct.push_back(new TSampleInfo(189.0,"189_DATA_1",  "DATA","ALL","kLEP2","da189_200.root",  -1,-1,-1,185.2,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc11342_1_200.root mc11342_2_200.root mc11342_3_200.root mc11342_4_200.root mc11342_5_200.root mc11342_6_200.root mc11342_7_200.root mc11342_8_200.root mc11342_9_200.root mc11342_10_200.root",-1,-1,-1,  0.0,99.36,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_PYTHIA_2","MCSI","(Z/g)*","kLEP2","mc11343_1_200.root mc11343_2_200.root mc11343_3_200.root mc11343_4_200.root mc11343_5_200.root mc11343_6_200.root mc11343_7_200.root mc11343_8_200.root mc11343_9_200.root mc11343_10_200.root ",    -1,-1,-1,  0.0,8.574,0.0));
    //!!FIXME!
    AIStruct.push_back(new TSampleInfo(189.0,"189_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5169_1_200.root mc5169_2_200.root mc5169_3_200.root mc5169_4_200.root mc5169_5_200.root mc5169_6_200.root mc5169_7_200.root mc5169_8_200.root mc5169_9_200.root mc5169_10_200.root",    -1,-1,-1,  0.0,99.36,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11981_1_200.root mc11981_2_200.root mc11981_3_200.root mc11981_4_200.root",    -1,-1,-1,  0.0,99.36,0.0));

    AIStruct.push_back(new TSampleInfo(189.0,"189_GRC4F_1","MCBG","llqq","kLEP2","mc8055_1_200.root mc8055_2_200.root",    -1,-1,-1,  0.0,8.679,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_GRC4F_2","MCBG","qqqq","kLEP2","mc7846_1_200.root mc7846_2_200.root mc7846_3_200.root",    -1,-1,-1,  0.0,8.418,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_GRC4F_3","MCBG","eeqq","kLEP2","mc7849_1_200.root",    -1,-1,-1,  0.0,25.52,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_GRC4F_4","MCBG","llqq","kLEP2","mc8637_1_200.root mc8637_2_200.root",    -1,-1,-1,  0.0,8.679,0.0));
    AIStruct.push_back(new TSampleInfo(189.0,"189_GRC4F_5","MCBG","qqqq","kLEP2","mc8636_1_200.root mc8636_2_200.root",    -1,-1,-1,  0.0,8.418,0.0));






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

    AIStruct.push_back(new TSampleInfo(192.0,"192_DATA_1",  "DATA","ALL","kLEP2","da1999_200.root",  -1,-1,-1,29.53,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc11344_1_200.root mc11344_2_200.root mc11344_3_200.root mc11344_4_200.root",-1,-1,-1,  0.0,94.84,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5171_1_200.root mc5171_2_200.root mc5171_3_200.root mc5171_4_200.root",    -1,-1,-1,  0.0,94.84,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11986_1_200.root mc11986_2_200.root mc11986_3_200.root mc11986_4_200.root",    -1,-1,-1,  0.0,94.84,0.0));

    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_1","MCBG","llqq","kLEP2","mc8750_1_200.root mc8750_2_200.root",    -1,-1,-1,  0.0,8.997,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_2","MCBG","qqqq","kLEP2","mc8751_1_200.root mc8751_2_200.root mc8751_3_200.root",    -1,-1,-1,  0.0,8.657,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_3","MCBG","eeqq","kLEP2","mc9277_1_200.root",    -1,-1,-1,  0.0,41.43,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_4","MCBG","llqq","kLEP2","mc9205_1_200.root mc9205_2_200.root",    -1,-1,-1,  0.0,8.997,0.0));
    AIStruct.push_back(new TSampleInfo(192.0,"192_GRC4F_5","MCBG","qqqq","kLEP2","mc9204_1_200.root mc9204_2_200.root",    -1,-1,-1,  0.0,8.741,0.0));


    /*
    #NT_VERSION 200
    #196 GeV
    #Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #                       			(pb)	(1/pb)
    #Data     	ALL       196	0	76.67	0	da1999
    #PYTHIA		(Z/g)* 	11345	90.09	0.000	8	mc11345
    #HERWIG		(Z/g)*	5172	90.09	0.000	5	mc5172
    #*HERWIG		(Z/g)*	11987	90.09	0.000	4	mc11987
    #*ist ARIADNE     4!
    #*GRC4F		 llqq	9096	9.14	0.000	2	mc9096
    #*GRC4F		 qqqq	9097	8.816	0.000	3	mc9097
    #GRC4F		 eeqq	9280	40.5	0.000	1	mc9280
    #GRC4F		 llqq	9202	9.18	0.000	2	mc9202
    #*ist KoralW!
    #GRC4F		 qqqq	9201	8.921	0.000	2	mc9201
    #*ist KoralW!
    */



    AIStruct.push_back(new TSampleInfo(196.0,"196_DATA_1",  "DATA","ALL","kLEP2","da1999_200.root",  -1,-1,-1,76.67,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc11345_1_200.root mc11345_2_200.root mc11345_3_200.root mc11345_4_200.root",-1,-1,-1,  0.0,90.09,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5172_1_200.root mc5172_2_200.root mc5172_3_200.root mc5172_4_200.root",    -1,-1,-1,  0.0,90.09,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11987_1_200.root mc11987_2_200.root mc11987_3_200.root mc11987_4_200.root",    -1,-1,-1,  0.0,90.09,0.0));

    AIStruct.push_back(new TSampleInfo(196.0,"196_GRC4F_1","MCBG","llqq","kLEP2","mc9096_1_200.root mc9096_2_200.root",    -1,-1,-1,  0.0,9.140,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_GRC4F_2","MCBG","qqqq","kLEP2","mc9097_1_200.root mc9097_2_200.root mc9097_3_200.root",    -1,-1,-1,  0.0,8.816,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_GRC4F_3","MCBG","eeqq","kLEP2","mc9280_1_200.root",    -1,-1,-1,  0.0,40.50,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_GRC4F_4","MCBG","llqq","kLEP2","mc9202_1_200.root mc9202_2_200.root",    -1,-1,-1,  0.0,9.18,0.0));
    AIStruct.push_back(new TSampleInfo(196.0,"196_GRC4F_5","MCBG","qqqq","kLEP2","mc9201_1_200.root mc9201_2_200.root",    -1,-1,-1,  0.0,8.921,0.0));


    /*
    #NT_VERSION 200
    #202 GeV
    #Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #                       			(pb)	(1/pb)
    #Data		ALL	0	0	37.970	0	da1999
    #PYTHIA       	(Z/g)*	11347	83.36	0.000	4	mc11347
    #HERWIG   	(Z/g)*	5174	83.36	0.000	4	mc5174
    #*HERWIG   	(Z/g)*	11989	83.36	0.000	4	mc11989
    #*ist ARIADNE 4
    #*GRC4F		qqqq	9712	8.944	0.000	3	mc9712
    #*GRC4F		llqq	9711	9.319	0.000	2	mc9711
    #GRC4F		eeqq	9713	39.05	0.000	1	mc9713
    #GRC4F		llqq	9702	9.397	0.000	2	mc9702
    #* ist Koralw ver\\
    #GRC4F	        qqqq	9701	9.034	0.000	2	mc9701
    #* ist Koralw ver\\
    #NT_VERSION 200
    */



    AIStruct.push_back(new TSampleInfo(202.0,"202_DATA_1",  "DATA","ALL","kLEP2","da1999_200.root",  -1,-1,-1,37.970,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc11347_1_200.root mc11347_2_200.root mc11347_3_200.root mc11347_4_200.root",-1,-1,-1,  0.0,83.36,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5174_1_200.root mc5174_2_200.root mc5174_3_200.root mc5174_4_200.root",    -1,-1,-1,  0.0,83.36,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11989_1_200.root mc11989_2_200.root mc11989_3_200.root mc11989_4_200.root",    -1,-1,-1,  0.0,83.36,0.0));

    AIStruct.push_back(new TSampleInfo(202.0,"202_GRC4F_1","MCBG","qqqq","kLEP2","mc9712_1_200.root mc9712_2_200.root mc9712_3_200.root",    -1,-1,-1,  0.0,8.944,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_GRC4F_2","MCBG","llqq","kLEP2","mc9711_1_200.root mc9711_2_200.root",    -1,-1,-1,  0.0,9.319,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_GRC4F_3","MCBG","eeqq","kLEP2","mc9713_1_200.root",    -1,-1,-1,  0.0,39.05,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_GRC4F_4","MCBG","llqq","kLEP2","mc9702_1_200.root mc9702_2_200.root",    -1,-1,-1,  0.0,9.397,0.0));
    AIStruct.push_back(new TSampleInfo(202.0,"202_GRC4F_5","MCBG","qqqq","kLEP2","mc9701_1_200.root mc9701_2_200.root",    -1,-1,-1,  0.0,9.034,0.0));





    /*
    #NT_VERSION 200
    #205 GeV
    #Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #                       			(pb)	(1/pb)
    #Data		ALL	0	0	81.96	0	da2000
    #PYTHIA       	(Z/g)*	11349	81.31	0.000	8	mc11349
    #HERWIG   	(Z/g)*	5176	81.31	0.000	4	mc5176
    #*HERWIG   	(Z/g)*	11991	81.31	0.000	4	mc11991
    #*ist ARIADNE 4
    #*GRC4F		llqq	11213	9.39	0.000	3	mc11213
    #*GRC4F		qqqq	11214	8.967	0.000	3	mc11214
    #GRC4F		eeqq	11218	38.34	0.000	1	mc11218
    #GRC4F		llll+llqq+qqqq	11202	21.88	0.000	4	mc11202
    //CORRECTED llqq->llll
    #*ist Koralw ver\\
    */
//#GRC4F		llqq+llqq+qqqq+ww	11202	21.88	0.000	4	mc11202


    AIStruct.push_back(new TSampleInfo(205.0,"205_DATA_1",  "DATA","ALL","kLEP2","da2000_200.root",  -1,-1,-1,81.96,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc11349_1_200.root mc11349_2_200.root mc11349_3_200.root mc11349_4_200.root mc11349_5_200.root mc11349_6_200.root mc11349_7_200.root mc11349_8_200.root",-1,-1,-1,  0.0,81.31,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5176_1_200.root mc5176_2_200.root mc5176_3_200.root mc5176_4_200.root",    -1,-1,-1,  0.0,81.31,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11991_1_200.root mc11991_2_200.root mc11991_3_200.root mc11991_4_200.root",    -1,-1,-1,  0.0,81.31,0.0));

    AIStruct.push_back(new TSampleInfo(205.0,"205_GRC4F_1","MCBG","llqq","kLEP2","mc11213_1_200.root mc11213_2_200.root mc11213_3_200.root",    -1,-1,-1,  0.0,9.39,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_GRC4F_2","MCBG","qqqq","kLEP2","mc11214_1_200.root mc11214_2_200.root mc11214_3_200.root",    -1,-1,-1,  0.0,8.967,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_GRC4F_3","MCBG","eeqq","kLEP2","mc11218_1_200.root",    -1,-1,-1,  0.0,38.34,0.0));
    AIStruct.push_back(new TSampleInfo(205.0,"205_GRC4F_4","MCBG","llqq:qqqq:eeqq","kLEP2","mc11202_1_200.root mc11202_2_200.root mc11202_3_200.root mc11202_4_200.root",    -1,-1,-1,  0.0,21.88,0.0));

















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

    AIStruct.push_back(new TSampleInfo(207.0,"207_DATA_1",  "DATA","ALL","kLEP2","da2000_200.root",  -1,-1,-1,137.14,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_PYTHIA_1",  "MCSI","(Z/g)*","kLEP2","mc11352_1_200.root mc11352_2_200.root mc11352_3_200.root mc11352_4_200.root  mc11352_5_200.root \
                                                                            mc11352_6_200.root mc11352_7_200.root mc11352_8_200.root mc11352_9_200.root  mc11352_10_200.root \
                                                                            mc11352_11_200.root mc11352_12_200.root mc11352_13_200.root mc11352_14_200.root  mc11352_15_200.root",-1,-1,-1,  0.0,79.38,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc5179_1_200.root mc5179_2_200.root mc5179_3_200.root mc5179_4_200.root",        -1,-1,-1,  0.0,79.38,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_HERWIG_2","MCSI","(Z/g)*","kLEP2","mc11984_1_200.root mc11984_2_200.root mc11984_3_200.root mc11984_4_200.root",    -1,-1,-1,  0.0,79.38,0.0));

    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_1","MCBG","llqq","kLEP2","mc10781_1_200.root mc10781_2_200.root",    -1,-1,-1,  0.0,9.417,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_2","MCBG","qqqq","kLEP2","mc10782_1_200.root mc10782_2_200.root mc10782_3_200.root",    -1,-1,-1,  0.0,8.97,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_3","MCBG","eeqq","kLEP2","mc11212_1_200.root",    -1,-1,-1,  0.0,38.11,0.0));
    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_4","MCBG","llqq:qqqq:eeqq","kLEP2","mc10788_1_200.root mc10788_2_200.root mc10788_3_200.root mc10788_4_200.root",    -1,-1,-1,  0.0,21.87,0.0));
//    AIStruct.push_back(new TSampleInfo(207.0,"207_GRC4F_5","MCBG","kLEP2","mc9204_1_200.root mc9204_2_200.root",    -1,-1,-1,  0.0,8.741,0.0));




    /*
    #	NT_VERSION 200
    #	9196 GeV
    #	Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #	                       		(pb)	(1/pb)
    #	Data		ALL	0	0	1	0	da91_96
    #	PYTHIA       	(Z/g)*	5025	1.00	0	2	mc5025
    #        * JETSET 7.408
    #	HERWIG   	(Z/g)*	12406	1.00	0	2	mc12406
    #        * Herwig 6.2
    */

    AIStruct.push_back(new TSampleInfo(91.00,"9196_DATA_1",  "DATA","ALL","kLEP2","da91_96_200.root",  -1,-1,-1,1.00,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9196_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc5025_1_200.root mc5025_2_200.root",-1,-1,-1,  0.0,1.00,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9196_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc12406_1_200.root mc12406_2_200.root",-1,-1,-1,  0.0,1.00,0.0));




    /*
    #NT_VERSION 200
    #	9197 GeV
    #	Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #	                       		(pb)	(1/pb)
    #	Data		ALL	0	0	1	0	da91_97
    #	PYTHIA       	(Z/g)*	5073	1.00	0	2	mc5073
    #        * Jetset 7.408
    #	HERWIG   	(Z/g)*	12407	1.00	0	4	mc12407
    #        * Herwig 6.2
    */



    AIStruct.push_back(new TSampleInfo(91.00,"9197_DATA_1",  "DATA","ALL","kLEP2","da91_97_200.root",  -1,-1,-1,1.00,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9197_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc5073_1_200.root mc5073_2_200.root",-1,-1,-1,  0.0,1.00,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9197_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc12407_1_200.root mc12407_2_200.root mc12407_3_200.root mc12407_4_200.root",-1,-1,-1,  0.0,1.00,0.0));


    /*

    #NT_VERSION 200
    #	9198 GeV
    #	Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #	                       		(pb)	(1/pb)
    #	Data 	        ALL	0	0	1	2	da91_98
    #	PYTHIA       	(Z/g)*	12040	1.00	0	4	mc12040
    #        * JETSET 7.4
    #	HERWIG   	(Z/g)*	12408	1.00	0	4	mc12408
    #        * Herwig 6.2
    */



    AIStruct.push_back(new TSampleInfo(91.00,"9198_DATA_1",  "DATA","ALL","kLEP2","da91_98_1_200.root da91_98_2_200.root",  -1,-1,-1,1.00,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9198_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12040_1_200.root mc12040_2_200.root mc12040_3_200.root mc12040_4_200.root",-1,-1,-1,  0.0,1.00,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9198_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc12408_1_200.root mc12408_2_200.root mc12408_3_200.root mc12408_4_200.root",-1,-1,-1,  0.0,1.00,0.0));


    /*
    #	NT_VERSION 200
    #	9199 GeV
    #	Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #	                       		(pb)	(1/pb)
    #	Data 	        ALL	0	0	1	2	da91_99
    #	PYTHIA       	(Z/g)*	12138	1.00	0	4	mc12138
    #        * JETSET 7.408
    #	HERWIG   	(Z/g)*	12409	1.00	0	4	mc12409
    #       * Herwig 6.2
    */


    AIStruct.push_back(new TSampleInfo(91.00,"9199_DATA_1",  "DATA","ALL","kLEP2","da91_99_1_200.root da91_99_2_200.root",  -1,-1,-1,1.00,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9199_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12138_1_200.root mc12138_2_200.root mc12138_3_200.root",-1,-1,-1,  0.0,1.00,0.0));
    //!FIXME!!
    AIStruct.push_back(new TSampleInfo(91.00,"9199_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc12409_1_200.root mc12409_2_200.root mc12409_3_200.root mc12409_4_200.root",-1,-1,-1,  0.0,1.00,0.0));


    /*
    #	NT_VERSION 200
    #	9100 GeV
    #	Generator	Process	Runno	Sigma	Lumi	Part	filestem
    #	                       		(pb)	(1/pb)
    #	Data 	        ALL	0	0	1	2	da91_2k
    #	PYTHIA       	(Z/g)*	12139	1.00	0	4	mc12139
    #       * JETSET 7.4
    #	HERWIG   	(Z/g)*	12410	1.00	0	4	mc12410
    #        * Herwig 6.2
    */


    AIStruct.push_back(new TSampleInfo(91.00,"9100_DATA_1",  "DATA","ALL","kLEP2","da91_2k_1_200.root da91_2k_2_200.root",  -1,-1,-1,1.00,  0.0,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9100_PYTHIA_1","MCSI","(Z/g)*","kLEP2","mc12139_1_200.root mc12139_2_200.root mc12139_3_200.root mc12139_4_200.root",-1,-1,-1,  0.0,1.00,0.0));
    AIStruct.push_back(new TSampleInfo(91.00,"9100_HERWIG_1","MCSI","(Z/g)*","kLEP2","mc12410_1_200.root mc12410_2_200.root mc12410_3_200.root mc12410_4_200.root",-1,-1,-1,  0.0,1.00,0.0));


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
