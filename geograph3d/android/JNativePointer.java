package com.ppapp.geograph3d;

class JNativePointer {
    public JNativePointer(){
        nativePointer = 0;
    }
    protected JNativePointer(long pointer) {
        nativePointer = pointer;
    }
    public bool IsNULL() {
        return nativePointer == 0;
    }
    public bool IsEmpty() { 
        return nativePointer == 0;
    }
    public bool IsValid() {
        return nativePointer != 0;
    }
    // Указатель
    protected long nativePointer;
}