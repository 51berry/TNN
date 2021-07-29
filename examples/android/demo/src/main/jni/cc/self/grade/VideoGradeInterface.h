//
// Created by berry on 2021/4/8.
//

#ifndef ANDROID_VIDEOGRADEINTERFACE_H
#define ANDROID_VIDEOGRADEINTERFACE_H

#include "tnn_sdk_sample.h"
#include "algorithm"
#include "iostream"
#include "string"
#include "memory"
#include "vector"

namespace TNN_NS {

typedef ObjectInfo BlazeFaceInfo;

class VideoGradeInput : public TNNSDKInput {
 public:
  VideoGradeInput(std::shared_ptr<Mat> mat = nullptr) : TNNSDKInput(mat) {};
  virtual ~VideoGradeInput(){}
};

class VideoGradeOutput : public TNNSDKOutput {
 public:
  VideoGradeOutput(std::shared_ptr<Mat> mat = nullptr) : TNNSDKOutput(mat) {};
  virtual ~VideoGradeOutput() {};
  std::vector<BlazeFaceInfo> face_list;
};

class VideoGradeOption : public TNNSDKOption {

 public:
  VideoGradeOption() {}
  virtual ~VideoGradeOption() {}
  int param1;
  int param2;
  int param3;
  int input_width;
  int input_height;
  int num_thread = 1;
  float min_score_threshold = 0.75;
  float min_suppression_threshold = 0.3;
  std::string anchor_path;
};

class VideoGradeImpl : public TNNSDKSample {
 public:
  virtual ~VideoGradeImpl() {};

  virtual Status Init(std::shared_ptr<TNNSDKOption> option);
  virtual MatConvertParam GetConvertParamForInput(std::string name = "");
  virtual std::shared_ptr<TNNSDKOutput> CreateSDKOutput();
  virtual Status ProcessSDKOutput(std::shared_ptr<TNNSDKOutput> output);
  virtual std::shared_ptr<Mat> ProcessSDKInputMat(std::shared_ptr<Mat> mat,
                                                  std::string name = kTNNSDKDefaultName);

 private:
  void GenerateBBox(std::vector<BlazeFaceInfo> &detects, Mat &scores, Mat &boxes,
                    int image_w, int image_h, float min_score_threshold);
  void BlendingNMS(std::vector<BlazeFaceInfo> &input, std::vector<BlazeFaceInfo> &output,
                   float min_suppression_threshold);

  std::vector<float> anchors;

  int num_anchors = 896;
  int detect_dims = 16;
  int num_keypoints = 6;
};

}

#endif //ANDROID_VIDEOGRADEINTERFACE_H
