//
// Created by berry on 2021/7/19.
//


#include "video_rank_jni.h"
#include <jni.h>
#include <macro.h>
#include "tnn_sdk_sample.h"
#include "helper_jni.h"
#include "self/rank/simplify_tnn_helper.h"

static int gComputeUnitType = TNN_NS::TNNComputeUnitsCPU;
static std::shared_ptr<TNN_NS::SimplifyTnnHelper> simplifyTnnHelper;

extern "C" {

JNIEXPORT jint JNICALL Java_com_tencent_tnn_demo_rank_VideoRank_init
    (JNIEnv *env, jobject thiz,
     jstring j_modelAbsolutePath,
     jstring j_protoAbsolutePath,
     jstring anchorAbsolutePath,
     jstring mockInputAbsolutePath) {

  std::string model_path;
  std::string proto_path;
  std::string anchor_path;
  std::string mockInput_path;

  model_path = jstring2string(env, j_modelAbsolutePath);
  proto_path = jstring2string(env, j_protoAbsolutePath);
  anchor_path = jstring2string(env, anchorAbsolutePath);
  mockInput_path = jstring2string(env, mockInputAbsolutePath);

  simplifyTnnHelper = std::make_shared<TNN_NS::SimplifyTnnHelper>();

  TNN_NS::Status status = simplifyTnnHelper->Init(model_path, proto_path, anchor_path, mockInput_path);

  if (status != TNN_NS::TNN_OK) {
    return -1;
  }
  return 0;
}

/*
 * Class:     com_tencent_tnn_demo_rank_VideoRank
 * Method:    deinit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_tencent_tnn_demo_rank_VideoRank_deinit
    (JNIEnv *, jobject) {
  return -1;
}

}