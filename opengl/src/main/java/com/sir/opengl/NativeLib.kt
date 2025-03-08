package com.sir.opengl

class NativeLib {

    /**
     * A native method that is implemented by the 'opengl' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'opengl' library on application startup.
        init {
            System.loadLibrary("opengl")
        }
    }
}