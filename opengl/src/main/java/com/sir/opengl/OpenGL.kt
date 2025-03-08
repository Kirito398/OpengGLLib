package com.sir.opengl

interface OpenGL {
    fun getString(): String
    fun initGL(surface: Any)
    fun drawFrame()
    fun clean()
}