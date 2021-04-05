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