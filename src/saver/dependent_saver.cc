#include "general_saver.hh"

void saveTrace(std::string name, std::vector<TraceData>* vTraceData,
               std::map<id_t, std::vector<id_t>>* mReadCentric) {
  for (auto trace : (*vTraceData)) {
    if (trace.isRead) {
      if (mReadCentric->count(trace.id)) {
        // Exists a corresponding write
        std::cout << "0,R," << trace.sLBA << "," << trace.nLB << ","
                  << trace.sec << trace.psec << "\n";
      }
    } else {
      // Is a write
      std::cout << "0,W," << trace.sLBA << "," << trace.nLB << "," << trace.sec
                << trace.psec << "\n";
    }
  }
}