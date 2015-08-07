#ifndef CUTS_CXX
#define CUTS_CXX
#include "Cuts.h"




std::map<std::string,std::map<std::string,double> > InitCuts()
{
    std::map<std::string,std::map<std::string,double> > A;


    std::map<std::string,double> B0;
    B0.insert(std::pair<std::string,double>("Icjst",3));
    B0.insert(std::pair<std::string,double>("Iebst",3));
    B0.insert(std::pair<std::string,double>("Itkmh",1));
    B0.insert(std::pair<std::string,double>("Ntkd02",5));
    B0.insert(std::pair<std::string,double>("Inonr",1));
    B0.insert(std::pair<std::string,double>("costt",0.9));
    A.insert(std::pair<std::string,std::map<std::string,double> >("data",B0));



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
