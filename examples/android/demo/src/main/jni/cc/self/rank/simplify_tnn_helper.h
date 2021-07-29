//
// Created by berry on 2021/7/19.
//

#ifndef ANDROID_SIMPLIFY_TNN_HELPER_H
#define ANDROID_SIMPLIFY_TNN_HELPER_H

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
#include "anchor_parser.h"
#include "mock_helper.h"

namespace TNN_NS {

class SimplifyTnnHelper {
 public:
  Status Init(std::string model_path, std::string proto_path, std::string anchor_path, std::string mockInput_path);
  TNN_NS::Status InitNet(std::string model_content, std::string proto_content);
  TNN_NS::Status InitInstance(InputShapesMap inputShapes);
  std::vector<std::string> GetInputNames();
  Status SetInputMat(InputShapesMap inputShapes,
                                        std::map<std::string, std::shared_ptr<DimsVectorFloat>> outDatas);
  InputShapesMap GetInputShapes(std::string anchor_path, std::shared_ptr<TNN_NS::AnchorParser> &anchorParser);
  virtual std::shared_ptr<Mat> ProcessSDKInputMat(std::shared_ptr<Mat> mat,
                                                  std::string name = kTNNSDKDefaultName);
  Status ProcessSDKOutput(std::shared_ptr<TNNSDKOutput> output_);
  TNN_NS::Status GetReorderOutput(std::shared_ptr<TNNSDKOutput> &output);
  std::vector<std::string> GetOutputNames();
  std::shared_ptr<TNNSDKOutput> CreateSDKOutput();
  std::vector<float> getScores(std::shared_ptr<TNNSDKOutput>);
  std::map<std::string, std::shared_ptr<DimsVectorFloat>> BuildInputData(std::string mockInputPath);


 private:
  std::shared_ptr<TNN_NS::AnchorParser> anchorParser_;
  std::shared_ptr<TNN_NS::MockDataManager> mockDataManager_;
  std::shared_ptr<TNN> net_             = nullptr;
  std::shared_ptr<Instance> instance_   = nullptr;
  DeviceType device_type_               = DEVICE_NAIVE;
};

}

#endif //ANDROID_SIMPLIFY_TNN_HELPER_H
