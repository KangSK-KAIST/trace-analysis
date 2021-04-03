#ifndef __INCLUDES_TYPES_HH_
#define __INCLUDES_TYPES_HH_

#include "include.hh"

struct TraceData {
  uint32_t id;    // id used for key; given after sorting
  uint32_t sec;   // second of request
  uint32_t usec;  // microsecond of requset
  uint32_t nLB;   // length of request
  uint64_t sLBA;  // address of request
  bool isRead;    // whether request is read/write

  friend bool operator<(TraceData const& a1, TraceData const& a2) {
    if (a1.sec != a2.sec) {
      return a1.sec < a2.sec;
    }
    if (a1.usec != a2.usec) {
      return a1.usec < a2.usec;
    }
    if (a1.sLBA != a2.sLBA) {
      return a1.sLBA < a2.sLBA;
    }
    if (a1.nLB != a2.nLB) {
      return a1.nLB < a2.nLB;
    }
    return false;
  }

  friend bool operator==(TraceData const& a1, TraceData const& a2) {
    return ((a1.sec == a2.sec) && (a1.usec == a2.usec) &&
            (a1.sLBA == a2.sLBA) && (a1.nLB == a2.nLB));
  }
};

#endif  // __INCLUDES_TYPES_HH_