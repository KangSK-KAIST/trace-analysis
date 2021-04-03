#ifndef __READER_RAW_FILE_READER_HH
#define __READER_RAW_FILE_READER_HH

#include "../includes/include.hh"
#include "../includes/types.hh"

int read_trace(std::string fileName, std::vector<TraceData> *vTraceData);

#endif  // __READER_RAW_FILE_READER_HH