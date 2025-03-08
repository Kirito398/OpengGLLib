#include <jni.h>
#include <string>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "egl/display.h"

extern "C" JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_initGL(JNIEnv* env, jobject obj, jobject surface) {
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    initGL(window);
}

extern "C" JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_drawFrame(JNIEnv* env, jobject obj) {
    drawFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_sir_opengl_NativeLib_clean(JNIEnv* env, jobject obj) {
    clean();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_sir_opengl_NativeLib_stringFromJNI(JNIEnv* env, jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}