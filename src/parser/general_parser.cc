// MIT License

// Copyright (c) 2021 KangSK-KAIST

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "general_parser.hh"

void parseTrace(std::vector<TraceData>* vTraceData, TraceData** aMemory,
                int64_t pageMin,
                std::map<id_t, std::vector<id_t>>* mReadCentric,
                std::map<id_t, std::vector<id_t>>* mWriteCentric) {
// Iterate through all traces
#ifdef LOGGING
  std::cerr << "[LOG]\tParsingFile..." << std::endl;
  int64_t segCount = 0;
  int counter = 0;
#endif
  for (auto trace : *vTraceData) {
#ifdef LOGGING
    if (counter++ % 1000 == 0)
      std::cerr << "[LOG]\t" << segCount / 1024 / 1024 << "MB data transfered"
                << std::endl;  // segCount * 512 / 1024 / 1024
    segCount += trace.nLB;
#endif
    if (trace.isRead) {
      // The trace is a read; insert all owners
      std::vector<id_t> owners;
      if (!owners.empty()) std::terminate();

      // Read basic params (in page-level mapping)
      page_t startTrace = trace.sLBA / PAGE_SIZE - pageMin;
      page_t endTrace = (trace.sLBA + trace.nLB) / PAGE_SIZE - pageMin;
      // Read through all passing pages
      for (int64_t i = startTrace; i <= endTrace; i++) {
        // Push back the owner of the page
        TraceData data = (*aMemory)[i];
        if ((data.sec == 0) && (data.psec == 0))
          continue;  // First access to this page
        owners.push_back(data.id);
      }
      if (!owners.empty()) {
        // Add to all write centric map
        for (auto owner : owners) {
          std::vector<id_t> users;
          if (mWriteCentric->count(owner)) {
            // This owner was already used
            users = (*mWriteCentric)[owner];
            mWriteCentric->erase(owner);
          }
          users.push_back(trace.id);
          mWriteCentric->insert(std::make_pair(owner, std::move(users)));
        }
        // Existed owner; add to read centric map
        mReadCentric->insert(std::make_pair(trace.id, std::move(owners)));
      }
    } else {
      // The trace is a write; overwrite
      // Read basic params (in page-level mapping)
      page_t startTrace = trace.sLBA / PAGE_SIZE - pageMin;
      page_t endTrace = (trace.sLBA + trace.nLB) / PAGE_SIZE - pageMin;
      // Read through all passing pages
      for (int64_t i = startTrace; i <= endTrace; i++) {
        // Overwrite all pages
        (*aMemory)[i] = trace;
      }
    }
  }
}