package com.ppapp.geograph3d;

// Класс дорог
public class JRoads extends JNativePointer {
    enum Direction { Forward, Backward, All };
    public JRoads() {
        nativePointer = createRoads();
    }
    protected void finalize () {
        clear(nativePointer, true);
        destroyRoads(nativePointer);
    }
    public void Clear(boolean removeFromMemory) {
        clear(nativePointer, removeFromMemory);
    }
    public boolean FillGraph(JGraph graph) {
        return fillGraph(nativePointer, graph.nativePointer);
    }
    public boolean AddRoad(ArrayList<JNode> nodes, Direction direction) {
        return addRoad(nativePointer, nodes, direction.original());
    }
    // Нативные функции    
    private native long     createRoads();
    private native void     destroyRoads(long nativePointer);
    private native void     clear(long nativePointer, boolean removeFromMemory);
    private native boolean  fillGraph(long nativePointer, long graphPointer);
    private native boolean  addRoad(long nativePointer, ArrayList<JNode> nodes, int directionType);
}
