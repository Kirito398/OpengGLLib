package com.sir.opengl

class OpenGLImpl : OpenGL {
    companion object {
        private val native = NativeLib.getInstance()
    }

    override fun getString(): String {
        return native.stringFromJNI()
    }

    override fun initGL(surface: Any) {
        native.initGL(surface)
    }

    override fun drawFrame() {
        native.drawFrame()
    }

    override fun clean() {
        native.clean()
    }
}