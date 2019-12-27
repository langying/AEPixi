APP_OPTIM    := release
APP_STL      := gnustl_static
APP_ABI      := armeabi armeabi-v7a x86
APP_PLATFORM := android-21
APP_CFLAGS   += -std=c++11 -Wall
APP_CPPFLAGS += -std=c++11 -Wall -frtti -D__BYTE_ORDER=__BIG_ENDIAN
LOCAL_CPP_FEATURES += exceptions

NDK_TOOLCHAIN_VERSION := 4.8

