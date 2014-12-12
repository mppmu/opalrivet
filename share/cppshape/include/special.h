#ifndef SPEC_H
#define SPEC_H
#include "GlobalsUtil.h"
//using namespace std;

extern std::string base_ntfile_dir;

extern const int     nr_of_moments;

extern const int     max_nr_hist;

extern const int     nr_of_generator;
extern const std::string  list_generator[];

extern const int     nr_of_process ;
extern const std::string  list_process[];

extern const int     nr_of_recon;
extern const std::string  list_recon[];

extern const int     nr_of_mcrecon;
extern const std::string  list_mcrecon[];

// extern const int     nr_of_mccuts;
// extern const string  list_mccuts[];

extern const std::vector<std::string> v_gen;
extern const std::vector<std::string> v_proc;
extern std::vector<std::string> v_obs;
extern const std::vector<std::string> v_reco;
extern const std::vector<std::string> v_mcreco;
extern std::vector<std::string> v_cuts;

// extern const vector<string> v_mccuts;
extern std::vector<std::string> v_mccuts;

extern GlobalsUtil GUtil;
#endif
