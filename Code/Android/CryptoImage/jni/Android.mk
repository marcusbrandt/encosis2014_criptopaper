LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include /home/marcusbrandt/Softwares/OpenCV-2.4.8-android-sdk/sdk/native/jni/OpenCV.mk

APP_STL := stlport_static
LOCAL_MODULE    := crypto_image
LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_SRC_FILES := crypto.cpp
LOCAL_LDLIBS    += -lm -llog -landroid


include $(BUILD_SHARED_LIBRARY)