package com.ppapp.geograph3d;

import android.util.Log;

import java.util.ArrayList;

public class JGraph extends JNativePointer {
    // Конструктор
    public JGraph() {
        nativePointer = createGraph();
    }
    protected void finalize () {
        clear(nativePointer);
        destroyGraph(nativePointer);
    }
    // Получение ближайшей точки от ...
    public JNode GetNearestNode(long id, double minRadius) {
        return new JNode(getNearestNode(nativePointer, id, minRadius));
    }
    public JNode GetNearestNode(double latitude, double longitude, int level, double minRadius) {
        return new JNode(getNearestNodeII(nativePointer, latitude, longitude, level, minRadius));
    }
    // Получение нод из графа
    public JNode GetNode(long id) {
        return new JNode(getNode(nativePointer, id));
    }
    public JNode GetNode(String tag) {
        return new JNode(getNodeII(nativePointer, tag));
    }
    public JNode GetNode(double latitude, double longitude, int level) {
        return new JNode(getNodeIII(nativePointer, latitude, longitude, level));
    }
    // Получить самый большой ID ноды в графе
    public long GetMaxNodeID() {
        return getMaxNodeID(nativePointer);
    }
    // Получить ноду по индексу
    public JNode GetNodeByIndex(long index) {
        return new JNode(getNodeByIndex(nativePointer, index));
    }
    // Получить число нод
    public long GetCountNodes() {
        return getCountNodes(nativePointer);
    }
    // Получить список нод
    public ArrayList<JNode> GetNodes() {
        long[] pointers = getNodes(nativePointer);
        ArrayList<JNode> result = new ArrayList<JNode>();
        for (long pointer : pointers) {
            if(pointer != 0) {
                result.add(new JNode(pointer));
            }
        }
        return result;
    }
    // Получить число ребер у графа
    public long GetCountEdges() {
        return getCountEdges(nativePointer);
    }
    // Получить ребро
    public JEdge GetEdge(long sourceId, long targetId, boolean allDirections) {
        return new JEdge(getEdge(nativePointer, sourceId, targetId, allDirections));
    } 
    // Получить список ребер у ноды
    public ArrayList<JEdge> GetEdges(long sourceNodeID) {
        long[] pointers = getEdges(nativePointer, sourceNodeID);
        ArrayList<JEdge> result = new ArrayList<JEdge>();
        for (long pointer : pointers) {
            if(pointer != 0) {
                result.add(new JEdge(pointer));
            }
        }
        return result;
    }
    // Получить вес ребра
    public double GetWeight(long sourceId, long targetId, long factorId) {
        return getWeight(nativePointer, sourceId, targetId, factorId);
    }
    // Добавить ноду
    public void AddNode(JNode node) {
        addNode(nativePointer, node.nativePointer);
    }
    public JNode AddNode(long id, String tag, double latitude, double longitude, int level) {
        return new JNode(addNodeII(nativePointer, id, tag, latitude, longitude, level));
    }
    // Удаление ноды по ID из графа
    public boolean RemoveNode(long id) {
        return removeNode(nativePointer, id);
    }
    // Добавляем ноду и создаем две связи для нее с графом на этаже
    public JNode AddNodeAndEdges(long id, String tag, double latitude, double longitude, int level) {
        return new JNode(addNodeAndEdges(nativePointer, id, tag, latitude, longitude, level));
    }
    // Добавляем ребро
    public JEdge AddEdge(long sourceId, long targetId) {
        return new JEdge(addEdge(nativePointer, sourceId, targetId));
    }
    // Удаляем все ребра связанные с нодой
    public boolean RemoveEdgesContainNode(long nodeId) {
        return removeEdgesContainNode(nativePointer, nodeId);
    }
    // Очищаем граф (удаление все нод и ребер из памяти)
    public void Clear() {
        clear(nativePointer);
    }
    // Нативные функции
    private native long     createGraph();
    private native void     destroyGraph(long nativePointer);
    private native long     getNearestNode(long nativePointer, long id, double minRadius);
    private native long     getNearestNodeII(long nativePointer, double latitude, double longitude, int level, double minRadius);
    private native long     getNode(long nativePointer, long id);
    private native long     getNodeII(long nativePointer, String tag);
    private native long     getNodeIII(long nativePointer, double latitude, double longitude, int level);    
    private native long     getMaxNodeID(long nativePointer);
    private native long     getNodeByIndex(long nativePointer, long index);
    private native long[]   getNodes(long nativePointer);
    private native long     getCountNodes(long nativePointer);
    private native long     getEdge(long nativePointer, long sourceId, long targetId, boolean allDirections);
    private native long[]   getEdges(long nativePointer, long sourceId);
    private native double   getWeight(long nativePointer, long sourceId, long targetId, long factorId);    
    private native long     getCountEdges(long nativePointer);
    private native void     addNode(long nativePointer, long nodePointer);
    private native long     addNodeII(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    private native boolean  removeNode(long nativePointer, long id);
    private native long     addNodeAndEdges(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    private native long     addEdge(long nativePointer, long sourceId, long targetId);
    private native boolean  removeEdgesContainNode(long nativePointer, long nodeId);
    private native void     clear(long nativePointer);
}
