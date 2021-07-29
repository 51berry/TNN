//
// Created by berry on 2021/7/21.
//

#include "anchor_parser.h"
#include <tnn/core/macro.h>
#include <istream>
#include <iostream>
#include "nlohmann/json.hpp"
#include <type_traits>

using json = nlohmann::json;
using namespace std;

namespace TNN_NS {
InputShapesMap AnchorParser::parser(std::string anchor_file_path) {
    json inputJson;
    ifstream jfile(anchor_file_path);
    jfile >> inputJson;

    InputShapesMap result = {};
    for (auto cur = inputJson.begin(); cur != inputJson.end(); cur++) {
      string key = cur.key();
      json val = cur.value();
      int dim1 = val.at("dim1");
      int dim2 = val.at("dim2");
      std::vector<int> nc = {dim1, dim2};
      result.insert(std::pair<std::string, TNN_NS::DimsVector>(key, nc));
    }

    return result;
  }

string AnchorParser::readfile(const char *filename){
  FILE *fp = fopen(filename, "rb");
  if(!fp){
    printf("open failed! file: %s", filename);
    return "";
  }

  char *buf = new char[1024*16];
  int n = fread(buf, 1, 1024*16, fp);
  fclose(fp);

  string result;
  if(n>=0){
    result.append(buf, 0, n);
  }
  delete []buf;
  return result;
}

}
