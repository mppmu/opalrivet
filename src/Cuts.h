#ifndef CUTS_H
#define CUTS_H
#include <map>
#include <string>
//#define ALGORITHMS "durham:cambridge:jade:eecambridge:antikt:kt:siscone"
#define ALGORITHMS "durham:jade:siscone:cambridge:antikt"
std::map<std::string,std::map<std::string,double> > InitCuts();
#endif
