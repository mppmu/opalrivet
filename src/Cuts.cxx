#ifndef CUTS_CXX
#define CUTS_CXX
#include "Cuts.h"




std::map<std::string,std::map<std::string,double> > InitCuts()
{
    std::map<std::string,std::map<std::string,double> > A;


    std::map<std::string,double> B0;
    B0.insert(std::pair<std::string,double>("Icjst",3));
    B0.insert(std::pair<std::string,double>("Iebst",3));
    B0.insert(std::pair<std::string,double>("Il2mh",1));
    B0.insert(std::pair<std::string,double>("Ntkd02",7));
    B0.insert(std::pair<std::string,double>("costt",0.9));
    B0.insert(std::pair<std::string,double>("wqqln",0.5));
    B0.insert(std::pair<std::string,double>("wqqqq",0.25));
    B0.insert(std::pair<std::string,double>("sprimedata",10.0));
    B0.insert(std::pair<std::string,double>("sprimemc",10.0));
    B0.insert(std::pair<std::string,double>("backgroundscale",1.0));
    B0.insert(std::pair<std::string,double>("objects",1.0));
    B0.insert(std::pair<std::string,double>("sprimalgo",1.0));
    A.insert(std::pair<std::string,std::map<std::string,double> >("central",B0));



    A.insert(std::pair<std::string,std::map<std::string,double> >("costtlow",B0));
    A["costtlow"]["costtlow"]=0.7;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqlnhigh",B0));
    A["wqqlnhigh"]["wqqln"]=0.75;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqlnlow",B0));
    A["wqqlnlow"]["wqqln"]=0.25;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqqqhigh",B0));
    A["wqqqqhigh"]["wqqqq"]=0.4;

    A.insert(std::pair<std::string,std::map<std::string,double> >("wqqqqlow",B0));
    A["wqqqqlow"]["wqqqq"]=0.10;

    A.insert(std::pair<std::string,std::map<std::string,double> >("backgroundlow",B0));
    A["backgroundlow"]["backgroundscale"]=0.95;

    A.insert(std::pair<std::string,std::map<std::string,double> >("backgroundhigh",B0));
    A["backgroundhigh"]["backgroundscale"]=1.05;


    A.insert(std::pair<std::string,std::map<std::string,double> >("mttotc",B0));
    A["mttotc"]["objects"]=2.0;


    A.insert(std::pair<std::string,std::map<std::string,double> >("sprm",B0));
    A["sprm"]["sprimalgo"]=2.0;


    /*


                const FReal spr_cut= 10.0;    // sprime reconstruction cut
                const FReal costt_stand= 0.9; // standard cos_thrust
                const FReal costt_var= 0.7;   // tight cos_thrust
                const FReal wqqln_stand= 0.5;       // like Joost: standard wqqln
                const FReal wqqln_hig  = 0.75;      //             tight wqqln cut
                const FReal wqqln_low  = 0.25;      //             loose wqqln cut
                const FReal wqqqq_stand= 0.25;      // like Joost: standard wqqqq
                const FReal wqqqq_hig  = 0.4;       //             tight wqqqq cut
                const FReal wqqqq_low  = 0.1;       //             loose wqqqq cut



    */

    std::map<std::string,double> B1;
    B1.insert(std::pair<std::string,double>("R",0.7));
    B1.insert(std::pair<std::string,double>("P",-1.0));
    A.insert(std::pair<std::string,std::map<std::string,double> >("antikt",B1));


    std::map<std::string,double> B2;
    B2.insert(std::pair<std::string,double>("R",0.7));
    A.insert(std::pair<std::string,std::map<std::string,double> >("durham",B2));


    std::map<std::string,double> B3;
    B3.insert(std::pair<std::string,double>("R",0.7));
    A.insert(std::pair<std::string,std::map<std::string,double> >("jade",B3));

    std::map<std::string,double> B4;
    B4.insert(std::pair<std::string,double>("R",0.7));
    B4.insert(std::pair<std::string,double>("P",-1.0));
    A.insert(std::pair<std::string,std::map<std::string,double> >("cambridge",B4));

    std::map<std::string,double> B5;
    B5.insert(std::pair<std::string,double>("R",0.75));
    B5.insert(std::pair<std::string,double>("OVERLAP_THRESHOLD",0.75));
    A.insert(std::pair<std::string,std::map<std::string,double> >("siscone",B5));


    std::map<std::string,double> B6;
    B6.insert(std::pair<std::string,double>("YMIN",1e-10));
    A.insert(std::pair<std::string,std::map<std::string,double> >("eecambridge",B6));



    std::map<std::string,double> B7;
    B7.insert(std::pair<std::string,double>("R",0.7));
    A.insert(std::pair<std::string,std::map<std::string,double> >("kt",B7));



    return A;

}





#endif
