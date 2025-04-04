//
// Created by Ilgiz Sultanbekov on 04.04.2025.
//

#ifndef OPENGGLLIB_NATIVECORE_H
#define OPENGGLLIB_NATIVECORE_H
#include <android/native_window.h>
#include <GLES3/gl3.h>
#include <__chrono/steady_clock.h>

#include "../egl/display.h"

void init(ANativeWindow *window);
void onSurfaceChanged(int width, int height);
void loadTexture(AAssetManager* assetManager, const char* filePath, GLuint* textureId, int* width, int* height);
void drawBegin();
void drawTexture(GLuint textureID, int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight);
void drawEnd();
long long getDeltaTime();

#endif //OPENGGLLIB_NATIVECORE_H
