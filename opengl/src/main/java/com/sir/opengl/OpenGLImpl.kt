package com.sir.opengl

import android.content.res.AssetManager

class OpenGLImpl : OpenGL {
    companion object {
        private val native = NativeLib.getInstance()
    }

    override fun initGL(surface: Any) {
        native.initGL(surface)
    }

    override fun loadTextures(filepath: String, assetManager: AssetManager): GLTexture2DParam {
        return native.loadTextures(filepath, assetManager)
    }

    override fun onSurfaceChanged(width: Int, height: Int) {
        native.onSurfaceChanged(width, height)
    }

    override fun getDeltaTime(): Long {
        return native.getDeltaTime()
    }

    override fun beginRender() {
        native.beginRender()
    }

    override fun render(textureId: Int, posX: Int, posY: Int, tileX: Int, tileY: Int, tileWidth: Int, tileHeight: Int, atlasWidth: Int, atlasHeight: Int) {
        native.render(textureId, posX, posY, tileX, tileY, tileWidth, tileHeight, atlasWidth, atlasHeight)
    }

    override fun endRender() {
        native.endRender()
    }
}