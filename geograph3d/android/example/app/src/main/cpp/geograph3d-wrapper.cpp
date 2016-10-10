#include <string.h>
#include <jni.h>
#include "src/geograph3d.hpp"
#include <android/log.h>

#define LOGV(TAG,...) __android_log_print(ANDROID_LOG_VERBOSE, TAG,__VA_ARGS__)
#define LOGD(TAG,...) __android_log_print(ANDROID_LOG_DEBUG  , TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO   , TAG,__VA_ARGS__)
#define LOGW(TAG,...) __android_log_print(ANDROID_LOG_WARN   , TAG,__VA_ARGS__)
#define LOGE(TAG,...) __android_log_print(ANDROID_LOG_ERROR  , TAG,__VA_ARGS__)


using namespace GeoGraph3D;

extern "C" {
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
    // double JNode->distanceToII(long nativePointer, double latitude, double longitude, int level, double levelSize);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JNode_distanceToII(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude, jdouble longitude, jint level, jdouble levelSize) {
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
    // void JNode->destroyNode(long nativePointer);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JNode_destroyNode(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            delete ((Node*)nativePointer);
        }
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
    // void JEdge->destroyEdge(long nativePointer);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JEdge_destroyEdge(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            delete ((Edge*)nativePointer);
        }
    }

    // JGraph
    // long JGraph->createGraph();
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_createGraph(JNIEnv *env, jobject thiz) {
        return (long)(new Graph());
    }
    // void JGraph->destroyGraph(long nativePointer);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JGraph_destroyGraph(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            delete ((Graph*)nativePointer);            
        }
    }
    //long JGraph->getNearestNode(long nativePointer, long id, double minRadius);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNearestNode(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id, jdouble minRadius) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNearestNode(id, minRadius);
        }
        return 0;
    }
    //long JGraph->getNearestNodeII(long nativePointer, double latitude, double longitude, int level, double minRadius)
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNearestNodeII(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude, jdouble longitude, jint level, jdouble minRadius) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNearestNode(latitude, longitude, level, minRadius);
        }
        return 0;
    }
    // long JGraph->getNode(long nativePointer, long id);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNode(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNode(id);
        }
        return 0;
    }
    // long JGraph->getNodeII(long nativePointer, String tag);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNodeII(JNIEnv *env, jobject thiz, jlong nativePointer, jstring tag) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNode(env->GetStringUTFChars(tag, 0));
        }
        return 0;
    }
    // long JGraph->getNodeIII(long nativePointer, double latitude, double longitude, int level);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNodeIII(JNIEnv *env, jobject thiz, jlong nativePointer, jdouble latitude, jdouble longitude, jint level) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNode(latitude, longitude, level);
        }
        return 0;
    }
    // long JGraph->getMaxNodeID(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getMaxNodeID(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetMaxNodeID();
        }
        return 0;
    }
    // long JGraph->getNodeByIndex(long nativePointer, long index);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNodeByIndex(JNIEnv *env, jobject thiz, jlong nativePointer, jlong index) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetNodeByIndex(index);
        }
        return 0;
    }
    // long JGraph->getCountNodes(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getCountNodes(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetCountNodes();
        }
        return 0;
    }
    // long[] JGraph->getNodes(long nativePointer)
    JNIEXPORT jlongArray JNICALL
    Java_com_ppapp_geograph3d_JGraph_getNodes(JNIEnv *env, jobject thiz, jlong nativePointer) {
        unsigned long sizeList = 0;
        unsigned long fillSize = 0;
        jlong* createdList = NULL;
        if(nativePointer != 0) {
            const std::map<unsigned int, Node*>* map = ((Graph*)nativePointer)->GetNodes();
            if(map != 0) {
                sizeList = map->size();
                if(sizeList > 0) {
                    createdList = new jlong[sizeList];
                    for (std::map<unsigned int, Node *>::const_iterator itN = map->begin();
                         itN != map->end(); itN++) {
                        if(fillSize >= sizeList) {
                            break;
                        }
                        if (itN->second != 0) {
                            createdList[fillSize] = (jlong) itN->second;
                            fillSize++;
                        }
                    }
                }
            }
        }
        jlongArray result;
        if(createdList != NULL) {
            if(fillSize > 0) {
                result = env->NewLongArray((jsize)fillSize);
                env->SetLongArrayRegion(result, 0, (jsize)fillSize, createdList);
            } else {
                result = env->NewLongArray(0);
            }
            delete []createdList;
        } else {
            result = env->NewLongArray(0);
        }
        return result;
    }
    // long JGraph->getEdge(long nativePointer, long sourceId, long targetId, boolean allDirections);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getEdge(JNIEnv *env, jobject thiz, jlong nativePointer, jlong sourceId, jlong targetId, jboolean allDirections) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->GetEdge(sourceId, targetId, allDirections);
        }
        return 0;
    }
    // long[] JGraph->getEdges(long nativePointer, long sourceId);
    JNIEXPORT jlongArray JNICALL
    Java_com_ppapp_geograph3d_JGraph_getEdges(JNIEnv *env, jobject thiz, jlong nativePointer, jlong sourceId) {
        unsigned long sizeList = 0;
        unsigned long fillSize = 0;
        jlong* createdList = NULL;

        if(nativePointer != 0) {
            MapEdges* map = ((Graph*)nativePointer)->GetEdges((unsigned int)sourceId);
            if(map != 0) {
                sizeList = map->size();
                if(sizeList > 0) {
                    createdList = new jlong[sizeList];
                    for (MapEdges::iterator itE = map->begin(); itE != map->end(); itE++) {
                        if (itE->second != 0) {
                            if(fillSize >= sizeList) {
                                break;
                            }
                            if (itE->second != 0) {
                                createdList[fillSize] = (jlong) itE->second;
                                fillSize++;
                            }
                        }
                    }
                }
            }
        }
        jlongArray result;
        if(createdList != NULL) {
            if(fillSize > 0) {
                result = env->NewLongArray((jsize)fillSize);
                env->SetLongArrayRegion(result, 0, (jsize)fillSize, createdList);
            } else {
                result = env->NewLongArray(0);
            }
            delete []createdList;
        } else {
            result = env->NewLongArray(0);
        }
        return result;
    }
    // double JGraph->getWeight(long nativePointer, long sourceId, long targetId, long factorId);
    JNIEXPORT jdouble JNICALL
    Java_com_ppapp_geograph3d_JGraph_getWeight(JNIEnv *env, jobject thiz, jlong nativePointer, jlong sourceId, jlong targetId, jlong factorId) {
        if(nativePointer != 0) {
            return ((Graph*)nativePointer)->GetWeight((unsigned int)sourceId, (unsigned int)targetId, (int)factorId);
        }
        return -1.0;
    }
    // long JGraph->getCountEdges(long nativePointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_getCountEdges(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            return (jlong)((Graph*)nativePointer)->GetCountEdges();
        }
        return 0;
    }
    // void JGraph->addNode(long nativePointer, long nodePointer);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JGraph_addNode(JNIEnv *env, jobject thiz, jlong nativePointer, jlong nodePointer) {
        if(nativePointer != 0 && nodePointer != 0) {
            ((Graph*)nativePointer)->AddNode((Node*)nodePointer);
        }
    }
    // long JGraph->addNodeII(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_addNodeII(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id, jstring tag, jdouble latitude, jdouble longitude, jint level) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->AddNode((unsigned int)id, env->GetStringUTFChars(tag, 0), latitude, longitude, level);
        }
        return 0;
    }
    // boolean JGraph->removeNode(long nativePointer, long id);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JGraph_removeNode(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id) {
        if(nativePointer != 0) {
            return (jboolean)((Graph*)nativePointer)->RemoveNode((unsigned int)id);
        }
        return JNI_FALSE;
    }
    // long JGraph->addNodeAndEdges(long nativePointer, long id, String tag, double latitude, double longitude, int level);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_addNodeAndEdges(JNIEnv *env, jobject thiz, jlong nativePointer, jlong id, jstring tag, jdouble latitude, jdouble longitude, jint level) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->AddNodeAndEdges((unsigned int)id, env->GetStringUTFChars(tag, 0), latitude, longitude, level);
        }
        return 0;
    }
    // long JGraph->addEdge(long nativePointer, long sourceId, long targetId);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JGraph_addEdge(JNIEnv *env, jobject thiz, jlong nativePointer, jlong sourceId, jlong targetId) {
        if(nativePointer != 0) {
            return (long)((Graph*)nativePointer)->AddEdge((unsigned int)sourceId, (unsigned int)targetId);
        }
        return 0;
    }
    // boolean JGraph->removeEdgesContainNode(long nativePointer, long nodeId);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JGraph_removeEdgesContainNode(JNIEnv *env, jobject thiz, jlong nativePointer, jlong nodeId) {
        if(nativePointer != 0) {
            return (jboolean)((Graph*)nativePointer)->RemoveEdgesContainNode((unsigned int)nodeId);
        }
        return JNI_FALSE;
    }
    // void JGraph->clear(long nativePointer);
    JNIEXPORT void JNICALL
    Java_com_ppapp_geograph3d_JGraph_clear(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            ((Graph*)nativePointer)->Clear();
        }
    }

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
            return (jboolean)((Roads*)nativePointer)->FillGraph((Graph*)graphPointer);
        }
        return JNI_FALSE;
    }
    // boolean JRoads->addRoad(long nativePointer, ArrayList<JNode> nodes, int directionType);
    JNIEXPORT jboolean JNICALL
    Java_com_ppapp_geograph3d_JRoads_addRoad(JNIEnv *env, jobject thiz, jlong nativePointer, jlongArray nodes, jint directionType) {
        if(nativePointer != 0 && nodes != 0) {
            Roads *roads = (Roads*)nativePointer;
            std::vector<Node*> vNodes;
            //----
            jsize size = env->GetArrayLength(nodes);
            jlong* items = env->GetLongArrayElements(nodes, 0);
            if(items != 0) {
                for (jint i = size - 1; i >= 0; i--) {
                    if (items[i] != 0) {
                        vNodes.push_back((Node *) items[i]);
                    }
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
            return (jboolean)roads->AddRoad(vNodes, direction);
        }
        return JNI_FALSE;
    }

    // JDijkstra
    // long JDijkstra->createDijkstra(long graphPointer);
    JNIEXPORT jlong JNICALL
    Java_com_ppapp_geograph3d_JDijkstra_createDijkstra(JNIEnv *env, jobject thiz, jlong graphPointer) {
        return (long)(new DijkstraSearch((Graph*)graphPointer));
    }
    // void JDijkstra->destroyDijkstra(long nativePointer);
    JNIEXPORT void JNICALL 
    Java_com_ppapp_geograph3d_JDijkstra_destroyDijkstra(JNIEnv *env, jobject thiz, jlong nativePointer) {
        if(nativePointer != 0) {
            delete ((DijkstraSearch*)nativePointer);            
        }
    }
    // long[] findPath(long nativePointer, long fromId, long toId, long factorId, double levelSize);
    JNIEXPORT jlongArray JNICALL
    Java_com_ppapp_geograph3d_JDijkstra_findPath(JNIEnv *env, jobject thiz, jlong nativePointer, jlong fromId, jlong toId, jlong factorId, jdouble levelSize) {
        unsigned long sizeList = 0;
        unsigned long fillSize = 0;
        jlong* createdList = NULL;

        if(nativePointer != 0) {
            ResultPath pathData = ((DijkstraSearch*)nativePointer)->FindPath((unsigned int)fromId, (unsigned int)toId, (int)factorId, levelSize);
            if(!pathData.haveErrors) {
                sizeList = pathData.nodes.size();
                if(sizeList > 0) {
                    createdList = new jlong[sizeList];
                    for(long i=0; i<pathData.nodes.size(); i++) {
                        if(pathData.nodes[i] != 0) {
                            if(fillSize >= sizeList) {
                                break;
                            }
                            createdList[fillSize] = (jlong) pathData.nodes[i];
                            fillSize++;
                        }
                    }
                }
            }     
        }

        jlongArray result;
        if(createdList != NULL) {
            if(fillSize > 0) {
                result = env->NewLongArray((jsize)fillSize);
                env->SetLongArrayRegion(result, 0, (jsize)fillSize, createdList);
            } else {
                result = env->NewLongArray(0);
            }
            delete []createdList;
        } else {
            result = env->NewLongArray(0);
        }
        return result;
    }
}