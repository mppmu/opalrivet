// -*- C++ -*-
///g++ -std=c++11  ../hepmcconvert.cxx -L./outputs/lib -lHepMCrootIO -lHepMC   -I./include  -I./rootIO/include $(root-config --cflags --glibs) -o hepmcconvert
#include "HepMC/GenEvent.h"
#include "HepMC/Reader.h"
#include "HepMC/Writer.h"
#include "HepMC/ReaderAsciiHepMC2.h"
#include "HepMC/ReaderAscii.h"
#include "HepMC/WriterAscii.h"
#include "HepMC/Print.h"
#include "HepMC/GenEvent.h"
#include "HepMC/ReaderRoot.h"
#include "HepMC/WriterRoot.h"

#include "WriterRootTree.h"
#include <iostream>
#include <cstdlib> // atoi
using namespace HepMC;
using std::cout;
using std::endl;
enum formats {hepmc2, hepmc3, root,treeroot };
int main(int argc, char** argv)
{
    if (argc<3)
        {
            printf("\
	Usage: %s <mode> <input_file.input_extension>    <output_file.output_extension>, or\n\
	       %s <mode> <input_file1[.input_extension]> <input_file2[.input_extension]> ...\n\
	Supported modes are: hepmc2_root hepmc3_root etc.\n",argv[0],argv[0]);
            exit(1);
        }
    std::map<std::string,formats> format_map;
    format_map.insert(std::pair<std::string,formats> ( "hepmc2", hepmc2 ));
    format_map.insert(std::pair<std::string,formats> ( "hepmc3", hepmc3 ));
    format_map.insert(std::pair<std::string,formats> ( "root", root ));
    format_map.insert(std::pair<std::string,formats> ( "treeroot", treeroot ));

    std::map<std::string,std::string> extention_map;
    extention_map.insert(std::pair<std::string,std::string> ( "hepmc2","hepmc2" ));
    extention_map.insert(std::pair<std::string,std::string> ( "hepmc3", "hepmc3" ));
    extention_map.insert(std::pair<std::string,std::string> ( "root", "root" ));
    extention_map.insert(std::pair<std::string,std::string> ( "treeroot", "root" ));
    
    
    
    std::vector<std::pair <std::string,std::string> > convert_list;
    std::pair<std::string,std::string> convert_formats;
    std::string mode(argv[1]);
    unsigned int i,j=0;
    int k;
    for (i=0; i<mode.size(); i++)
        if (mode[i]!='_')
            {
                if (j==0) convert_formats.first+=mode[i];
                if (j==1) convert_formats.second+=mode[i];
                if (j>1)  {printf("Wrong mode string: %s\nMode string should be <format>_<format>.\n",argv[1]); exit(1);}
            }
        else j++;
    
        if (format_map.find(convert_formats.first )==format_map.end()) { printf("Input format %s is unknown.\n",convert_formats.first.c_str()); exit(2); }
    if (format_map.find(convert_formats.second)==format_map.end()) { printf("Output format %s is unknown.\n",convert_formats.second.c_str()); exit(2); }
    if (argc==4)
        {
            convert_list.push_back(std::pair<std::string,std::string>(std::string(argv[2]),std::string(argv[3])));
            if (
            (     convert_list.back().first.substr(convert_list.back().first.find_last_of(".") + 1)   != extention_map.at(convert_formats.first)) 
            ||
            (convert_list.back().second.substr(convert_list.back().second.find_last_of(".") + 1) != extention_map.at(convert_formats.second))
            )
            { printf("The conversion mode=%s is not suitable for extensions of %s %s files\n",argv[1],argv[2],argv[3]); exit(1);}
        }
    else
        for (k=2; k<argc; k++)
            {
                convert_list.push_back(std::pair<std::string,std::string>(std::string(argv[k]),std::string(argv[k])));
                if (convert_list.back().first.substr(convert_list.back().first.find_last_of(".") + 1) == convert_formats.first)
                    convert_list.back().second.replace(convert_list.back().second.find_last_of(".") + 1,convert_formats.first.size(), convert_formats.second);
                else
                    {
                        convert_list.back().second+= ".";
                        convert_list.back().second+=convert_formats.second;
                    }
            }    
for (i=0; i<convert_list.size(); i++)
        {
  int events_parsed = 0;
    int events_limit  = 0;
Reader*      input_file=0;            

            switch (format_map.at(convert_formats.first))
                {
                case hepmc2:
                    input_file=new ReaderAsciiHepMC2(convert_list[i].first);
                    break;
                case hepmc3:
                    input_file=new ReaderAscii(convert_list[i].first);
                    break;
                case root:
                    input_file=new ReaderRoot(convert_list[i].first);
                    break;
                default:
                    printf("Input format %s is unknown.\n",convert_formats.first.c_str());
                    exit(2);
                    break;
                }
Writer*      output_file=0;            
            switch (format_map.at(convert_formats.second))
                {
                case hepmc2:
                    printf("WARNING: hepmc3 format will be used instead of hepmc3.\n");
                    output_file=new WriterAscii(convert_list[i].second.c_str());
                    break;
                case hepmc3:
                    output_file=new WriterAscii(convert_list[i].second.c_str());
                    break;
                case root:
                    output_file=new WriterRoot(convert_list[i].second);
                    break;
                case treeroot:
                    output_file=new WriterRootTree(convert_list[i].second);
                    break;
                default:
                    printf("Output format %s is unknown.\n",convert_formats.second.c_str());
                    exit(2);
                    break;
                }
    while( !input_file->failed() ) {
        GenEvent evt(Units::GEV,Units::MM);
        input_file->read_event(evt);
        if( input_file->failed() ) break;
        output_file->write_event(evt);
        if(events_parsed==0) {
            cout << " First event: " << endl;
            Print::listing(evt);
        }
        evt.clear();
        ++events_parsed;
        if( events_parsed%100 == 0 ) cout<<"Events parsed: "<<events_parsed<<endl;
        if( events_limit && events_parsed >= events_limit ) break;
    }

    if (input_file) input_file->close();
    if (output_file) output_file->close();
}
    return 0;
}
