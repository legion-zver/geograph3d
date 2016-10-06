package com.ppapp.geograph3d;

public class JEdge extends JNativePointer {
    
    // Нативные функции
    private native long  createEdge(long nativePointer, long nodeSourcePointer, long nodeTargetPointer);    
    private native long  getSourcePointer(long nativePointer);
    private native long  getTargetPointer(long nativePointer);
    public native long   getFactor(long nativePointer, long id);
    public native void   addFactor(long nativePointer, long id, double value);
    public native void   removeFactor(long nativePointer, long id);
    public native long   getCountFactors(long nativePointer);
    public native double getWeight(long nativePointer, long factorID, double levelSize);
}
