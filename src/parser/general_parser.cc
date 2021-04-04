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

void parseTrace(std::vector<TraceData>* vTraceData,
                std::map<addr_t, TraceData>* mMemory,
                std::map<id_t, std::vector<id_t>>* mReadCentric,
                std::map<id_t, std::vector<id_t>>* mWriteCentric) {
  // Iterate through all traces
  std::cerr << "[LOG]\tParsingFile..." << std::endl;
#ifdef LOGGING
  int segCount = 0;
  int counter = 0;
#endif
  for (auto trace : *vTraceData) {
#ifdef LOGGING
    if (counter++ % 1000 == 0)
      std::cerr << "[LOG]\t" << segCount / 2048 << "MB data transfered"
                << std::endl;  // segCount * 512 / 1024 / 1024
    segCount += trace.nLB;
#endif
    if (trace.isRead) {
      // The trace is a read; insert all owners
      std::vector<id_t> owners;
      if (!owners.empty()) std::terminate();

      // Loop through memory segments
      for (auto segment : (*mMemory)) {
        // Read basic params
        addr_t startTrace = trace.sLBA;
        addr_t endTrace = trace.sLBA + trace.nLB;
        addr_t startSegment = segment.first;
        addr_t endSegment = segment.first + segment.second.nLB;
        // If start of segment is larger than end of trace, break
        if (endTrace <= startSegment) break;
        // If segment and trace overlap, add to owner
        if ((startTrace < endSegment) && (startSegment < endTrace)) {
          owners.push_back(segment.second.id);
        }
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
      // The trace is a write; apply segmentation
      // Read basic params
      addr_t startTrace = trace.sLBA;
      addr_t endTrace = trace.sLBA + trace.nLB;
      // Cases to handle
      addr_t head = -1;
      addr_t tail = -1;
      addr_t huge = -1;
      std::vector<addr_t> dead;  // Dead may be multiple
      // Loop through memory segments
      for (auto segment : (*mMemory)) {
        // Read basic params
        addr_t startSegment = segment.first;
        addr_t endSegment = segment.first + segment.second.nLB;
        TraceData data = segment.second;
        // If start of segment is larger than end of trace, break
        if (endTrace <= startSegment) break;
        // head case (segment begin < trace begin < segment end <= trace end)
        if ((startSegment < startTrace) && (startTrace < endSegment) &&
            (endSegment <= endTrace)) {
          head = data.sLBA;
        }
        // dead case (trace begin <= segment begin < segment end <= trace end)
        else if ((startTrace <= startSegment) && (endSegment <= endTrace)) {
          dead.push_back(data.sLBA);
        }
        // tail case (trace begin <= segment begin < trace end < segment end)
        else if ((startTrace <= startSegment) && (startSegment < endTrace) &&
                 (endTrace < endSegment)) {
          tail = data.sLBA;
        }
        // huge case (segment begin < trace begin < trace end < segment end)
        else if ((startSegment < startTrace) && (endTrace < endSegment)) {
          huge = data.sLBA;
        }
      }
      // Finished looping; modify map
      if (head != -1) {
        // Read basic params
        TraceData data = (*mMemory)[head];
        addr_t startSegment = data.sLBA;
        // Delete/Modify map
        data.sLBA = startSegment;
        data.nLB = startTrace - startSegment;
        mMemory->erase(head);
        mMemory->insert(std::make_pair(startSegment, std::move(data)));
      }
      if (tail != -1) {
        // Read basic params
        TraceData data = (*mMemory)[tail];
        addr_t endSegment = data.sLBA + data.nLB;
        // Delete/Modify map
        data.sLBA = endTrace;
        data.nLB = endSegment - endTrace;
        mMemory->erase(tail);
        mMemory->insert(std::make_pair(endTrace, std::move(data)));
      }
      if (huge != -1) {
        // Read basic params
        TraceData data = (*mMemory)[huge];
        addr_t startSegment = data.sLBA;
        addr_t endSegment = data.sLBA + data.nLB;
        // Delete/Modify map
        TraceData dataHead = data;
        TraceData dataTail = data;
        dataHead.sLBA = startSegment;
        dataHead.nLB = startTrace - startSegment;
        dataTail.sLBA = endTrace;
        dataTail.nLB = endSegment - endTrace;
        mMemory->erase(huge);
        mMemory->insert(std::make_pair(startSegment, std::move(dataHead)));
        mMemory->insert(std::make_pair(endTrace, std::move(dataTail)));
      }
      for (auto id : dead) {
        mMemory->erase(id);
      }
      // Add new trace to map
      mMemory->insert(std::make_pair(trace.sLBA, trace));
    }
  }
}