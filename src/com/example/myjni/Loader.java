package com.example.myjni;

import android.util.Log;

public class Loader {
    static {
        System.loadLibrary("myjni");
        System.loadLibrary("avutil-54");  
        System.loadLibrary("avcodec-56");  
        System.loadLibrary("avformat-56");  
        System.loadLibrary("avdevice-56");  
        System.loadLibrary("swresample-1");  
        System.loadLibrary("swscale-3");  
//        System.loadLibrary("postproc-53");  
        System.loadLibrary("avfilter-5"); 
    }
    
    public void doTest() {
        
        Log.i("myjni", "test to invoke jni func.");
        Log.i("myjni", "Myjni string: " + test());
    }

    
//    public native String fexit(String videokitLibPath);
//    
//    public native String unload();
//
//    public native String load(String[] args, String videokitSdcardPath, String videokitLibPath, boolean isComplex);
    
    public native String test();
}
