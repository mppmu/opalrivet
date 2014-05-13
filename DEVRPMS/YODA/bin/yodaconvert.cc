/* AV 2014 */
#include "YODA/WriterYODA.h"
#include "YODA/ReaderYODA.h"
#include "YODA/WriterFLAT.h"
#include "YODA/ReaderFLAT.h"
#include "YODA/WriterAIDA.h"
#include "YODA/ReaderAIDA.h"
#ifdef ENABLE_ROOT
#include "YODA/WriterROOT.h"
#include "YODA/ReaderROOT.h"
#endif
#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

using namespace std;
using namespace YODA;
enum formats {yoda, flat, aida
#ifdef ENABLE_ROOT
, root
#endif
};
int main(int argc, char** argv)
{
    if (argc<3)
        {
            printf("\
	Usage: %s <mode> <input_file.input_extension>    <output_file.output_extension>, or\n\
	       %s <mode> <input_file1[.input_extension]> <input_file2[.input_extension]> ...\n\
	Supported modes are: yoda2flat yoda2aida flat2yoda flat2aida aida2flat aida2yoda root2flat root2aida root2yoda.\n",argv[0],argv[0]);
            exit(1);
        }
    const  std::map<std::string,formats> format_map = { { "yoda", formats::yoda }, { "flat", formats::flat }, { "aida", formats::aida }
#ifdef ENABLE_ROOT
    , { "root", formats::root }       
#endif
    };
    std::vector<std::pair <std::string,std::string> > convert_list;
    std::pair<std::string,std::string> convert_formats;
    std::string mode(argv[1]);
    int i,j=0;
    for (i=0; i<mode.size(); i++)
        if (mode[i]!='2')
            {
                if (j==0) convert_formats.first+=mode[i];
                if (j==1) convert_formats.second+=mode[i];
                if (j>1)  {printf("Wrong mode string: %s\nMode string should be <format>2<format>.\n",argv[1]); exit(1);}
            }
        else j++;
    if (format_map.find(convert_formats.first )==format_map.end()) { printf("Input format %s is unknown.\n",convert_formats.first.c_str()); exit(2); }
    if (format_map.find(convert_formats.second)==format_map.end()) { printf("Output format %s is unknown.\n",convert_formats.second.c_str()); exit(2); }
    if (argc==4)
        {
            convert_list.push_back(std::pair<std::string,std::string>(std::string(argv[2]),std::string(argv[3])));
            if ((convert_list.back().first.substr(convert_list.back().first.find_last_of(".") + 1) != convert_formats.first) ||
                    (convert_list.back().second.substr(convert_list.back().second.find_last_of(".") + 1) != convert_formats.second))
                { printf("The conversion mode=%s doesn't match extensions of %s %s files\n",argv[1],argv[2],argv[3]); exit(1);}
        }
    else
        for (i=2; i<argc; i++)
            {
                convert_list.push_back(std::pair<std::string,std::string>(std::string(argv[i]),std::string(argv[i])));
                if (convert_list.back().first.substr(convert_list.back().first.find_last_of(".") + 1) == convert_formats.first)
                    convert_list.back().second.replace(convert_list.back().second.find_last_of(".") + 1,convert_formats.first.size(), convert_formats.second);
                else
                    {
                        convert_list.back().second+= ".";
                        convert_list.back().second+=convert_formats.second;
                    }
            }

    std::vector<AnalysisObject*> in;
    for (i=0; i<convert_list.size(); i++)
        {
            switch (format_map.at(convert_formats.first))
                {
                case formats::yoda:
                    in=ReaderYODA::create().read(convert_list[i].first);
                    break;
                case formats::flat:
                    in=ReaderFLAT::create().read(convert_list[i].first);
                    break;
                case formats::aida:
                    in=ReaderAIDA::create().read(convert_list[i].first);
                    break;
#ifdef ENABLE_ROOT
                case formats::root:
                    in=ReaderROOT::create(convert_list[i].first).read("just_a_place_holder");
                    break;
#endif
                default:
                    printf("Input format %s is unknown.\n",convert_formats.first.c_str());
                    exit(2);
                    break;
                }

            ofstream ofile;
            
            switch (format_map.at(convert_formats.second))
                {
                case formats::yoda:
                ofile.open (convert_list[i].second.c_str());
                    for (vector<AnalysisObject*>::const_iterator j = in.begin(); j != in.end(); ++j) YODA::WriterYODA::write(ofile, (**j));
                    ofile.close();
                    break;
                case formats::flat:
                ofile.open (convert_list[i].second.c_str());
                    for (vector<AnalysisObject*>::const_iterator j = in.begin(); j != in.end(); ++j) YODA::WriterFLAT::write(ofile, (**j));
                    ofile.close();
                    break;
                case formats::aida:
                ofile.open (convert_list[i].second.c_str());
                    for (vector<AnalysisObject*>::const_iterator j = in.begin(); j != in.end(); ++j) YODA::WriterAIDA::write(ofile, (**j));
                    ofile.close();
                    break;
#ifdef ENABLE_ROOT
                case formats::root:
                    for (vector<AnalysisObject*>::const_iterator j = in.begin(); j != in.end(); ++j) YODA::WriterROOT::write(convert_list[i].second.c_str(), (**j));                    
                    break;
#endif
                default:
                    printf("Output format %s is unknown.\n",convert_formats.second.c_str());
                    exit(2);
                    break;
                }
            
        }

    exit(0);
}
