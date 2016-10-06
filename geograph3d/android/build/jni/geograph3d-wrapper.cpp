#include <string.h>
#include <jni.h>
#include <../include/geograph3d.hpp>

extern "C" {
    // MARK: JNode
    // long JNode->createNode(long id, String tag, double latitude, double longitude, int level);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JNode_createNode(JNIEnv *env, jobject thiz, jlong id, jstring tag, jdouble latitude, jdouble longitude, jint level) {
        return (long)(new Node(id, tag, latitude, longitude, level));
    }
    // double JNode->distanceTo(long nativePointer, long nodePointer, double levelSize);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JNode_distanceTo(JNIEnv *env, jobject thiz, jlong nativePointer, jlong nodePointer, jdouble levelSize) {
        if(nativePointer != 0 && nodePointer != 0) {                        
            return ((Node*)nativePointer)->DistanceTo((Node*)nodePointer, levelSize);
        }
        return -1.0;
    }
    // double JNode->distanceTo(long nativePointer, double latitude, double longitude, int level, double levelSize);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JNode_distanceTo_II(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude, jdouble longitude, jint level, jdouble levelSize) {
        if(nativePointer != 0 ) {
            return ((Node*)nativePointer)->DistanceTo(latitude, longitude, level, levelSize);
        }
        return -1.0;
    }
    // boolean JNode->compareLocation(long nativePointer, double latitude, double longitude);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JNode_compareLocation(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude, jdouble longitude) {
        if(nativePointer != 0 ) {
            return ((Node*)nativePointer)->CompareLocation(latitude, longitude);
        }
        return false;
    }
    // void JNode->setTag(long nativePointer, String tag);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JNode_setTag(JNIEnv *env, jobject thiz, jlong nativePointer, jstring tag) {
        if(nativePointer != 0 ) {
            ((Node*)nativePointer)->SetTag(tag);
        }
    }
    // void JNode->setLatitude(long nativePointer, double latitude);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JNode_setLatitude(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude) {
        if(nativePointer != 0 ) {
            ((Node*)nativePointer)->SetLatitude(latitude);
        }
    }
    // void JNode->setLongitude(long nativePointer, double latitude);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JNode_setLongitude(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble longitude) {
        if(nativePointer != 0 ) {
            ((Node*)nativePointer)->SetLongitude(longitude);
        }
    }
    // void JNode->setLevel(long nativePointer, int level);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JNode_setLevel(JNIEnv *env, jobject thiz, jlong nativePointer, jint level) {
        if(nativePointer != 0 ) {
            ((Node*)nativePointer)->SetLevel(level);
        }
    }
    // long JNode->getID(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JNode_getID(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return ((Node*)nativePointer)->GetID();
        }
        return -1;
    }
    // String JNode->getTag(long nativePointer);
    JNIEXPORT jstring JNICALL
    Java_com_ppapp_geograph3d_JNode_getTag(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            (*env)->NewStringUTF(env, ((Node*)nativePointer)->GetTag());
        }
        return (*env)->NewStringUTF(env, "");
    }
    // double JNode->getLatitude(long nativePointer);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JNode_getLatitude(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return ((Node*)nativePointer)->GetLatitude();
        }
        return 0.0;
    }
    // double JNode->getLongitude(long nativePointer);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JNode_getLongitude(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return ((Node*)nativePointer)->GetLongitude();
        }
        return 0.0;
    }
    // double JNode->getLevel(long nativePointer);
    JNIEXPORT jint JNICALL
    Java_com_ppapp_geograph3d_JNode_getLevel(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return ((Node*)nativePointer)->GetLevel();
        }
        return 0;
    }

    // MARK: JEdge
    
}