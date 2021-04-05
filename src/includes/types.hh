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

#ifndef __INCLUDES_TYPES_HH_
#define __INCLUDES_TYPES_HH_

#include "include.hh"

struct TraceData {
  uint32_t id;    // id used for key; given after sorting
  uint32_t sec;   // second of request
  uint64_t psec;  // microsecond of requset
  uint64_t sLBA;  // address of request
  uint32_t nLB;   // length of request
  bool isRead;    // whether request is read/write

  friend bool operator<(TraceData const& a1, TraceData const& a2) {
    if (a1.sec != a2.sec) {
      return a1.sec < a2.sec;
    }
    if (a1.psec != a2.psec) {
      return a1.psec < a2.psec;
    }
    if (a1.sLBA != a2.sLBA) {
      return a1.sLBA < a2.sLBA;
    }
    if (a1.nLB != a2.nLB) {
      return a1.nLB < a2.nLB;
    }
    return false;
  }

  friend bool operator==(TraceData const& a1, TraceData const& a2) {
    return ((a1.sec == a2.sec) && (a1.psec == a2.psec) &&
            (a1.sLBA == a2.sLBA) && (a1.nLB == a2.nLB));
  }
};

typedef uint32_t id_t;
typedef uint64_t page_t;

#endif  // __INCLUDES_TYPES_HH_