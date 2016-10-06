package com.ppapp.geograph3d;

class JNativePointer {
    public JNativePointer(){};
    protected JNativePointer(long pointer) {
        nativePointer = pointer;
    }    
    protected long nativePointer;
}