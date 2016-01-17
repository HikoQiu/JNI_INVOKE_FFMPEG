LOCAL_PATH := $(call my-dir)
#$(warning $(LOCAL_PATH))

include $(CLEAR_VARS)
LOCAL_MODULE    := myjni
LOCAL_LDLIBS := -llog -ljnigraphics -lz -landroid
LOCAL_CFLAGS := -Wdeprecated-declarations
ANDROID_LIB := -landroid
LOCAL_C_INCLUDES:=/Users/hikoqiu/packages/android-ndk-r10e/sources/ffmpeg
LOCAL_SRC_FILES :=  myjni.c ffmpeg.c ffmpeg_filter.c ffmpeg_opt.c cmdutils.c
LOCAL_SHARED_LIBRARIES := libavformat libavcodec libswscale libavutil libswresample libavfilter libavdevice

include $(BUILD_SHARED_LIBRARY)
$(call import-module,ffmpeg/android/arm)