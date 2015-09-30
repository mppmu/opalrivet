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
//http://stackoverflow.com/questions/599989/is-there-a-built-in-way-to-split-strings-in-c
static void Filein_tokenize(const std::string& str, const std::string& delimiters , std::vector<std::string>& tokens)
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
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

if (inBuf[0]=='*') {  printf("Commented line");  continue;}

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
                    
                    // Obviously wrong line if( tokens[0].find( list_generator[igen] ) != std::string::npos )
                        if (tokens[0]==std::string(list_generator[igen]))
                        {
							
							printf ("Found Gen: %s\n",tokens[0].c_str());
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
                    
                    std::vector<std::string> tokens;
                    Filein_tokenize(inBuf," ",tokens);
                    printf("->%s<-\n",inBuf.c_str());
                    if (tokens.size()<7) continue;
                    printf("->%s<-\n",inBuf.c_str());
                    std::stringstream stokens[tokens.size()];
                    for (int kk=0;kk<tokens.size();kk++)  stokens[kk].str(tokens[kk].c_str()); 
                    stokens[0]>>nf._generator;
                    stokens[1]>>nf._process;
                    stokens[2]>>nf._runno;
                    stokens[3]>>nf._sigma;
                    stokens[4]>>nf._lumi;
                    stokens[5]>>partit;
                    stokens[6]>>fname;
                    if (tokens.size()>7) stokens[7]>>nf._ntid;                    else  nf._ntid= 10;
                    
                    printf("%s %s %i %f %f %i %s %i\n",
                    nf._generator.c_str(),
                    nf._process.c_str(),
                    nf._runno,
                    nf._sigma,
                    nf._lumi,
                    partit,
                    fname.c_str(),
                    nf._ntid);
                    /* Best example how not to write a code
                    
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
                            
                            */
                            
                        for( int ipar= std::min( 1, partit ); ipar <= partit; ipar++ )
                        {
                            nf._part= std::max( 1, ipar );
                            std::string ostr=base_ntfile_dir;                            
                            if( base_ntfile_dir.substr( base_ntfile_dir.size()-1 ) != "/" )
                                {
                                    ostr += "/";
                                }
                            ostr += fname;
                            ostr +=  "_";
                            if( ipar == 0 )
                                {
                                    ostr += _version; ostr +=".histo";
                                }
                            else
                                {
									char bbuf[20];
									sprintf(bbuf,"%i",ipar);
                                    ostr +=std::string(bbuf);
                                     ostr += "_";
                                      ostr += _version;
                                       ostr += ".histo";
                                }
                            nf._diskname= ostr;
                            printf("---->%s<-\n",ostr.c_str());
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
