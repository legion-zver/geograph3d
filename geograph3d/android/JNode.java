package com.ppapp.geograph3d;

// Класс ноды
public class JNode extends JNativePointer {
    // Constructor
    public JNode(long id, String tag, double latitude, double longitude, int level) {
        nativePointer = createNode(id, tag, latitude, longitude, level);
    }
    // Math:
    public double DistanceTo(double latitude, double longitude, int level, double levelSize) {
        return distanceToII(nativePointer, latitude, longitude, level, levelSize);
    }
    public double DistanceTo(Node node, double levelSize) {
        return distanceTo(nativePointer, node.nativePointer, levelSize);
    }
    public boolean CompareLocation(double latitude, double longitude) {
        return compareLocation(nativePointer, latitude, longitude);
    }
    // Sets:
    public void SetTag(String tag) {
        setTag(nativePointer, tag);
    }
    public void SetLatitude(double latitude) {
        setLatitude(nativePointer, latitude);
    }
    public void SetLevel(int level) {
        setLevel(nativePointer, level);
    }
    // Gets:
    public long GetID() {
        return getID(nativePointer);
    }
    public double GetLatitude() {
        return getLatitude(nativePointer);
    }
    public double GetLongitude() {
        return getLongitude(nativePointer);
    }
    public int GetLevel() {
        return getLevel(nativePointer);
    }
    // Нативные функции (только для внутреннего использования)
    private native long    createNode(long id, String tag, double latitude, double longitude, int level);        
    private native double  distanceTo(long nativePointer, long nodePointer, double levelSize);
    private native double  distanceToII(long nativePointer, double latitude, double longitude, int level, double levelSize);
    private native boolean compareLocation(long nativePointer, double latitude, double longitude);    
    private native void    setTag(long nativePointer, String tag);
    private native void    setLatitude(long nativePointer, double latitude);
    private native void    setLongitude(long nativePointer, double longitude);
    private native void    setLevel(long nativePointer, int level);
    private native long    getID(long nativePointer);
    private native String  getTag(long nativePointer);
    private native double  getLatitude(long nativePointer);
    private native double  getLongitude(long nativePointer);
    private native int     getLevel(long nativePointer);        
}
