#include "raw_file_reader.hh"

int read_trace(std::string fileName, std::vector<TraceData> *vTraceData) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cerr << "[ERROR]\tFile open error" << std::endl;
    std::terminate();
  }

  std::string line;
  TraceData td;

  std::smatch match;
  std::regex regexTrace("([0-9]+)\\.([0-9]+) ([a-zA-Z]+) ([0-9]+) ([0-9]+)");

  while (std::getline(file, line)) {
    if (!std::regex_match(line, match, regexTrace)) {
      std::cerr << "[ERROR]\tRegex-match error" << std::endl;
    }
    td.sec = strtoul(match[1].str().c_str(), nullptr, 10);
    td.usec = strtoul(match[2].str().c_str(), nullptr, 10);
    td.isRead = (match[3].str() == std::string("DiskRead")) ? true : false;
    td.sLBA = strtoull(match[4].str().c_str(), nullptr, 10);
    td.nLB = strtoul(match[5].str().c_str(), nullptr, 10);
    vTraceData->push_back(std::move(td));
  }

  // Sort the array, just in case
  std::sort(vTraceData->begin(), vTraceData->end());

  // Assing an unique id
  uint32_t count = 0;
  for (auto iter = vTraceData->begin(); iter < vTraceData->end(); iter++) {
    iter->id = count++;
  }

  file.close();
  return 0;
}