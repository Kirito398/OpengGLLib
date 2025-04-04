package com.sir.opengllib

import com.sir.opengllib.base.GLActivity
import com.sir.opengllib.base.GLSprite2D
import com.sir.opengllib.base.GLTexture2D
import com.sir.opengllib.base.interfaces.GLRenderer

class MainActivity : GLActivity() {
    private lateinit var texture: GLTexture2D
    private lateinit var sprite1: GLSprite2D
    private lateinit var sprite2: GLSprite2D

    override fun onSurfaceCreated() {
        texture = GLTexture2D("texture.png", applicationContext)
        sprite1 = GLSprite2D(texture, 0, 0, 430, 430)
        sprite2 = GLSprite2D(texture, 430, 430, 430, 430)
    }

    override fun onUpdate(deltaTime: Long) {
        //TODO("Not yet implemented")
    }

    override fun onDraw(renderer: GLRenderer) {
        renderer.apply {
            //render(texture, 0, 0)
            render(sprite1, -215, 215)
            render(sprite2, 215, -215)
        }
    }
}