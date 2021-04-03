#ifndef __INCLUDES_TYPES_HH_
#define __INCLUDES_TYPES_HH_

#include "include.hh"

struct TraceData {
  uint64_t sLBA;
  uint32_t nLB;
  bool isRead;
};

struct TimeData {
  uint32_t sec;
  uint32_t usec;
  friend bool operator<(const TimeData& t1, const TimeData& t2) {
    if (t1.sec != t2.sec)
      return t1.sec < t2.sec;
    else
      return t1.usec < t2.usec;
  }
  friend bool operator==(const TimeData& t1, const TimeData& t2) {
    return ((t1.sec == t2.sec) && (t1.usec == t2.usec));
  }
};

typedef uint64_t addr_t;

#endif  // __INCLUDES_TYPES_HH_