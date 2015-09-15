#ifndef CUTS_H
#define CUTS_H
#include <map>
#include <string>
//#define ALGORITHMS "durham:cambridge:jade:eecambridge:antikt:kt:siscone"
#define ALGORITHMS "durham:cambridge:jade:siscone"
#define ENERGYTOLERANCE  1.5
std::map<std::string,std::map<std::string,double> > InitCuts();
#endif
