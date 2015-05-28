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
    A.insert(std::pair<std::string,std::map<std::string,double> >("antikt",B1));


    std::map<std::string,double> B2;
    A.insert(std::pair<std::string,std::map<std::string,double> >("durham",B2));

    std::map<std::string,double> B3;
    A.insert(std::pair<std::string,std::map<std::string,double> >("jade",B3));

    std::map<std::string,double> B4;
    A.insert(std::pair<std::string,std::map<std::string,double> >("cambridge",B4));

    std::map<std::string,double> B5;
    A.insert(std::pair<std::string,std::map<std::string,double> >("siscone",B5));

    return A;

}





#endif
