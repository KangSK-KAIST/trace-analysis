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

/**
 * @brief Counts the number of requests around (+-20 us) each read
 *
 * @param vTraceData (pointer) vector of trace data
 *
 * @note The purpose of this analytics is to numerize the best-case boost of
 * performance. 20us was selected because it is the currently fastest NAND's
 * latency, and therefore we can safely assume that requests around +- 20us of
 * some request will be handled together. The total number of requests is the
 * maximum parallelism we can get, while the poorest case is when all of them
 * are stalled on each other.
 */
static void analyzeTrace(std::vector<TraceData>* vTraceData) {
  std::vector<int64_t> parallelCount;
  for (auto trace : *vTraceData) {
    // If write, pass
    if (!trace.isRead) continue;
    // Is a read, count all requests within 20us
    int64_t count = 0;
    for (auto cmpTrace : *vTraceData)
      // TODO Use better algorithm here
      // Ignoring second-level comparison (may overflow)
      if ((trace.sec == cmpTrace.sec) &&
          (std::abs((long long)trace.psec - (long long)cmpTrace.psec) <=
           (long long)20000000)) {
        count++;
      }
    parallelCount.push_back(count);
  }
  std::cout << "[TraceParallel]" << std::endl;
  std::cout << (double)std::accumulate(parallelCount.begin(),
                                       parallelCount.end(), (uint64_t)0) /
                   (double)parallelCount.size()
            << std::endl;
}

static void analyzeWindow(std::vector<TraceData>* vWindow,
                          std::vector<int32_t>* chunks) {
  int64_t prevPage = -1;
  int32_t index = 0;
  for (auto trace : *vWindow) {
    if ((trace.sLBA / PAGE_SIZE != prevPage) &&
        (trace.sLBA / PAGE_SIZE != prevPage + 1)) {
      // A new sequencial block starts
      chunks->push_back(index);
    } else {
#ifdef LOGGING
      std::cerr << "[LOG]\tSequential !" << std::endl;
#endif
    }
    prevPage = (trace.sLBA + trace.nLB) / PAGE_SIZE;
    index++;
  }
}

static void analyzeTraceSeq(std::vector<TraceData>* vTraceData,
                            std::map<id_t, std::set<id_t>>* mReadCentric) {
  // Parameters to solve
  int64_t logicalRand = 0;
  int64_t logicalSeq = 0;
  int64_t physicalSeq = 0;
  int64_t logicalRandSize = 0;
  int64_t logicalSeqSize = 0;
  int64_t physicalSeqSize = 0;

  // Each physical sequential block sizes
  std::vector<int64_t> lgSeqBlockSize;
  std::vector<int64_t> phySeqBlockSize;

  // Loop through all traces
  for (auto iter = vTraceData->begin(); iter < vTraceData->end(); iter++) {
    if (!iter->isRead) continue;
    std::vector<TraceData> window;
    // Time of first read in the time window
    int64_t startTime = iter->sec * (uint64_t)1000000000000 + iter->psec;
    // Loop for 20 us
    while ((iter < vTraceData->end()) &&
           (iter->sec * (uint64_t)1000000000000 + iter->psec <
            startTime + (uint64_t)20000000)) {
      if (!(iter->isRead)) {
        iter++;
      } else {
        window.push_back(*iter);
        iter++;
      }
    }
    std::vector<int32_t> chunks;
    analyzeWindow(&window, &chunks);

    // Now we have all index of sequential starts
    int32_t prev = 0;
    for (auto id : chunks) {
      if (id == 0) continue;
      if (id == prev + 1) {  // The request was random
        logicalRand++;
        logicalRandSize += window[prev].nLB;
        prev = id;
      } else {
        // It is logically sequential; is it physically too?
        bool isPhySeq = true;
        // Temporary sequential size
        int64_t lgSeq = 0;
        int64_t lgSeqSize = 0;
        int64_t phySeq = 0;
        int64_t phySeqSize = 0;
        // Loop through seqential blocks
        for (int32_t i = prev; i < id; i++) {
          lgSeq++;
          lgSeqSize += window[i].nLB;
          phySeq++;
          phySeqSize += window[i].nLB;
          if ((*mReadCentric)[window[i].id].size() > 1) {
            isPhySeq = false;
            phySeqBlockSize.push_back(phySeqSize);
            phySeq = 0;
            phySeqSize = 0;
          }
        }
        if (isPhySeq) {
          physicalSeq += phySeq;
          physicalSeqSize += phySeqSize;
        }
        logicalSeqSize += lgSeq;
        logicalSeqSize += lgSeqSize;
        lgSeqBlockSize.push_back(lgSeqSize);
      }
    }
  }
  // Print result
  std::cout << "[Sequential]" << std::endl;
  std::cout << logicalRand << "\t" << logicalRandSize << "\t" << logicalSeq
            << "\t" << logicalSeqSize << "\t" << physicalSeq << "\t"
            << physicalSeqSize << std::endl;

  std::cout << "[Sequential BD]" << std::endl;
  std::cout << (double)std::accumulate(lgSeqBlockSize.begin(),
                                       lgSeqBlockSize.end(), (int64_t)0) /
                   (double)lgSeqBlockSize.size()
            << "\t"
            << (double)std::accumulate(phySeqBlockSize.begin(),
                                       phySeqBlockSize.end(), (int64_t)0) /
                   (double)phySeqBlockSize.size()
            << std::endl;
}

