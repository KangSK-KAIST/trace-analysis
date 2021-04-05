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

#include "general_analyzer.hh"

static void analyzeDependTypes(std::vector<TraceData>* vTraceData,
                               std::map<id_t, std::set<id_t>>* mCentric,
                               bool isRead, int32_t* indep, int32_t* depShort,
                               int32_t* depLong) {
  for (auto trace : (*vTraceData)) {
    if (trace.isRead == isRead) {
      if (mCentric->count(trace.id)) {
        // Exists a corresponding write
        if ((*mCentric)[trace.id].size() > 1)
          (*depLong)++;
        else
          (*depShort)++;
      } else
        (*indep)++;
    }
  }
}

void analyze(std::vector<TraceData>* vTraceData,
             std::map<id_t, std::set<id_t>>* mReadCentric,
             std::map<id_t, std::set<id_t>>* mWriteCentric) {
  // Read breakdown
  int32_t indepReads = 0;     // Reads without correspoding writes
  int32_t depShortReads = 0;  // Reads connected to one write
  int32_t depLongReads = 0;   // Reads with multiple corresponding writes
  analyzeDependTypes(vTraceData, mReadCentric, true, &indepReads,
                     &depShortReads, &depLongReads);
  std::cout << "[Read BD]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << "\t" << indepReads << "\t" << depShortReads << "\t"
            << depLongReads << std::endl;

  // Write breakdown
  int32_t indepWrites = 0;     // Writes without correspoding writes
  int32_t depShortWrites = 0;  // Writes connected to one write
  int32_t depLongWrites = 0;   // Writes with multiple corresponding writes
  analyzeDependTypes(vTraceData, mWriteCentric, false, &indepWrites,
                     &depShortWrites, &depLongWrites);
  std::cout << "[Write BD]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << "\t" << indepWrites << "\t" << depShortWrites << "\t"
            << depLongWrites << std::endl;
}