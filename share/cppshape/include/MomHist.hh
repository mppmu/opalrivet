#ifndef MOMHIST_HH
#define MOMHIST_HH


// This class manages a double array for each histo,
// implemented as singleton
// Use like this: MomHist::instance().packHistos()


#include <map>
// Can't use valarray on CERN lxplus museum systems
// #include <valarray>
#include <vector>
#include <string>

//using namespace std;
using std::map;
using std::vector;
using std::string;


// Define arrays and map:
// typedef valarray<double> d_array;
typedef vector<double> d_array;
typedef map<int,d_array*> IDMap;


class MomHist {

public:

  ~MomHist();

  // Create moment histo with ID, title and number of bins (n):
  void createHist( int, const string &, int );

  // Fill n moments in bins 1 to n, count events in bin n+1:
  void fillHist( int, double );

  // Divide by number of entries and pack into hbook histos
  // for all histos is map:
  void packHistos();

  // Return reference to single instance:
  static MomHist & instance();

private:

  // Private ctor:
  MomHist();

  // The map of histo IDs to array pointers:
  IDMap _coll;

  // Pointer to single instance:
  static MomHist* _momhist;

};


#endif
