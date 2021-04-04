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

#include "analyzer/general_analyzer.hh"
#include "includes/include.hh"
#include "includes/types.hh"
#include "parser/general_parser.hh"
#include "reader/general_reader.hh"

int main(int argc, char** argv) {
  // std::string fileName(
  //     "/home/kangsk/gitrepo/trace-analysis/snia_refined/MSEnterprise/"
  //     "Enterprise1.total.csv.orig");
  if (argc < 3) {
    std::cerr << "Usage: main [input filename] [size of transfer (in MB)]"
              << std::endl;
    std::terminate();
  }

  std::string fileName(argv[1]);
  std::string sizeInput(argv[2]);
  int32_t size = strtoul(sizeInput.c_str(), nullptr, 10);

  std::vector<TraceData> vTraceData;
  printStat(fileName);
  readTrace(fileName, &vTraceData, size);

#ifdef DEBUG
  int count = 0;
  for (auto iter = vTraceData.begin(); count++ < 20; iter++) {
    std::cerr << iter->id << " " << iter->psec << " " << iter->sLBA << " "
              << iter->isRead << std::endl;
  }
#endif

  // Simulate the whole memory as a map
  std::map<addr_t, TraceData> mMemory;
  // <Read time, Write time>, <Write time, Read time>
  std::map<id_t, std::vector<id_t>> mReadCentric;
  std::map<id_t, std::vector<id_t>> mWriteCentric;
  parseTrace(&vTraceData, &mMemory, &mReadCentric, &mWriteCentric);

#ifdef DEBUG
  std::cerr << "==================" << std::endl;
  for (auto readOwn : mReadCentric) {
    for (auto data : readOwn.second)
      std::cerr << readOwn.first << "\t" << data << std::endl;
  }
  std::cerr << "==================" << std::endl;
  for (auto writeOwn : mWriteCentric) {
    for (auto data : writeOwn.second)
      std::cerr << writeOwn.first << "\t" << data << std::endl;
  }
#endif

  analyze(&vTraceData, &mReadCentric, &mWriteCentric);

  // save_pickle();
  // analyze_trace();
  return 0;
}