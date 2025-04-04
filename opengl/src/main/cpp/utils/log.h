//
// Created by Ilgiz Sultanbekov on 03.04.2025.
//

#ifndef OPENGGLLIB_LOG_H
#define OPENGGLLIB_LOG_H

#include <android/log.h>

#define LOG_TAG "NativeLog"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //OPENGGLLIB_LOG_H
