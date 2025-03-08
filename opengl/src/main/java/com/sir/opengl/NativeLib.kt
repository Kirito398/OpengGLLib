package com.sir.opengl

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
    external fun stringFromJNI(): String
    external fun initGL(surface: Any)
    external fun drawFrame()
    external fun clean()
}