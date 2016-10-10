package com.ppapp.geograph3d;

class JNativePointer {
    public JNativePointer(){
        nativePointer = 0;
    }
    protected JNativePointer(long pointer) {
        nativePointer = pointer;
    }
    public boolean IsNULL() {
        return nativePointer == 0;
    }
    public boolean IsEmpty() {
        return nativePointer == 0;
    }
    public boolean IsValid() {
        return nativePointer != 0;
    }
    // Указатель
    protected long nativePointer;
}