//
// Created by Ilgiz Sultanbekov on 08.03.2025.
//

#ifndef OPENGGLLIB_DISPLAY_H
#define OPENGGLLIB_DISPLAY_H
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>

class NativeDisplay {
    void initBuffers();
    void updateTileVertices(int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight);

public:
    NativeDisplay();
    ~NativeDisplay();

    void initGL(ANativeWindow *nativeWindow);
    void initShaders();
    void loadTexture(AAssetManager* assetManager, const char* filePath, GLuint* textureId, int* width, int* height);
    void onSurfaceChanged(int width, int height);
    void drawBegin();
    void drawTexture(GLuint textureID, int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight);
    void drawEnd();
};

#endif //OPENGGLLIB_DISPLAY_H
