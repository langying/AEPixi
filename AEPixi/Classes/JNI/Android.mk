LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)   
LOCAL_MODULE    := libcurl
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)   
LOCAL_MODULE    := libjs_static
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libjs_static.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)   
LOCAL_MODULE    := libpng
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)   
LOCAL_MODULE    := libssl
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)   
LOCAL_MODULE    := libcrypto
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    	   := pixi
LOCAL_MODULE_FILENAME  := libpixi
LOCAL_STATIC_LIBRARIES := libcurl libjs_static libpng libssl libcrypto

MY_SRC_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/AELoop/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/AEPixi/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/AEPixi/Base/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/AJPixi/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/AJPixi/Base/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/ANUrl/*.cpp)
MY_SRC_LIST += $(wildcard $(LOCAL_PATH)/libjson/*.cpp)
LOCAL_SRC_FILES := $(patsubst $(LOCAL_PATH)/%, %, $(MY_SRC_LIST))

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/AELoop
LOCAL_C_INCLUDES += $(LOCAL_PATH)/AEPixi
LOCAL_C_INCLUDES += $(LOCAL_PATH)/AEPixi/Base
LOCAL_C_INCLUDES += $(LOCAL_PATH)/AJPixi
LOCAL_C_INCLUDES += $(LOCAL_PATH)/AJPixi/Base
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ANUrl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libcurl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libjs
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libjs/js
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libjs/mozilla
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libjson/json
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libpng

LOCAL_LDLIBS := -lz -llog -landroid -lGLESv2

LOCAL_CFLAGS   := -fexceptions -DJSON_IS_AMALGAMATION -D__STDC_LIMIT_MACROS=1 -D__ANDROID__ -Wsign-compare -Wno-invalid-offsetof
LOCAL_CPPFLAGS := -fexceptions -DJSON_IS_AMALGAMATION -D__STDC_LIMIT_MACROS=1 -D__ANDROID__ -Wsign-compare -Wno-invalid-offsetof

include $(BUILD_SHARED_LIBRARY)
