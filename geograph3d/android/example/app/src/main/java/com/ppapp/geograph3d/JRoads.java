package com.ppapp.geograph3d;

import java.util.ArrayList;

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
        if(nodes.size() > 0) {
            // Проверка реальных данных
            int size = 0;
            for(JNode node: nodes) {
                if(node.IsValid()) {
                    size++;
                }
            }
            if(size > 0) {
                long[] pointers = new long[size];
                int i = 0;
                for(JNode node: nodes) {
                    if(node.IsValid()) {
                        pointers[i] = node.nativePointer;
                        i++;
                    }
                }
                return addRoad(nativePointer, pointers, direction.ordinal());
            }
        }
        return false;
    }
    // Нативные функции    
    private native long     createRoads();
    private native void     destroyRoads(long nativePointer);
    private native void     clear(long nativePointer, boolean removeFromMemory);
    private native boolean  fillGraph(long nativePointer, long graphPointer);
    private native boolean  addRoad(long nativePointer, long[] nodes, int directionType);
}
