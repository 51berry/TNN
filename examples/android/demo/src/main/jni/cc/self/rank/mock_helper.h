//
// Created by berry on 2021/7/27.
//

#ifndef ANDROID_MOCK_HELPER_H
#define ANDROID_MOCK_HELPER_H
#include "tnn_sdk_sample.h"
#include "macro.h"
#include <cmath>
#include <fstream>
#include <cstring>
#include <time.h>
#include <cmath>
#include <fstream>
#include <cstring>
#include <time.h>
#include "helper_jni.h"

namespace TNN_NS {

class MockDataManager {
 public:
  std::map<std::string, std::shared_ptr<std::vector<float>>> GetMockInputData(std::string mock_input_path);

};
}


#endif //ANDROID_MOCK_HELPER_H
