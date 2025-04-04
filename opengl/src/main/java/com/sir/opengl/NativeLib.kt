package com.sir.opengl

import android.content.res.AssetManager

class NativeLib private constructor() {
    companion object {
        init {
            System.loadLibrary("opengl")
        }

        fun getInstance(): NativeLib {
            return NativeLib()
        }
    }

    /**
     * A native method that is implemented by the 'opengl' native library,
     * which is packaged with this application.
     */
    external fun initGL(surface: Any)
    external fun onSurfaceChanged(width: Int, height: Int)
    external fun loadTextures(filePath: String, assetManager: AssetManager): GLTexture2DParam

    external fun beginRender()
    external fun render(textureId: Int, posX: Int, posY: Int, tileX: Int, tileY: Int, tileWidth: Int, tileHeight: Int, atlasWidth: Int, atlasHeight: Int)
    external fun endRender()
    external fun getDeltaTime(): Long
}