/**
 * @brief Counts number of each occurences; indep/single/multi
 *
 * @param vTraceData (pointer) vector of trace data
 * @param mCentric (pointer) map of read or write centric
 * @param isRead whether to analyze read or write traces
 * @param indep (pointer) number of independent traces
 * @param depShort (pointer) number of single dependent traces
 * @param depLong (pointer) number of multiple dependent traces
 *
 * @note Independent traces are read/write traces that are reading/writing
 * from addresses never written/read by others. Single dependent traces are
 * read/write traces thar are reading/writing from addresses (written by
 * one)/(read once) by others. Multiple dependent traces are read/write
 * traces thar are reading/writing from addresses (written by
 * multiple)/(read multiple times) multiply by others, where written
 * multiply means it is reading from a segmented range of address, not
 * meaning hotspot.
 */
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

/**
 * @brief Counts total bytes of each occurences; indep/single/multi
 *
 * @param vTraceData (pointer) vector of trace data
 * @param mCentric (pointer) map of read or write centric
 * @param isRead whether to analyze read or write traces
 * @param indep (pointer) size of independent traces
 * @param depShort (pointer) size of single dependent traces
 * @param depLong (pointer) size of multiple dependent traces
 *
 * @note Independent traces are read/write traces that are reading/writing
 * from addresses never written/read by others. Single dependent traces are
 * read/write traces thar are reading/writing from addresses (written by
 * one)/(read once) by others. Multiple dependent traces are read/write traces
 * that are reading/writing from addresses (written by multiple)/(read
 * multiple times) multiply by others, where written multiply means it is
 * reading from a segmented range of address, not meaning hotspot.
 */
static void analyzeDependTypeSize(std::vector<TraceData>* vTraceData,
                                  std::map<id_t, std::set<id_t>>* mCentric,
                                  bool isRead, int64_t* indep,
                                  int64_t* depShort, int64_t* depLong) {
  for (auto trace : (*vTraceData)) {
    if (trace.isRead == isRead) {
      if (mCentric->count(trace.id)) {
        // Exists a corresponding write
        if ((*mCentric)[trace.id].size() > 1)
          (*depLong) += trace.nLB;
        else
          (*depShort) += trace.nLB;
      } else
        (*indep) += trace.nLB;
    }
  }
}

/**
 * @brief Counts all hot writes in page-level
 *
 * @param vTraceData (pointer) vector of traces
 * @param mWriteCentric (pointer) write centric map
 *
 * @note Hot writes means the data written by the write was read by other
 * reads. The function iterates through all hot writes and the pages they
 * wrote, and count the number of occurances of which the data was read by
 * another request. This is done in a page-specific manner, which hereby
 * results in the number of reads each pages experience before overwritten.
 */
static void analyzeHotWritePage(std::vector<TraceData>* vTraceData,
                                std::map<id_t, std::set<id_t>>* mWriteCentric) {
  std::vector<uint32_t> readCountsTotal;
  for (auto write : *mWriteCentric) {
    // Iterate for all writes that are read at least once
    // Read basic parameters
    int64_t pageStart = (*vTraceData)[write.first].sLBA / PAGE_SIZE;
    int64_t pageEnd =
        ((*vTraceData)[write.first].sLBA + (*vTraceData)[write.first].nLB) /
        PAGE_SIZE;
    int64_t pageNum = pageEnd - pageStart + 1;

    // Simulate a small segemnt of memory as page array
    int32_t* readCounts = new int32_t[pageNum];
    for (int i = 0; i < pageNum; i++) {
      readCounts[i] = 0;
    }

    // Iterate for all reads that read the pages
    for (auto read : write.second) {
      int64_t readStartReal = (*vTraceData)[read].sLBA / PAGE_SIZE;
      int64_t readEndReal =
          ((*vTraceData)[read].sLBA + (*vTraceData)[read].nLB) / PAGE_SIZE;
      // Read might start earilier, end later than write
      int64_t readStartOverlap = std::max(pageStart, readStartReal);
      int64_t readEndOverlap = std::min(pageEnd, readEndReal);
      // Calculate offset of read request in page count
      int64_t readOffset = readStartOverlap - pageStart;
      int64_t readNum = readEndOverlap - readStartOverlap + 1;
      // Iterate for overlapping pages
      for (int i = 0; i < readNum; i++) {
        readCounts[readOffset + i]++;
      }
    }
    // Finished simulation; append to total vector
    for (int i = 0; i < pageNum; i++) {
      readCountsTotal.push_back(readCounts[i]);
    }
    delete[] readCounts;
  }
  // Count each numbers for better reading
  std::map<int32_t, int64_t> countDuplicate;
  std::for_each(readCountsTotal.begin(), readCountsTotal.end(),
                [&countDuplicate](int val) { countDuplicate[val]++; });

  // Finished all analysis; print data
  std::cout << "[HotWritePage]" << std::endl;
  for (auto hot : countDuplicate) {
    std::cout << hot.first << "\t";
  }
  std::cout << std::endl;
  for (auto hot : countDuplicate) {
    std::cout << hot.second << "\t";
  }
  std::cout << std::endl;

  // Print average value for graph
  int64_t countTotal = 0;
  int64_t readTotal = 0;
  for (auto dup : countDuplicate) {
    countTotal += dup.second;
    readTotal += dup.first * dup.second;
  }
  double averageRead = (double)readTotal / (double)countTotal;
  std::cout << averageRead << std::endl;
}

