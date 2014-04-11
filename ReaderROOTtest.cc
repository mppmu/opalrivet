
#include "YODA/Histo1D.h"
#include "YODA/WriterAIDA.h"
#include "YODA/WriterYODA.h"
#include "YODA/ReaderAIDA.h"
#include "YODA/ReaderYODA.h"
#include "YODA/ReaderROOT.h"
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
using namespace YODA;
int main()
{
	
	std::vector<AnalysisObject*> aos;
	//std::ifstream is("1.txt"); 
	
	//ReaderROOT* A= new ReaderROOT();
	//A->read(is,  aos);
	
	vector<AnalysisObject*> hs3 = ReaderROOT::create().read("1.root");
	
	  for (vector<AnalysisObject*>::const_iterator i = hs3.begin(); i != hs3.end(); ++i) {
    cout << (*i)->type() << endl;
    YODA::WriterYODA::write(std::cout, (**i));
          }
	exit(0);
	
	
}	

