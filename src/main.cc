#include "includes/include.hh"
#include "includes/types.hh"
#include "parser/snia_parser.hh"
#include "reader/raw_file_reader.hh"

int main() {
  std::string fileName(
      "/home/kangsk/gitrepo/trace-analysis/snia_refined/MSEnterprise/"
      "Enterprise1.total.csv.orig");
  std::vector<TraceData> vTraceData;
  read_trace(fileName, &vTraceData);
  for (int i = 0; i < 10; i++) {
    std::cout << vTraceData[i].sec << " " << vTraceData[i].usec << " "
              << vTraceData[i].sLBA << " " << vTraceData[i].nLB << " "
              << vTraceData[i].isRead << std::endl;
  }
  // parse_trace();
  // group_trace();
  // save_pickle();
  // analyze_trace();
  return 0;
}