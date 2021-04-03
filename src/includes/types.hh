#ifndef __INCLUDES_TYPES_HH_
#define __INCLUDES_TYPES_HH_

#include "include.hh"

struct TraceData {
  uint32_t sec;
  uint32_t usec;
  uint64_t sLBA;
  uint32_t nLB;
  bool isRead;
};

#endif  // __INCLUDES_TYPES_HH_