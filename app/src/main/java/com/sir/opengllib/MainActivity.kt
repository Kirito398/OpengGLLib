package com.sir.opengllib

import android.os.Bundle
import android.view.SurfaceHolder
import android.view.SurfaceView
import androidx.appcompat.app.AppCompatActivity
import com.sir.opengl.OpenGL
import com.sir.opengl.OpenGLImpl

class MainActivity : AppCompatActivity() {
    private val openGL: OpenGL = OpenGLImpl()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val surface = SurfaceView(this)
        setContentView(surface)

        surface.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                openGL.initGL(holder.surface)
            }

            override fun surfaceChanged(p0: SurfaceHolder, p1: Int, p2: Int, p3: Int) {
                openGL.drawFrame()
            }

            override fun surfaceDestroyed(p0: SurfaceHolder) {
                openGL.clean()
            }
        })
    }
}