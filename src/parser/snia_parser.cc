#include "snia_parser.hh"

void sort_trace(std::vector<TraceData> *vTraceData) {
  std::sort(vTraceData->begin(), vTraceData->end(),
            [](TraceData const &a, TraceData const &b) -> bool {
              // First look at op type; write first
              if (!a.isRead && b.isRead) return true;
              if (a.isRead && !b.isRead) return false;
              // Second look at time; early first
              if (a.sec != b.sec) return a.sec < b.sec;
              if (a.usec != b.usec) return a.usec < b.usec;
              // Third look at address; lower address first
              if (a.sLBA != b.sLBA) return a.sLBA < b.sLBA;
              // Last look at size; larger first
              if (a.nLB != b.nLB) return a.nLB > b.nLB;
            });
}

int parse_trace(std::vector<TraceData> *vTraceData) {
  sort_trace(vTraceData);
  return 0;
}