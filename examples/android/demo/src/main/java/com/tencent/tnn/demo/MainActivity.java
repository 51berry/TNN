package com.tencent.tnn.demo;


import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;

import com.tencent.tnn.demo.ImageBlazeFaceDetector.ImageBlazeFaceDetectActivity;
import com.tencent.tnn.demo.ImageClassifyDetector.ImageClassifyDetectActivity;
import com.tencent.tnn.demo.ImageFaceDetector.ImageFaceDetectActivity;
import com.tencent.tnn.demo.ImageObjectDetectorSSD.ImageObjectDetectSSDActivity;
import com.tencent.tnn.demo.ImageOCRDetector.ImageOCRDetectActivity;
import com.tencent.tnn.demo.StreamBlazeFaceAlign.StreamBlazeFaceAlignActivity;
import com.tencent.tnn.demo.StreamBlazeFaceDetector.StreamBlazeFaceDetectActivity;
import com.tencent.tnn.demo.StreamFaceDetector.StreamFaceDetectActivity;
import com.tencent.tnn.demo.ImageObjectDetector.ImageObjectDetectActivity;
import com.tencent.tnn.demo.StreamHairSegmentation.StreamHairSegmentationActivity;
import com.tencent.tnn.demo.StreamObjectDetector.StreamObjectDetectActivity;
import com.tencent.tnn.demo.StreamObjectDetectorSSD.StreamObjectDetectSSDActivity;
import com.tencent.tnn.demo.StreamPoseDetectLandmark.StreamPoseDetectLandmarkActivity;
import com.tencent.tnn.demo.StreamSkeletonDetector.StreamSkeletonDetectActivity;
import com.tencent.tnn.demo.rank.VideoRank;
import com.tencent.tnn.demo.video.VideoGrade;
import com.tencent.tnn.demo.StreamOCRDetector.StreamOCRDetectActivity;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.util.Iterator;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


public class MainActivity extends Activity {

    private TextView lightLiveCheckBtn;
    private VideoGrade videoGrade;
    private Context context;

    private boolean isShowedActivity = false;
    private VideoRank videoRank;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        context = this;
        init();

    }

    private void showToast(String title, String content) {
        AlertDialog.Builder alertdialogbuilder = new AlertDialog.Builder(context);
        alertdialogbuilder.setTitle(title);
        alertdialogbuilder.setMessage(String.format("运行结果=%s", content));
        alertdialogbuilder.setPositiveButton("确定", null);
        final AlertDialog alertdialog1 = alertdialogbuilder.create();
        alertdialog1.show();
    }

    private void init() {

        findViewById(R.id.tv_test).setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                videoGrade = new VideoGrade();
                int result = videoGrade.initTNN("123" , "456", 1);
                AlertDialog.Builder alertdialogbuilder = new AlertDialog.Builder(context);
                alertdialogbuilder.setTitle("推荐打分");
                alertdialogbuilder.setMessage(String.format("运行结果=%d", result));
                alertdialogbuilder.setPositiveButton("确定", null);
                final AlertDialog alertdialog1 = alertdialogbuilder.create();
                alertdialog1.show();
            }
        });

        findViewById(R.id.tv_test2).setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                videoRank = new VideoRank();
                File fileModel = new File(Environment.getExternalStorageDirectory() + "/model.tnnmodel");
                File fileProto = new File(Environment.getExternalStorageDirectory() + "/model.tnnproto");
                File fileAnchor = new File(Environment.getExternalStorageDirectory() + "/tnn_input.json");
                File mockInput = new File(Environment.getExternalStorageDirectory() + "/mock_input2.json");

                if (!fileModel.exists() || !fileProto.exists() || !fileAnchor.exists() || !mockInput.exists()) {
                    showToast("推荐重排列", "模型文件不存在");
                    return;
                }
                int result = videoRank.init(fileModel.getAbsolutePath(), fileProto.getPath(), fileAnchor.getPath(), mockInput.getPath());
                showToast("推荐重排列", String.valueOf(result));
            }
        });

        findViewById(R.id.stream_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamFaceDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });
        findViewById(R.id.image_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageFaceDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.image_classify_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageClassifyDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.image_object_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageObjectDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        /*
        findViewById(R.id.image_ocr_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageOCRDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });
        */

        findViewById(R.id.stream_object_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamObjectDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });
        findViewById(R.id.image_object_detectssd_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageObjectDetectSSDActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_object_detectssd_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamObjectDetectSSDActivity.class);
                    activity.startActivity(intent);
                }
            }
        });
        findViewById(R.id.image_facedetect_blaze_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, ImageBlazeFaceDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_facedetect_blaze_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamBlazeFaceDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_facealign_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamBlazeFaceAlignActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_hairsegmentation_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamHairSegmentationActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_pose_detect_landmark_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamPoseDetectLandmarkActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_skeleton_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamSkeletonDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });

        findViewById(R.id.stream_ocr_detect_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isShowedActivity) {
                    isShowedActivity = true;
                    Intent intent = new Intent();
                    Activity activity = MainActivity.this;
                    intent.setClass(activity, StreamOCRDetectActivity.class);
                    activity.startActivity(intent);
                }
            }
        });
    }

    public static String readJsonFile(String fileName) {
        String jsonStr = "";
        File jsonFile = new File(fileName);
        FileReader fileReader = null;
        try {
            fileReader = new FileReader(jsonFile);
            Reader reader = new InputStreamReader(new FileInputStream(jsonFile),"utf-8");
            int ch = 0;
            StringBuffer sb = new StringBuffer();
            while ((ch = reader.read()) != -1) {
                sb.append((char) ch);
            }
            fileReader.close();
            reader.close();
            jsonStr = sb.toString();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return jsonStr;
    }

    public static File getFileFromAssetsFile(Context context, String fileName){
        String path = "file:///android_asset/" + fileName;
        File file = new File(path);
        return file;
    }

    @Override
    protected void onResume() {
        super.onResume();
        isShowedActivity = false;
    }

}
