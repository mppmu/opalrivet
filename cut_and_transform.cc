/* AV 2014 */
#include "YODA/WriterYODA.h"
#include "YODA/ReaderYODA.h"
#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

using namespace std;
using namespace YODA;
enum formats {yoda, flat, aida, root};
int main(int argc, char** argv)
{
    if (argc<4)
        {
            printf("\
	Usage: %s   <set_0_bin_width=yes|no>  <input_file.input_extension>    <histohram_path>  [<new_histohram_path>]\n",argv[0]);
            exit(1);
        }
    std::vector<AnalysisObject*> in;
    in=ReaderYODA::create().read(argv[2]);
    for (vector<AnalysisObject*>::const_iterator j = in.begin(); j != in.end(); ++j)
        {
            if (((*j)->type()=="Scatter2D")&&((*j)->path()==argv[3]))
                {
Scatter2D* S=(Scatter2D*)(*j);
                    if (!strcmp("yes",argv[1]))
                        {
                            int i;
                            
                            for (i=0;	i<S->numPoints(); i++)
                                {

                                    S->point(i).setXErrMinus(0);
                                    S->point(i).setXErrPlus(0);

                                }

                        }
                        
                        
                       if (argc==5) S->setPath(argv[4]);
                    YODA::WriterYODA::write(std::cout, (**j));

                }
        }
    exit(0);
}
