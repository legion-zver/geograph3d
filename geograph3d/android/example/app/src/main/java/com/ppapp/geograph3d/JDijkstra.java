package com.ppapp.geograph3d;

import java.util.ArrayList;

// Класс дорог
public class JDijkstra extends JNativePointer {
    // Конструктор
    public JDijkstra(JGraph graph) {
        nativePointer = createDijkstra(graph.nativePointer);
    }
    protected void finalize () {        
        destroyDijkstra(nativePointer);
    }
    // Поиск пути
    // factorId = -1 - без учета фактора движения
    // levelSize = 0.03 - высота потолков (среднее значение)
    public ArrayList<JNode> FindPath(long fromId, long toId, long factorId, double levelSize) {
        long[] pointers = findPath(nativePointer, fromId, toId, factorId, levelSize);
        ArrayList<JNode> result = new ArrayList<JNode>();
        for (long pointer : pointers) {
            if(pointer != 0) {
                result.add(new JNode(pointer));
            }
        }
        return result;
    }
    // Нативные функции
    private native long createDijkstra(long graphPointer);
    private native void destroyDijkstra(long nativePointer);
    private native long[] findPath(long nativePointer, long fromId, long toId, long factorId, double levelSize);
}