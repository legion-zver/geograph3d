package com.ppapp.geograph3d;

// Класс дорог
public class JDijkstra extends JNativePointer {

    // Нативные функции
    private native long     createDijkstra(long graphPointer);
    private native void     destroyDijkstra(long nativePointer);
}