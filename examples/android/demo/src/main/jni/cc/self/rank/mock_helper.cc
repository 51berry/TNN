//
// Created by berry on 2021/7/27.
//

#include "mock_helper.h"
#include <tnn/core/macro.h>
#include <istream>
#include <iostream>
#include "nlohmann/json.hpp"
#include <type_traits>

using json = nlohmann::json;
namespace TNN_NS {

std::map<std::string, std::shared_ptr<DimsVectorFloat>> MockDataManager::GetMockInputData(std::string mock_input_path) {
  json inputJson;
  std::ifstream jfile(mock_input_path);
  jfile >> inputJson;
  std::map<std::string, std::shared_ptr<DimsVectorFloat>> result = {};
  for (auto cur = inputJson.begin(); cur != inputJson.end(); cur++) {
    std::string key = cur.key();
    json val = cur.value();
    auto dimsData = std::make_shared<std::vector<float>>();
    for (auto cur2 = val.begin(); cur2 != val.end(); cur2++) {
      float v = cur2.value();
      dimsData->push_back(v);
    }
    result[key] = dimsData;
    LOGI("\r\nGetMockInputData, name:%s, dims.size:%d", key.c_str(), dimsData->size());
  }
  LOGI("\r\nGetMockInputData, result.size:%d", result.size());
  return result;
}

}
