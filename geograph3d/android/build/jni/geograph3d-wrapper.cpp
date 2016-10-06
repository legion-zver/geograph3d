#include <string.h>
#include <jni.h>
#include <../include/geograph3d.hpp>

using namespace GeoGraph3D;

//extern "C" {
    // MARK: JNode
    // long JNode->createNode(long id, String tag, double latitude, double longitude, int level);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JNode_createNode(JNIEnv *env, jobject thiz, jlong id, jstring tag, jdouble latitude, jdouble longitude, jint level) {
        return (long)(new Node(id, env->GetStringUTFChars(tag, 0), latitude, longitude, level));
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
            ((Node*)nativePointer)->SetTag(env->GetStringUTFChars(tag, 0));
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
            return env->NewStringUTF(((Node*)nativePointer)->GetTag().c_str());
        }
        return env->NewStringUTF("");
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
    // long JEdge->createEdge(long nodeSourcePointer, long nodeTargetPointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JEdge_createEdge(JNIEnv *env, jobject thiz, jlong nodeSourcePointer, jlong nodeTargetPointer) {
        return (long)(new Edge((Node*)nodeSourcePointer, (Node*)nodeTargetPointer));
    }
    // long JEdge->getSourcePointer(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JEdge_getSourcePointer(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return (long)((Edge*)nativePointer)->GetSource();
        }
        return 0;
    }
    // long JEdge->getTargetPointer(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JEdge_getTargetPointer(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return (long)((Edge*)nativePointer)->GetTarget();
        }
        return 0;
    }
    // long JEdge->getFactor(long nativePointer, long id);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JEdge_getFactor(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id) {
        if(nativePointer != 0) {
            return ((Edge*)nativePointer)->GetFactor(id);
        }
        return 1.0;
    }
    // void JEdge->addFactor(long nativePointer, long id, double value);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JEdge_addFactor(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id, jdouble value) {
        if(nativePointer != 0) {
            ((Edge*)nativePointer)->AddFactor(id, value);
        }
    }
    // void JEdge->removeFactor(long nativePointer, long id);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JEdge_removeFactor(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id) {
        if(nativePointer != 0) {
            ((Edge*)nativePointer)->RemoveFactor(id);
        }
    }
    // long JEdge->getCountFactors(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JEdge_getCountFactors(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return ((Edge*)nativePointer)->GetCountFactors();
        }
        return 0;
    }
    // double JEdge->getWeight(long nativePointer, long factorID, double levelSize);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JEdge_getWeight(JNIEnv *env, jobject thiz, jlong nativePointer, jlong factorID, jdouble levelSize) {
        if(nativePointer != 0) {
            return ((Edge*)nativePointer)->GetWeight(factorID, levelSize);
        }
        return -1.0;
    }
    // JGraph

    // JRoads
    // long JRoads->createRoads();
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JRoads_createRoads(JNIEnv *env, jobject thiz) {
        return (long)(new Roads());
    }
    // void JRoads->destroyRoads(long nativePointer);
    JNIEXPORT void JNICALL 
    Java_com_ppapp_geograph3d_JRoads_destroyRoads(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            delete ((Roads*)nativePointer);            
        }
    }
    // void JRoads->clear(long nativePointer, boolean removeFromMemory);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JRoads_clear(JNIEnv *env, jobject thiz, jlong nativePointer, jboolean removeFromMemory) {
        if(nativePointer != 0) {
            ((Roads*)nativePointer)->Clear(removeFromMemory);
        }
    }
    // boolean JRoads->fillGraph(long nativePointer, long graphPointer);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JRoads_fillGraph(JNIEnv *env, jobject thiz, jlong nativePointer, jlong graphPointer) {
        if(nativePointer != 0 && graphPointer != 0) {
            return ((Roads*)nativePointer)->FillGraph((Graph*)graphPointer);
        }
        return false;
    }
    // boolean JRoads->addRoad(long nativePointer, ArrayList<JNode> nodes, int directionType);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JRoads_addRoad(JNIEnv *env, jobject thiz, jlong nativePointer, jobject nodes, jint directionType) {
        if(nativePointer != 0) {
            Roads *roads = (Roads*)nativePointer;
            std::vector<Node*> vNodes;
            //----
            jclass clazzArrayList = (*env).FindClass("java/util/ArrayList");
            jint size = env->CallIntMethod(nodes, env->GetMethodID(clazzArrayList, "size", "()I"));
            for(jint i=size-1; i>=0; i--) {
                jlong nodePtr = env->CallLongMethod(nodes, (*env).GetMethodID(clazzArrayList, "get","(I)J"), i);
                if(nodePtr != 0) {
                    vNodes.push_back((Node*)nodePtr);
                }
            }
            //----
            Direction direction;
            if(directionType == 0) {
                direction = Forward;
            } else if(directionType == 1) {
                direction = Backward;
            } else {
                direction = All;
            }
            return roads->AddRoad(vNodes, direction);           
        }
        return false;
    }
//}