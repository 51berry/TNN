//
// Created by berry on 2021/7/21.
//

#ifndef ANDROID_ANCHOR_PARSER_H
#define ANDROID_ANCHOR_PARSER_H

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

class AnchorParser {
 public:
  std::map<std::string, DimsVector> parser(std::string anchor_file_path);
  std::string readfile(const char *filename);
};

}
#endif //ANDROID_ANCHOR_PARSER_H
