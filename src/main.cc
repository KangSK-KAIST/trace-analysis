#include "includes/include.hh"
#include "includes/types.hh"
#include "parser/snia_parser.hh"
#include "reader/raw_file_reader.hh"

int main() {
  // std::string fileName(
  //     "/home/kangsk/gitrepo/trace-analysis/snia_refined/MSEnterprise/"
  //     "Enterprise1.total.csv.orig");
  std::string fileName(
      "/home/kangsk/gitrepo/trace-analysis/Enterprise1.total.csv.simple");
  std::vector<TraceData> vTraceData;
  read_trace(fileName, &vTraceData);

  // Debug code
  int count = 0;
  for (auto iter = vTraceData.begin();; iter++) {
    std::cout << iter->id << " " << iter->usec << " " << iter->sLBA
              << std::endl;
    if (count++ > 20) break;
  }
  parse_trace();
  // save_pickle();
  // analyze_trace();
  return 0;
}