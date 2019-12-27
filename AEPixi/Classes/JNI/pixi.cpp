#ifdef __ANDROID__

#include "AJPixi.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL
Java_app_engine_PIXI_create(JNIEnv *env, jclass type, jstring pathfile_) {
    const char *pathfile = env->GetStringUTFChars(pathfile_, 0);
    AJPixi* pixi = new AJPixi(pathfile);
    env->ReleaseStringUTFChars(pathfile_, pathfile);
    return (jlong)pixi;
}

JNIEXPORT void JNICALL
Java_app_engine_PIXI_release(JNIEnv *env, jclass type, jlong pixi_) {
    AJPixi* pixi = (AJPixi*)pixi_;
    delete pixi;
}

JNIEXPORT void JNICALL
Java_app_engine_PIXI_loadGame(JNIEnv *env, jclass type, jlong pixi_, jstring gamename_) {
    if (pixi_ == 0) {
        return;
    }
    const char *gamename = env->GetStringUTFChars(gamename_, 0);
    AJPixi* pixi = (AJPixi*)pixi_;
    pixi->loadGame(gamename);
    env->ReleaseStringUTFChars(gamename_, gamename);
}

JNIEXPORT void JNICALL
Java_app_engine_PIXI_onTouch(JNIEnv *env, jclass type, jlong pixi_, jfloatArray events_, jstring function_) {
    if (pixi_ == 0) {
        return;
    }
    AJPixi* pixi = (AJPixi*)pixi_;
    jsize   length = env->GetArrayLength(events_);
    jfloat *events = env->GetFloatArrayElements(events_, NULL);
    const char *function = env->GetStringUTFChars(function_, 0);
    AEPointList points;
    for (int i = 0; i < length; i=i+2) {
        points.push_back(AEPointMake(events[i], events[i+1]));
    }
    pixi->onTouch(points, function);
    env->ReleaseFloatArrayElements(events_, events, 0);
}

JNIEXPORT void JNICALL
Java_app_engine_PIXI_onLoop(JNIEnv *env, jclass type, jlong pixi_) {
    if (pixi_ == 0) {
        return;
    }
    AJPixi* pixi = (AJPixi*)pixi_;
    pixi->onLoop();
    CheckGlError();
}

#ifdef __cplusplus
}
#endif

#endif
