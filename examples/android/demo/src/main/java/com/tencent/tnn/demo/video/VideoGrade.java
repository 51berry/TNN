package com.tencent.tnn.demo.video;

public class VideoGrade {

    static {
        System.loadLibrary("tnn_wrapper");
    }

    public native int initTNN(String modelAbsolutePath, String protoAbsolutePath, int computUnitType);

    public native int deinit();

}
