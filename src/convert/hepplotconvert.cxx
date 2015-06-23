/*
 * hepplotconvert.cxx
 *
 * Copyright 2014,2015 Andrii Verbytskyi <andriish@mppmu.mpg.de>
 * Max-Planck Institut für Physik
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
#include "YODA/WriterYODA.h"
#include "YODA/ReaderYODA.h"
#include "YODA/WriterFLAT.h"
#include "YODA/ReaderFLAT.h"
#include "YODA/WriterAIDA.h"
#include "YODA/ReaderAIDA.h"
#include "WriterROOT.h"
#include "ReaderROOT.h"
#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

using namespace std;
using namespace YODA;
enum formats {yoda, flat, aida, root };
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
    const  std::map<std::string,formats> format_map = { { "yoda", formats::yoda }, { "flat", formats::flat }, { "aida", formats::aida } , { "root", formats::root }};
    std::vector<std::pair <std::string,std::string> > convert_list;
    std::pair<std::string,std::string> convert_formats;
    std::string mode(argv[1]);
    unsigned int i,j=0;
    int k;
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
                case formats::root:
                    in=ReaderROOT::create(convert_list[i].first).read("just_a_place_holder");
                    break;
                default:
                    printf("Input format %s is unknown.\n",convert_formats.first.c_str());
                    exit(2);
                    break;
                }



            switch (format_map.at(convert_formats.second))
                {
                case formats::yoda:
                    YODA::WriterYODA::create().write(convert_list[i].second.c_str(), in);
                    break;
                case formats::flat:
                    YODA::WriterFLAT::create().write(convert_list[i].second.c_str(), in);
                    break;
                case formats::aida:
                    YODA::WriterAIDA::create().write(convert_list[i].second.c_str(), in);
                    break;
                case formats::root:
                    YODA::WriterROOT::create(convert_list[i].second.c_str()).write("just_a_place_holder",in);
                    break;
                default:
                    printf("Output format %s is unknown.\n",convert_formats.second.c_str());
                    exit(2);
                    break;
                }

        }

    exit(0);
}
