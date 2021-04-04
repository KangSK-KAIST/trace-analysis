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
                std::map<id_t, std::vector<id_t>>* mReadCentric,
                std::map<id_t, std::vector<id_t>>* mWriteCentric) {
  // Simulate the whole memory as a map
  std::map<addr_t, TraceData> memory;

  // Iterate through all traces
  for (auto trace : *vTraceData) {
    if (trace.isRead) {
      // The trace is a read; insert all owners
      std::vector<id_t> owners;
      for (auto segment : memory) {
        // Loop through memory segments
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
      // std::cout << owners.empty() << std::endl;
      if (!owners.empty()) {
        // Existed owner; add to read centric map
        mReadCentric->insert(std::make_pair(trace.id, std::move(owners)));
        // TODO Add to all write centric map
      }
    } else {
      // The trace is a write; apply segmentation
      addr_t head = 0;
      addr_t tail = 0;
      addr_t huge = 0;
      std::vector<addr_t> dead;  // Dead may be multiple
      // Read basic params
      addr_t startTrace = trace.sLBA;
      addr_t endTrace = trace.sLBA + trace.nLB;

      // Loop through memory segments
      for (auto segment : memory) {
        // Read basic params
        addr_t startSegment = segment.first;
        addr_t endSegment = segment.first + segment.second.nLB;
        TraceData data = segment.second;
        // If start of segment is larger than end of trace, break
        if (endTrace <= startSegment) break;
        // head case (segment begin < trace begin < segment end <= trace end)
        if ((startSegment < startTrace) && (startTrace < endSegment) &&
            (endSegment <= endTrace)) {
          head = data.id;
        }
        // dead case (trace begin <= segment begin < segment end <= trace end)
        else if ((startTrace <= startSegment) && (endSegment <= endTrace)) {
          dead.push_back(data.id);
        }
        // tail case (trace begin <= segment begin < trace end < segment end)
        else if ((startTrace <= startSegment) && (startSegment < endTrace) &&
                 (endTrace < endSegment)) {
          tail = data.id;
        }
        // huge case (segment begin < trace begin < trace end < segment end)
        else if ((startSegment < startTrace) && (endTrace < endSegment)) {
          huge = data.id;
        }
      }
      // Finished looping; Modify map
      if (head) {
        // Read basic params
        TraceData data = (*vTraceData)[head];
        addr_t startSegment = data.sLBA;
        // Delete/Modify map
        data.sLBA = startSegment;
        data.nLB = startTrace - startSegment;
        memory.erase(startSegment);
        memory.insert(std::make_pair(startSegment, std::move(data)));
      }
      if (tail) {
        // Read basic params
        TraceData data = (*vTraceData)[tail];
        addr_t startSegment = data.sLBA;
        addr_t endSegment = data.sLBA + data.nLB;
        // Delete/Modify map
        data.sLBA = endTrace;
        data.nLB = endSegment - endTrace;
        memory.erase(startSegment);
        memory.insert(std::make_pair(endTrace, std::move(data)));
      }
      if (huge) {
        // Read basic params
        TraceData data = (*vTraceData)[huge];
        addr_t startSegment = data.sLBA;
        addr_t endSegment = data.sLBA + data.nLB;
        // Delete/Modify map
        TraceData dataHead = data;
        TraceData dataTail = data;
        dataHead.sLBA = startTrace;
        dataHead.nLB = startTrace - startSegment;
        dataTail.sLBA = endTrace;
        dataTail.nLB = endSegment - endTrace;
        memory.erase(startSegment);
        memory.insert(std::make_pair(startSegment, std::move(dataHead)));
        memory.insert(std::make_pair(endTrace, std::move(dataTail)));
      }
      for (auto id : dead) {
        // Read basic params
        TraceData data = (*vTraceData)[id];
        addr_t startSegment = data.sLBA;
        // Delete/Modify map
        memory.erase(startSegment);
      }
      // Add new trace to map
      memory.insert(std::make_pair(trace.sLBA, trace));
    }
  }
}