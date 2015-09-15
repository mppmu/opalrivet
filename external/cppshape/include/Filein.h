#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <string>
#include <vector>

#include <TObject.h>

//using namespace std;
/*
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
*/
struct nt_attribute
{
    int     _cms;
    std::string  _diskname;
    std::string  _generator;
    std::string  _process;
    float   _lumi;
    float   _sigma;
    int     _runno;
    int     _part;
    int     _ntid;
};


class Filein : public TObject
{

public:

    Filein();
    Filein( std::string name );
    ~Filein();
    int nr_files();
    int cms();
    nt_attribute nt_info( int );
    std::string version();
    void print();

private:

    void init();
    void init2();
    std::string _version;
    std::string _filein_name;
    std::vector<nt_attribute> _ntname;
    
    ClassDef(Filein,0)
};

#endif
