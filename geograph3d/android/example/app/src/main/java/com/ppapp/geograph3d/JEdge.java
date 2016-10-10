package com.ppapp.geograph3d;

public class JEdge extends JNativePointer {
    protected JEdge(long pointer) {
        nativePointer = pointer;
    }
    public JEdge(JNode source, JNode target) {
        nativePointer = createEdge(source.nativePointer, target.nativePointer);
    }
    public JNode GetSource() {
        return new JNode(getSourcePointer(nativePointer));
    }
    public JNode GetTarget() {
        return new JNode(getTargetPointer(nativePointer));
    }
    public double GetFactor(long id) {
        return getFactor(nativePointer, id);
    }
    public void AddFactor(long id, double value) {
        addFactor(nativePointer, id, value);
    }
    public void RemoveFactor(long id) {
        removeFactor(nativePointer, id);
    }
    public long GetCountFactors() {
        return getCountFactors(nativePointer);
    }
    public double GetWeight(long factorID, double levelSize) {
        return getWeight(nativePointer, factorID, levelSize);
    }
    public void Destroy() {
        destroyEdge(nativePointer);
        nativePointer = 0;
    }
    // Нативные функции
    private native long  createEdge(long nodeSourcePointer, long nodeTargetPointer);
    private native void  destroyEdge(long nativePointer);
    private native long  getSourcePointer(long nativePointer);
    private native long  getTargetPointer(long nativePointer);
    public native double getFactor(long nativePointer, long id);
    public native void   addFactor(long nativePointer, long id, double value);
    public native void   removeFactor(long nativePointer, long id);
    public native long   getCountFactors(long nativePointer);
    public native double getWeight(long nativePointer, long factorID, double levelSize);
}
