#include "general_analyzer.hh"

static void analyzeDependTypes(std::vector<TraceData>* vTraceData,
                               std::map<id_t, std::set<id_t>>* mCentric,
                               bool isRead, int32_t* indep, int32_t* depShort,
                               int32_t* depLong) {
  for (auto trace : (*vTraceData)) {
    if (trace.isRead == isRead) {
      if (mCentric->count(trace.id)) {
        // Exists a corresponding write
        if ((*mCentric)[trace.id].size() > 1)
          (*depLong)++;
        else
          (*depShort)++;
      } else
        (*indep)++;
    }
  }
}

void analyze(std::vector<TraceData>* vTraceData,
             std::map<id_t, std::set<id_t>>* mReadCentric,
             std::map<id_t, std::set<id_t>>* mWriteCentric) {
  // Read breakdown
  int32_t indepReads = 0;     // Reads without correspoding writes
  int32_t depShortReads = 0;  // Reads connected to one write
  int32_t depLongReads = 0;   // Reads with multiple corresponding writes
  analyzeDependTypes(vTraceData, mReadCentric, true, &indepReads,
                     &depShortReads, &depLongReads);
  std::cout << "[Read BD]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << "\t" << indepReads << "\t" << depShortReads << "\t"
            << depLongReads << std::endl;

  // Write breakdown
  int32_t indepWrites = 0;     // Writes without correspoding writes
  int32_t depShortWrites = 0;  // Writes connected to one write
  int32_t depLongWrites = 0;   // Writes with multiple corresponding writes
  analyzeDependTypes(vTraceData, mWriteCentric, false, &indepWrites,
                     &depShortWrites, &depLongWrites);
  std::cout << "[Write BD]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << "\t" << indepReads << "\t" << depShortReads << "\t"
            << depLongReads << std::endl;
}