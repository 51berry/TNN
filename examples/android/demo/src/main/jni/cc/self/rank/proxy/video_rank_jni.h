//
// Created by berry on 2021/7/19.
//

#ifndef ANDROID_VIDEO_RANK_JNI_H
#define ANDROID_VIDEO_RANK_JNI_H

#include "../../../../../../../../../../../../../../Library/Android/sdk/ndk/21.0.6113669/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"

extern "C" {

JNIEXPORT jint JNICALL Java_com_tencent_tnn_demo_rank_VideoRank_init
    (JNIEnv *, jobject, jstring, jstring, jstring, jstring);

/*
 * Class:     com_tencent_tnn_demo_rank_VideoRank
 * Method:    deinit
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_tencent_tnn_demo_rank_VideoRank_deinit
    (JNIEnv *, jobject);
};

#endif //ANDROID_VIDEO_RANK_JNI_H
