package com.sir.opengllib.base

import android.content.Context
import com.sir.opengl.GLTexture2DParam
import com.sir.opengl.OpenGL
import com.sir.opengl.OpenGLImpl

class GLTexture2D(
    filePath: String,
    context: Context
) {
    private val openGL: OpenGL = OpenGLImpl()
    val param: GLTexture2DParam

    init {
        context.assets?.let {
            param = openGL.loadTextures(filePath, it)
        } ?: error("Asset manager not found!")
    }
}