#ifndef CUTS_H
#define CUTS_H
#include <map>
#include <string>
#define ALGORITHMS "durham:kt:antikt"
#define ENERGYTOLERANCE  1.5
std::map<std::string,std::map<std::string,double> > InitCuts();
#endif
