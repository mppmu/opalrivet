#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Filein.h"
#include "GlobalsUtil.h"
#include "special.h"

ostream & operator << ( std::ostream & os, nt_attribute & c )
{
    os << " cms: " << c._cms;
    os << " gen: " << std::setw(8) << c._generator;
    os << std::setw(8) << c._process;
    os << " run: " << std::setw(5) << c._runno;
    os << " xsec: " << std::setw(8) << c._sigma;
    os << " lumi: " << std::setw(8) << c._lumi;
    os << " part: " << std::setw(3) << c._part;
    os << "\non disk: " << c._diskname;
    os << std::endl;
    return os;
}



Filein::Filein()
{

    std::cout << "Filein::Filein: Give QCD admin file name:" << std::endl;
    std::cin >> _filein_name;
    std::cout << _filein_name << std::endl;
    init();

}


Filein::Filein( std::string filename )
{
	if (filename.length()!=0)
    _filein_name= filename;
    
    else
    {
    std::cout << "Filein::Filein: Give QCD admin file name:" << std::endl;
    std::cin >> _filein_name;
    std::cout << _filein_name << std::endl;
		
		
	}	
    
    init();
    
}


void Filein::init()
{
    // Open admin file:
    ifstream InputFile( _filein_name.c_str() );
    if( !InputFile )
        {
            std::cout << "Filein::init: Error opening file: " << _filein_name << std::endl;
            exit(1);
        }

    // Read admin records:
    int f_cms;
    std::string inBuf;
    while( getline( InputFile, inBuf ) )
        {

            // Split line into tokens by whitespace:
            std::istringstream line( inBuf );
            std::vector<std::string> tokens;
            std::string token;
            while( line >> token ) tokens.push_back( token );
            if( tokens.size() == 0 ) continue;

            // Get ntuple version:
            if( tokens[0].find( "NT_VERSION" ) != std::string::npos )
                {
                    std::istringstream token(tokens[1]);
                    token >> _version;
                }

            // Get ntuple E_cms:
            if( tokens.size() > 1 &&
                    tokens[1].find( "GeV" ) != std::string::npos )
                {
                    std::istringstream token(tokens[0]);
                    token >> f_cms;
                }

            // Find lines with data/generator information:
            bool match= false;
            for( int igen= 0; igen < nr_of_generator; igen++ )
                {
                    if( tokens[0].find( list_generator[igen] ) != std::string::npos )
                        {
                            match= true;
                            break;
                        }
                }
            if( match )
                {
                    nt_attribute nf;
                    nf._cms= f_cms;
                    int partit;
                    std::string fname;
                    line.clear();
                    line.str( inBuf );
                    line >> nf._generator >> nf._process >> nf._runno >> nf._sigma
                         >> nf._lumi >> partit >> fname;
                    if( !line.eof() )
                        {
                            line >> nf._ntid;
                        }
                    else
                        {
                            nf._ntid= 10;
                        }
                    for( int ipar= std::min( 1, partit ); ipar <= partit; ipar++ )
                        {
                            nf._part= std::max( 1, ipar );
                            std::ostringstream ostr;
                            ostr << base_ntfile_dir;
                            if( base_ntfile_dir.substr( base_ntfile_dir.size()-1 ) != "/" )
                                {
                                    ostr << "/";
                                }
                            ostr << fname << "_";
                            if( ipar == 0 )
                                {
                                    ostr << _version << ".histo";
                                }
                            else
                                {
                                    ostr << ipar << "_" << _version << ".histo";
                                }
                            nf._diskname= ostr.str();
                            _ntname.push_back( nf );
                        }
                }

        }

}


Filein::~Filein() {}


int Filein::cms()
{
    return _ntname[0]._cms;
}


std::string Filein::version()
{
    return _version;
}


void Filein::print()
{
    std::cout << "\n\t PROCESSING FILE \t" << _filein_name << std::endl;
    std::cout << "\t Ntuple version is " << _version << "\n\n" << std::endl;
    for( size_t i= 0; i < _ntname.size(); i++ )
        {
            std::cout << "(" << i << ")" << _ntname[i];
        }
    std::cout << "(" << nr_files() << " runnumbers in total) "<<std::endl;
}


int Filein::nr_files()
{
    return _ntname.size();
}


nt_attribute Filein::nt_info( int ifile )
{
    if( ifile < 0 || ifile > nr_files() )
        {
            std::cout << "Filein::nt_info: file nr " << ifile
                 << " not possible" << std::endl;
            exit(1);
        }
    return _ntname[ifile];
}
