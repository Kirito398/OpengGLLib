//
// Created by Ilgiz Sultanbekov on 08.03.2025.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "display.h"
#include "../utils/log.h"

const char* vertexShaderSource = R"(
    attribute vec4 a_Position;
    attribute vec2 a_TexCoord;
    varying vec2 v_TexCoord;

    void main() {
        gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
        v_TexCoord = a_TexCoord;
    }
)";

const char* fragmentShaderSource = R"(
    precision mediump float;
    varying vec2 v_TexCoord;
    uniform sampler2D u_Texture;

    void main() {
        gl_FragColor = texture2D(u_Texture, v_TexCoord);
    }
)";

GLfloat tileVertices[] = {
        //  X      Y      U     V
        -1.0f, -1.0f,  0.0f, 1.0f,  // Левый нижний
        1.0f, -1.0f,  1.0f, 1.0f,  // Правый нижний
        -1.0f,  1.0f,  0.0f, 0.0f,  // Левый верхний
        1.0f,  1.0f,  1.0f, 0.0f   // Правый верхний
};

GLuint VBO;

EGLDisplay display;
EGLSurface surface;
EGLContext context;
GLuint shaderProgram;

void NativeDisplay::initGL(ANativeWindow *nativeWindow) {
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    EGLConfig config;
    EGLint numConfigs;
    EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_NONE
    };

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    surface = eglCreateWindowSurface(display, config, nativeWindow, nullptr);
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
    eglMakeCurrent(display, surface, surface, context);
}

void NativeDisplay::drawBegin() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
}

void NativeDisplay::drawTexture(GLuint textureID, int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight) {
    updateTileVertices(posX, posY, tileX, tileY, tileWidth, tileHeight, atlasWidth, atlasHeight);
    initBuffers();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void NativeDisplay::drawEnd() {
    if (eglGetCurrentSurface(EGL_DRAW) == EGL_NO_SURFACE) {
        LOGE("EGLSurface not found!");
        return;
    }

    eglSwapBuffers(display, surface);
}

void NativeDisplay::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

static GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        LOGD("Shader compilation failed: %s", infoLog);
    }
    return shader;
}

void NativeDisplay::initShaders() {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        LOGD("Shader linking failed: %s", infoLog);
    }
}

void NativeDisplay::initBuffers() {
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tileVertices), tileVertices, GL_STATIC_DRAW);

    // Координаты вершин
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Координаты текстуры
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void NativeDisplay::updateTileVertices(int posX, int posY, int tileX, int tileY, int tileWidth, int tileHeight, int atlasWidth, int atlasHeight) {
    float uStart = tileX / (float)atlasWidth;
    float vStart = tileY / (float)atlasHeight;
    float uEnd = (tileX + tileWidth) / (float)atlasWidth;
    float vEnd = (tileY + tileHeight) / (float)atlasHeight;

    tileVertices[2] = uStart;
    tileVertices[3] = vEnd;

    tileVertices[6] = uEnd;
    tileVertices[7] = vEnd;

    tileVertices[10] = uStart;
    tileVertices[11] = vStart;

    tileVertices[14] = uEnd;
    tileVertices[15] = vStart;

    float tileWidthHalf = (float)tileWidth / 2.0F;
    float tileHeightHalf = (float)tileHeight / 2.0F;
    float atlasWidthHalf = (float)atlasWidth / 2.0F;
    float atlasHeightHalf = (float)atlasHeight / 2.0F;

    tileVertices[0] = ((float)posX - tileWidthHalf) / atlasWidthHalf;
    tileVertices[1] = ((float)posY - tileHeightHalf) / atlasHeightHalf;

    tileVertices[4] = ((float)posX + tileWidthHalf) / atlasWidthHalf;
    tileVertices[5] = ((float)posY - tileHeightHalf) / atlasHeightHalf;

    tileVertices[8] = ((float)posX - tileWidthHalf) / atlasWidthHalf;
    tileVertices[9] = ((float)posY + tileHeightHalf) / atlasHeightHalf;

    tileVertices[12] = ((float)posX + tileWidthHalf) / atlasWidthHalf;
    tileVertices[13] = ((float)posY + tileHeightHalf) / atlasHeightHalf;
}

void NativeDisplay::loadTexture(AAssetManager* assetManager, const char* filePath, GLuint* textureId, int* width, int* height) {
    AAsset* asset = AAssetManager_open(assetManager, filePath, AASSET_MODE_BUFFER);
    if (!asset) {
        LOGE("Failed to open asset: %s", filePath);
        return;
    }

    // Получаем размер файла и читаем его в буфер
    off_t assetSize = AAsset_getLength(asset);
    auto* buffer = new unsigned char[assetSize];
    AAsset_read(asset, buffer, assetSize);
    AAsset_close(asset);

    int channels;
    unsigned char* image = stbi_load_from_memory(buffer, assetSize, width, height, &channels, STBI_rgb_alpha);
    delete []buffer;

    if (!image) {
        LOGD("Failed to load texture: %s", filePath);
        return;
    }

    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_2D, *textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
}

NativeDisplay::NativeDisplay() = default;

NativeDisplay::~NativeDisplay() {
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);
}
