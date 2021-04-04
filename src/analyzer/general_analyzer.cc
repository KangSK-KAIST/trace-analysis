#include "general_analyzer.hh"

static void analyzeReadTypes(std::vector<TraceData>* vTraceData,
                             std::map<id_t, std::vector<id_t>>* mReadCentric,
                             std::map<id_t, std::vector<id_t>>* mWriteCentric,
                             int32_t* indepReads, int32_t* depShortReads,
                             int32_t* depLongReads, int32_t* writes) {
  for (auto trace : (*vTraceData)) {
    if (trace.isRead) {
      if (mReadCentric->count(trace.id)) {
        // Exists a corresponding write
        if ((*mReadCentric)[trace.id].size() > 1)
          (*depLongReads)++;
        else
          (*depShortReads)++;
      } else
        (*indepReads)++;
    } else
      (*writes)++;
  }
}

void analyze(std::vector<TraceData>* vTraceData,
             std::map<id_t, std::vector<id_t>>* mReadCentric,
             std::map<id_t, std::vector<id_t>>* mWriteCentric) {
  int32_t indepReads = 0;     // Reads without correspoding writes
  int32_t depShortReads = 0;  // Reads connected to one write
  int32_t depLongReads = 0;   // Reads with multiple corresponding writes
  int32_t writes = 0;         // Writes
  analyzeReadTypes(vTraceData, mReadCentric, mWriteCentric, &indepReads,
                   &depShortReads, &depLongReads, &writes);
  std::cout << "Independent\tDep_Short\tDep_Long\tWrites" << std::endl;
  std::cout << indepReads << "\t" << depShortReads << "\t" << depLongReads
            << "\t" << writes << std::endl;
}