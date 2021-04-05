#ifndef __GENENERAL_ANALYZER_HH_
#define __GENENERAL_ANALYZER_HH_

#include "../includes/include.hh"
#include "../includes/types.hh"

void analyze(std::vector<TraceData>* vTraceData,
             std::map<id_t, std::set<id_t>>* mReadCentric,
             std::map<id_t, std::set<id_t>>* mWriteCentric);

#endif  //__GENENERAL_ANALYZER_HH_