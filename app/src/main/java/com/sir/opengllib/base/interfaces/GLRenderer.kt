package com.sir.opengllib.base.interfaces

import android.opengl.GLSurfaceView
import com.sir.opengllib.base.GLSprite2D
import com.sir.opengllib.base.GLTexture2D

interface GLRenderer : GLSurfaceView.Renderer {
    fun render(texture: GLTexture2D, posX: Int, posY: Int)
    fun render(sprite: GLSprite2D, posX: Int, posY: Int)
    fun addCallback(callback: Callback)

    interface Callback {
        fun onSurfaceCreated()
        fun onUpdate(deltaTime: Long)
        fun onDraw(renderer: GLRenderer)
    }
}