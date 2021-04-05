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

#include "general_reader.hh"

std::smatch match;
std::regex regexTrace(
    "[0-9]+,([a-zA-Z]+),([0-9]+),([0-9]+),([0-9]{4})([0-9]+)");

/**
 * @brief Scan through trace and read min/max page no.
 *
 * @param fileName path of the trace file
 * @param pageMin (pointer) minimun page number
 * @param pageMax (pointer) maximum page number
 */
void scanTrace(std::string fileName, int64_t *pageMin, int64_t *pageMax) {
#ifdef LOGGING
  std::cerr << "[LOG]\tScanning File..." << std::endl;
#endif
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "[ERROR]\tFile open error" << std::endl;
    std::terminate();
  }

  int64_t totalBytes = 0;
  std::string line;
  while (std::getline(file, line)) {
    if (!std::regex_match(line, match, regexTrace)) {
      std::cerr << "[ERROR]\tRegex-match error" << std::endl;
      std::terminate();
    }
    int64_t addr = strtoull(match[4].str().c_str(), nullptr, 10);
    int64_t size = strtoul(match[5].str().c_str(), nullptr, 10);
    int64_t pageStart = addr / PAGE_SIZE;
    int64_t pageEnd = (addr + size) / PAGE_SIZE;
    *pageMin = (*pageMin > pageStart) ? pageStart : *pageMin;
    *pageMax = (*pageMax < pageEnd) ? pageEnd : *pageMax;

    totalBytes += size;
  }
#ifdef LOGGGING
  std::cerr << "[LOG]\tTotal " << totalBytes << " bytes in trace." << std::endl;
#endif
  std::cout << "Total transfer size in bytes\t" << totalBytes << std::endl;
  file.close();
}

void printStat(std::string fileName) {
#ifdef LOGGING
  std::cerr << "[LOG]\tPrinting File Stat..." << std::endl;
#endif
  std::cout << "FileName:\t" << fileName << std::endl;
}

void readTrace(std::string fileName, std::vector<TraceData> *vTraceData,
               int32_t size) {
#ifdef LOGGING
  std::cerr << "[LOG]\tReading File..." << std::endl;
#endif
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "[ERROR]\tFile open error" << std::endl;
    std::terminate();
  }

  std::string line;
  TraceData td;

  bool isFullRead = (size == 0);
  int64_t bytesToRead = (uint64_t)size * 1024 * 1024;  // size * 1024 * 1024

  std::smatch match;
  std::regex regexTrace(
      "[0-9]+,([a-zA-Z]+),([0-9]+),([0-9]+),([0-9]{4})([0-9]+)");

  while (std::getline(file, line)) {
    if (!std::regex_match(line, match, regexTrace)) {
      std::cerr << "[ERROR]\tRegex-match error" << std::endl;
      std::terminate();
    }
    td.isRead = (match[1].str() == std::string("R")) ? true : false;
    td.sLBA = strtoull(match[2].str().c_str(), nullptr, 10);
    td.nLB = strtoul(match[3].str().c_str(), nullptr, 10);
    td.sec = strtoul(match[4].str().c_str(), nullptr, 10);
    td.psec = strtoull(match[5].str().c_str(), nullptr, 10);
    if (!isFullRead) {
      if (bytesToRead < (uint64_t)td.nLB) break;
      bytesToRead -= (uint64_t)td.nLB;
    }
    vTraceData->push_back(std::move(td));
  }

  // Sort the array, just in case
  std::sort(vTraceData->begin(), vTraceData->end());

  // Assign an unique id
  uint32_t count = 0;
  for (auto iter = vTraceData->begin(); iter < vTraceData->end(); iter++) {
    iter->id = count++;
  }

  file.close();
}