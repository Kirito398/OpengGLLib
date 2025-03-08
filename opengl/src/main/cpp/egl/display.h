//
// Created by Ilgiz Sultanbekov on 08.03.2025.
//

#ifndef OPENGGLLIB_DISPLAY_H
#define OPENGGLLIB_DISPLAY_H
#include <EGL/egl.h>
#include <GLES3/gl3.h>

void initGL(ANativeWindow *nativeWindow);
void drawFrame();
void clean();

#endif //OPENGGLLIB_DISPLAY_H
