package com.sir.opengllib.base

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.sir.opengllib.base.interfaces.GLRenderer

abstract class GLActivity : AppCompatActivity(), GLRenderer.Callback {
    private lateinit var glSurfaceView: GLSurfaceView
    private lateinit var renderer: GLRenderer

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        glSurfaceView = GLSurfaceView(this)

        renderer = GLRendererImpl(glSurfaceView.holder).apply {
            addCallback(this@GLActivity)
        }

        glSurfaceView.apply {
            setEGLContextClientVersion(2)
            setRenderer(renderer)
        }

        setContentView(glSurfaceView)
    }

    override fun onResume() {
        super.onResume()
        glSurfaceView.onResume()
    }

    override fun onPause() {
        super.onPause()
        glSurfaceView.onPause()
    }
}