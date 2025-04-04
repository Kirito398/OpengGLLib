#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "core/nativecore.h"
#include "utils/log.h"

extern "C" JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_initGL(JNIEnv* env, jobject obj, jobject surface) {
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    init(window);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_onSurfaceChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    onSurfaceChanged(width, height);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_sir_opengl_NativeLib_loadTextures(JNIEnv *env, jobject thiz, jstring filePath, jobject assetManager) {
    AAssetManager* gAssetManager = AAssetManager_fromJava(env, assetManager);
    unsigned int textureId;
    int width;
    int height;

    const char *charFilePath = env->GetStringUTFChars(filePath, nullptr);
    loadTexture(gAssetManager, charFilePath, &textureId, &width, &height);
    env->ReleaseStringUTFChars(filePath, charFilePath);

    jclass myObjectClass = env->FindClass("com/sir/opengl/GLTexture2DParam");
    if (myObjectClass == nullptr) {
        LOGE("Class MyObject not found!");
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(myObjectClass, "<init>", "(III)V");
    if (constructor == nullptr) {
        LOGE("Constructor not found!");
        return nullptr;
    }

    jobject myObject = env->NewObject(myObjectClass, constructor, (int)textureId, width, height);
    return myObject;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_beginRender(JNIEnv *env, jobject thiz) {
    drawBegin();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_render(JNIEnv *env, jobject thiz, jint textureId, jint posX, jint posY, jint tileX, jint tileY, jint tileWidth, jint tileHeight, jint atlasWidth, jint atlasHeight) {
    drawTexture(textureId, posX, posY, tileX, tileY, tileWidth, tileHeight, atlasWidth, atlasHeight);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_endRender(JNIEnv *env, jobject thiz) {
    drawEnd();
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_sir_opengl_NativeLib_getDeltaTime(JNIEnv *env, jobject thiz) {
    return getDeltaTime();
}