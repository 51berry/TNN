package com.tencent.tnn.demo.rank;

public class VideoRank {

    static {
        System.loadLibrary("tnn_wrapper");
    }

    public native int init(String modelAbsolutePath, String protoAbsolutePath, String anchorAbsolutePath, String mockInputAbsolutePath);

    public native int deinit();

}
