#include "general_saver.hh"

void saveTrace(std::string name, std::vector<TraceData>* vTraceData,
               std::map<id_t, std::vector<id_t>>* mReadCentric) {
  std::ofstream file(name);
  if (!file.is_open()) {
    std::cerr << "[ERROR]\tFile open error" << std::endl;
    std::terminate();
  }
  for (auto trace : (*vTraceData)) {
    if (trace.isRead) {
      if (mReadCentric->count(trace.id)) {
        // Exists a corresponding write
        file << "0,R," << trace.sLBA << "," << trace.nLB << "," << trace.sec
             << trace.psec << std::endl;
      } else {
        // Is a write
        file << "0,W," << trace.sLBA << "," << trace.nLB << "," << trace.sec
             << trace.psec << std::endl;
      }
    }
    file.close();
  }
}