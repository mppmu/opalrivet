#include "YODA/WriterYODA.h"
#include "YODA/ReaderROOT.h"
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
using namespace YODA;
int main(int argc, char** argv)
{
	if (argc<2) { printf("Usage: %s INPUT.root OUTPUT.yoda\n",argv[0]);   exit(1); }
	ofstream ofile;
    ofile.open (argv[2]);
	std::vector<AnalysisObject*> aos;
	vector<AnalysisObject*> hs3 = ReaderROOT::create(argv[1]).read("just_a_place_holder");
	for (vector<AnalysisObject*>::const_iterator i = hs3.begin(); i != hs3.end(); ++i)
	YODA::WriterYODA::write(ofile, (**i));
	ofile.close();
	exit(0);
}	

