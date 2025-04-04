//
// Created by Ilgiz Sultanbekov on 04.04.2025.
//

#include "nativecore.h"

NativeDisplay nativeDisplay;
std::chrono::steady_clock::time_point lastTime;

void init(ANativeWindow *window) {
    nativeDisplay.initGL(window);
    nativeDisplay.initShaders();

    lastTime = std::chrono::steady_clock::now();
}

long long getDeltaTime() {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);

    lastTime = currentTime;

    return duration.count() / 1000L;
}

void loadTexture(AAssetManager* assetManager, const char* filePath, GLuint * textureId, int* width, int* height) {
    nativeDisplay.loadTexture(assetManager, filePath, textureId, width, height);
}

void onSurfaceChanged(int width, int height) {
    nativeDisplay.onSurfaceChanged(width, height);
}

void drawBegin() {
    nativeDisplay.drawBegin();
}

void drawTexture(GLuint textureID, int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight) {
    nativeDisplay.drawTexture(textureID, posX, posY, tileX, tileY, tileWidth, tileHeight, atlasWidth, atlasHeight);
}

void drawEnd() {
    nativeDisplay.drawEnd();
}