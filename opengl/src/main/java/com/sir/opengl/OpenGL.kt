package com.sir.opengl

import android.content.res.AssetManager

interface OpenGL {
    fun initGL(surface: Any)
    fun loadTextures(filepath: String, assetManager: AssetManager): GLTexture2DParam
    fun onSurfaceChanged(width: Int, height: Int)

    fun getDeltaTime(): Long
    fun beginRender()
    fun render(textureId: Int, posX: Int, posY: Int, tileX: Int, tileY: Int, tileWidth: Int, tileHeight: Int, atlasWidth: Int, atlasHeight: Int)
    fun endRender()
}