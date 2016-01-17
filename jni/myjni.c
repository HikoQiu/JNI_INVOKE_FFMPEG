#include <stdio.h>
#include <jni.h>
#include <android/log.h>
#include "com_example_myjni_Loader.h"
#include "logjam.h"
#define TAG "myjni"


int main(int argc, char **argv);

//int main(int argc, char **argv);

/* This function will be call when the library first be load.
* You can do some init in the libray. return which version jni it support.
*/
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	__android_log_print(ANDROID_LOG_INFO, TAG,"=====Start to load JNI=======");
	return JNI_VERSION_1_6;
}


/**
 * 1. /Users/hikoqiu/packages/android-ndk-r10e/sources/ffmpeg/android/arm/Android.mk
 * 2. /Users/hikoqiu/packages/android-ndk-r10e/ndk-build
 * ffmpeg -y -i /storage/emulated/0/appwonderroot/v/raw/vedio-1586478489.mp4 -strict experimental -r 30 -vcodec mpeg4 -b 50000 /storage/emulated/0/appwonderroot/v/cps/abc.mp4
 *
 */

jstring Java_com_example_myjni_Loader_test(JNIEnv* env, jobject thiz)
{
	__android_log_print(ANDROID_LOG_INFO, TAG, "begin to vcodec");
        char const *str;
        int argc=9;
        char *argv[9];
//        argv[0]="ffmpeg";
//        argv[1]="-i";
//        argv[2]="/storage/emulated/0/appwonderroot/v/raw/vedio367994338.mp4";
//        argv[3]="-i";
//        argv[4]="/storage/emulated/0/appwonderroot/v/raw/vedio367994338.mp4";
//        argv[5]="-vcodec";
//        argv[6]="copy";
//        argv[7]="-acodec";
//        argv[8] = "copy";
//        argv[9]="/storage/emulated/0/appwonderroot/v/raw/newoutput.avi";
        argv[0] = "ffmpeg";
        argv[1] = "-y";
        argv[2] = "-i";
        argv[3] = "/storage/emulated/0/appwonderroot/v/raw/vedio-1586478489.mp4";
        argv[4] = "-strict";
        argv[5] = "experimental";
        argv[6] = "-b";
        argv[7] = "500";
        argv[8] = "/storage/emulated/0/appwonderroot/v/cps/c-vedio-1586478489-c.mp4";


        main(argc, argv);

        __android_log_print(ANDROID_LOG_INFO, TAG, "finish vcodec...");

    char ver[25];
    sprintf(ver, "%d", avcodec_version());

//	avcodec_register_all();

//main(argc, argv);
//    str="Using FFMPEG doing your job";
//    return (*env)->NewStringUTF(env,str);
	//	return (*env)->NewStringUTF(env, "Hello return from jni.");
		return (*env)->NewStringUTF(env, ver);
}


