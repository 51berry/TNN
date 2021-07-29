//
// Created by berry on 2021/7/19.
//

#include "simplify_tnn_helper.h"
#include "anchor_parser.h"

namespace TNN_NS {
using namespace std;
Status SimplifyTnnHelper::Init(std::string model_path, std::string proto_path, std::string anchor_path, std::string mockInputPath) {

  LOGI("\r\nmodel_path:%s, proto_path:%s", model_path.c_str(), proto_path.c_str());

  TNN_NS::Status status = InitNet(model_path, proto_path);
  if (status != TNN_NS::TNN_OK) {
    return status;
  }

  InputShapesMap inputShapes = GetInputShapes(anchor_path, anchorParser_);
  if (inputShapes.size() <= 0) {
    LOGE("inputshape empty");
    return TNN_NS::Status(-1, "inputshape empty");
  }

  status = InitInstance(inputShapes);
  if (status != TNN_NS::TNN_OK) {
    LOGE("init network failed, code:%d, reason:%s", (int)status, status.description().c_str());
    return -1;
  }

  std::map<std::string, std::shared_ptr<DimsVectorFloat>> inputDatas = BuildInputData(mockInputPath);
  if (inputDatas.size() <= 0 || inputDatas.size() != inputShapes.size()) {
    LOGE("init mock data failed, mockDatas.size:%d", inputDatas.size());
    return -1;
  }

  status = SetInputMat(inputShapes, inputDatas);
  if (status != TNN_NS::TNN_OK) {
    LOGE("set input failed, reason:%s", status.description().c_str());
    return -1;
  }

  status = instance_->ForwardAsync(nullptr);
  if (status != TNN_NS::TNN_OK) {
    LOGE("instance.Forward Error: %s\n", status.description().c_str());
    return status;
  }

  std::shared_ptr<TNN_NS::TNNSDKOutput> output = CreateSDKOutput();
  status = GetReorderOutput(output);
  status = ProcessSDKOutput(output);

  if (output->IsEmpty()) {
    LOGE("output.IsEmpty()");
  }

  if (status != TNN_NS::TNN_OK) {
    LOGE("instance.Forward Error: %s\n", status.description().c_str());
    return status;
  }
  return 0;
}

/**
 * 供JNI层获取最后的运行结果
 * @return
 */
std::vector<float> SimplifyTnnHelper::getScores(std::shared_ptr<TNNSDKOutput>) {
  return {};
}

/**
 * 从outpub 中获取我们需要的数据，并记录到output的成员变量中
 * @param output_
 * @return
 */
TNN_NS::Status SimplifyTnnHelper::ProcessSDKOutput(std::shared_ptr<TNNSDKOutput> output_) {

  auto output = output_.get();
  auto scores = output->GetMat("pred");
  RETURN_VALUE_ON_NEQ(!scores, false,
                      Status(TNNERR_PARAM_ERR, "scores mat is nil"));

  DimsVector dims = scores->GetDims();
  if (dims.size() <= 0) {
    return Status(-1, "ProcessSDKOutput, dims.size:%d" + dims.size());
  }
  int size = 1;
  for (int i=0; i < dims.size(); i++) {
    size = dims[i] * size;
  }

  float *score_data = static_cast<float*>(scores->GetData());

  if (score_data == nullptr) {
    return Status(-1, "score_data is null");
  }

  for (int i=0; i < size; i++) {
    LOGI("\r\nscore_data[%d]:%f", i, score_data[i]);
  }

  return TNN_NS::TNN_OK;
}

std::vector<std::string> SimplifyTnnHelper::GetOutputNames() {
  std::vector<std::string> names;
  if (instance_) {
    BlobMap blob_map;
    instance_->GetAllOutputBlobs(blob_map);
    for (const auto& item : blob_map) {
      names.push_back(item.first);
    }
  }
  return names;
}

TNN_NS::Status SimplifyTnnHelper::SetInputMat(InputShapesMap inputShapes, std::map<std::string, std::shared_ptr<DimsVectorFloat>> outDatas) {
  std::vector<std::string> input_names = GetInputNames();
  if (input_names.size() <= 0) {
    return Status(-1, "input names is empty");
  }
  DimsVectorFloat* element = nullptr;
  DimsVectorFloat datas;
  for (std::string key : input_names) {
    std::string name = key;
    element = outDatas[name].get();
    datas = *element;
  //  LOGI("\r\nSetInputMat, name:%s, datas.size():%d, datas[0]:%f", name.c_str(), datas.size(), datas[0]);

    auto input_mat = std::make_shared<TNN_NS::Mat>(device_type_, TNN_NS::NCHW_FLOAT, inputShapes[key], element);
    input_mat = ProcessSDKInputMat(input_mat, key);
    MatConvertParam input_convert_param;
    auto status = instance_->SetInputMat(input_mat, input_convert_param, key);
    RETURN_ON_NEQ(status, TNN_NS::TNN_OK);
  }

  return Status(TNN_NS::TNN_OK, "set input mat suc");
}


TNN_NS::Status SimplifyTnnHelper::GetReorderOutput(std::shared_ptr<TNNSDKOutput> &output) {
  auto output_names = SimplifyTnnHelper::GetOutputNames();
  TNN_NS::Status status = TNN_NS::TNN_OK;
  for (auto name : output_names) {
    MatConvertParam output_convert_param;
    std::shared_ptr<TNN_NS::Mat> output_mat = nullptr;
    status = instance_->GetOutputMat(output_mat, output_convert_param, name,
                                     TNNSDKUtils::GetFallBackDeviceType(device_type_));
    RETURN_ON_NEQ(status, TNN_NS::TNN_OK);
    output->AddMat(output_mat, name);
  }
  return status;
}

std::shared_ptr<TNNSDKOutput> SimplifyTnnHelper::CreateSDKOutput() {
  return std::make_shared<TNNSDKOutput>();
}

/**
 * 构建一个map.size 大小的map。每个value 是一个 2.72 个元素，每个元素的数值范围是0～1 的浮点数
 * @param inputShapesMap
 * @return
 */
std::map<std::string, std::shared_ptr<DimsVectorFloat>> SimplifyTnnHelper::BuildInputData(std::string mockInputPath) {
  mockDataManager_ = std::make_shared<MockDataManager>();
  return mockDataManager_->GetMockInputData(mockInputPath);
}

std::shared_ptr<TNN_NS::Mat> SimplifyTnnHelper::ProcessSDKInputMat(std::shared_ptr<TNN_NS::Mat> mat,
                                                              std::string name) {
  return mat;
}

/**
 * step1 解析模型文件
 * @param model_path
 * @param proto_path
 * @return
 */
TNN_NS::Status SimplifyTnnHelper::InitNet(std::string model_path, std::string proto_path) {
  std::string model_content;
  std::string proto_content;

  model_content = fdLoadFile(model_path);
  proto_content = fdLoadFile(proto_path);
  LOGI("\r\nmodel_content:%s, proto_content:%s", model_content.c_str(), proto_content.c_str());

  TNN_NS::ModelConfig model_config;
  model_config.model_type = TNN_NS::MODEL_TYPE_TNN;
  model_config.params.push_back(proto_content);
  model_config.params.push_back(model_content);

  net_ = std::make_shared<TNN_NS::TNN>();
  TNN_NS::Status initStatus = net_->Init(model_config);

  if (initStatus != TNN_NS::TNN_OK) {
    LOGE("instance.net init failed %d, reason:%s", (int)initStatus, initStatus.description().c_str());
    return initStatus;
  }
  return TNN_NS::TNN_OK;
}

/**
 * 创建网络实例
 * @param inputShapes
 * @return
 */
TNN_NS::Status SimplifyTnnHelper::InitInstance(InputShapesMap inputShapes) {
  TNN_NS::NetworkConfig networkConfig;
  device_type_ = TNN_NS::DEVICE_NAIVE;
  networkConfig.device_type = TNN_NS::DEVICE_NAIVE;
  TNN_NS::Status status;
  instance_ = net_->CreateInst(networkConfig, status, inputShapes);
  if (status != TNN_NS::TNN_OK) {
    LOGE("init network failed, code:%d, reason:%s", (int)status, status.description().c_str());
    return status;
  }
  return TNN_NS::TNN_OK;
}

/**
 * 解析特征定义文件
 * @param anchor_path
 * @return
 */
InputShapesMap SimplifyTnnHelper::GetInputShapes(std::string anchor_path, std::shared_ptr<TNN_NS::AnchorParser> &anchorParser) {
  anchorParser = std::make_shared<TNN_NS::AnchorParser>();
  return anchorParser_->parser(anchor_path);
}

std::vector<std::string> SimplifyTnnHelper::GetInputNames() {
  std::vector<std::string> names;
  if (instance_) {
    BlobMap blob_map;
    instance_->GetAllInputBlobs(blob_map);
    for (const auto& item : blob_map) {
      names.push_back(item.first);
    }
  }
  return names;
}

}