/**
 * @brief Counts all hot writes in request-level
 *
 * @param vTraceData (pointer) vector of traces
 * @param mWriteCentric (pointer) write centric map
 *
 * @note Hot writes means the data written by the write was read by other
 * reads. The function iterates through all hot writes and counts the number
 * of read requests per write requests.
 */
static void analyzeHotWriteRequest(
    std::vector<TraceData>* vTraceData,
    std::map<id_t, std::set<id_t>>* mWriteCentric) {
  std::vector<uint32_t> readCountsTotal;
  for (auto write : *mWriteCentric) {
    // Iterate for all writes that are read at least once
    readCountsTotal.push_back(write.second.size());
  }
  // Count each numbers for better reading
  std::map<int32_t, int64_t> countDuplicate;
  std::for_each(readCountsTotal.begin(), readCountsTotal.end(),
                [&countDuplicate](int val) { countDuplicate[val]++; });

  // Finished all analysis; print data
  std::cout << "[HotWriteRequest]" << std::endl;
  for (auto hot : countDuplicate) {
    std::cout << hot.first << "\t";
  }
  std::cout << std::endl;
  for (auto hot : countDuplicate) {
    std::cout << hot.second << "\t";
  }
  std::cout << std::endl;

  // Print average value for graph
  int64_t countTotal = 0;
  int64_t readTotal = 0;
  for (auto dup : countDuplicate) {
    countTotal += dup.second;
    readTotal += dup.first * dup.second;
  }
  double averageRead = (double)readTotal / (double)countTotal;
  std::cout << averageRead << std::endl;
}

void analyze(std::vector<TraceData>* vTraceData, int64_t pageNum,
             std::map<id_t, std::set<id_t>>* mReadCentric,
             std::map<id_t, std::set<id_t>>* mWriteCentric) {
  // Trace parallelism
  // analyzeTrace(vTraceData);
  analyzeTraceSeq(vTraceData, mReadCentric);

  // Read breakdown
  int32_t indepReads = 0;     // Reads without correspoding writes
  int32_t depShortReads = 0;  // Reads connected to one write
  int32_t depLongReads = 0;   // Reads with multiple corresponding writes
  analyzeDependTypes(vTraceData, mReadCentric, true, &indepReads,
                     &depShortReads, &depLongReads);
  std::cout << "[Read BD (#)]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << indepReads << "\t" << depShortReads << "\t" << depLongReads
            << std::endl;

  // Read breakdown, in size
  int64_t indepReadSize = 0;     // Reads without correspoding writes
  int64_t depShortReadSize = 0;  // Reads connected to one write
  int64_t depLongReadSize = 0;   // Reads with multiple corresponding writes
  analyzeDependTypeSize(vTraceData, mReadCentric, true, &indepReadSize,
                        &depShortReadSize, &depLongReadSize);
  std::cout << "[Read BD (Bytes)]\tIndependent\tDep_Short\tDep_Long"
            << std::endl;
  std::cout << indepReadSize << "\t" << depShortReadSize << "\t"
            << depLongReadSize << std::endl;

  // Write breakdown
  int32_t indepWrites = 0;     // Writes without correspoding writes
  int32_t depShortWrites = 0;  // Writes connected to one write
  int32_t depLongWrites = 0;   // Writes with multiple corresponding writes
  analyzeDependTypes(vTraceData, mWriteCentric, false, &indepWrites,
                     &depShortWrites, &depLongWrites);
  std::cout << "[Write BD (#)]\tIndependent\tDep_Short\tDep_Long" << std::endl;
  std::cout << indepWrites << "\t" << depShortWrites << "\t" << depLongWrites
            << std::endl;

  // Write breakdown, in size
  int64_t indepWriteSize = 0;     // Writes without correspoding writes
  int64_t depShortWriteSize = 0;  // Writes connected to one write
  int64_t depLongWriteSize = 0;   // Writes with multiple corresponding writes
  analyzeDependTypeSize(vTraceData, mWriteCentric, false, &indepWriteSize,
                        &depShortWriteSize, &depLongWriteSize);
  std::cout << "[Write BD (Bytes)]\tIndependent\tDep_Short\tDep_Long"
            << std::endl;
  std::cout << indepWriteSize << "\t" << depShortWriteSize << "\t"
            << depLongWriteSize << std::endl;

  analyzeHotWritePage(vTraceData, mWriteCentric);
  analyzeHotWriteRequest(vTraceData, mWriteCentric);
}