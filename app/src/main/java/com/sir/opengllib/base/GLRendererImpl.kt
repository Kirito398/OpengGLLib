package com.sir.opengllib.base

import android.view.SurfaceHolder
import com.sir.opengl.OpenGL
import com.sir.opengl.OpenGLImpl
import com.sir.opengllib.base.interfaces.GLRenderer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class GLRendererImpl(
    private val holder: SurfaceHolder
) : GLRenderer {
    private val openGL: OpenGL = OpenGLImpl()
    private var callback: GLRenderer.Callback? = null

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        callback?.onSurfaceCreated()
        openGL.initGL(holder.surface)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        openGL.onSurfaceChanged(width, height)
    }

    override fun onDrawFrame(p0: GL10?) {
        callback?.apply {
            onUpdate(openGL.getDeltaTime())
            openGL.beginRender()
            onDraw(this@GLRendererImpl)
            openGL.endRender()
        }
    }

    override fun render(texture: GLTexture2D, posX: Int, posY: Int) {
        openGL.render(
            texture.param.textureId,
            posX = posX,
            posY = posY,
            tileX = 0,
            tileY = 0,
            tileWidth = texture.param.width,
            tileHeight = texture.param.height,
            atlasWidth = texture.param.width,
            atlasHeight = texture.param.height
        )
    }

    override fun render(sprite: GLSprite2D, posX: Int, posY: Int) {
        val texture = sprite.texture
        openGL.render(
            texture.param.textureId,
            posX = posX,
            posY = posY,
            tileX = sprite.startX,
            tileY = sprite.startY,
            tileWidth = sprite.width,
            tileHeight = sprite.height,
            atlasWidth = texture.param.width,
            atlasHeight = texture.param.height
        )
    }

    override fun addCallback(callback: GLRenderer.Callback) {
        this.callback = callback
    }
}