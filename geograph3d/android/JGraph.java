package com.ppapp.geograph3d;

public class JGraph extends JNativePointer {

    // Нативные функции
    private native long     createGraph();
    private native void     destroyGraph(long nativePointer);
    private native long     getNearestNode(long nativePointer, long id, double minRadius);
    private native long     getNearestNode(long nativePointer, double latitude, double longitude, int level, double minRadius);
    private native long     getNode(long nativePointer, long id);
    private native long     getNode(long nativePointer, String tag);
    private native long     getNode(long nativePointer, double latitude, double longitude, int level);    
    private native long     getMaxNodeID(long nativePointer);
    private native long     getNodeByIndex(long nativePointer, long index);
    private native Map<long, long> getNodes(long nativePointer);
    private native long     getCountNodes(long nativePointer);
    private native long     getEdge(long nativePointer, long sourceId, long targetId, boolean allDirections);
    private native Map<long, long> getEdges(long nativePointer, long sourceId);
    private native double   getWeight(long nativePointer, long sourceId, long targetId, long factorId);
    private native double   getWeight(long nativePointer, long sourceId, long targetId, long factorId);
    private native long     getCountEdges(long nativePointer);
    private native void     addNode(long nativePointer, long nodePointer);
    private native long     addNode(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    private native boolean  removeNode(long id);
    private native long     addNodeAndEdges(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    private native long     addEdge(long nativePointer, long sourceId, long targetId);
    private native boolean  removeEdgesContainNode(long nativePointer, long nodeId);
    private native void     clear(long nativePointer);
}
