LOCAL_PATH := $(call my-dir)

# static library info
LOCAL_MODULE := libgeograph3d
LOCAL_CFLAGS := -frtti -fexceptions
LOCAL_SRC_FILES := ../static/$(TARGET_ARCH_ABI)/geograph3d.a
LOCAL_EXPORT_C_INCLUDES := ../include
include $(PREBUILT_STATIC_LIBRARY)


# wrapper info
include $(CLEAR_VARS)
LOCAL_C_INCLUDES += ../include
LOCAL_MODULE    := geograph3d-wrapper
LOCAL_SRC_FILES := geograph3d-wrapper.cpp
LOCAL_STATIC_LIBRARIES := libgeograph3d
include $(BUILD_SHARED_LIBRARY)