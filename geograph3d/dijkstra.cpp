//
//  dijkstra.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "dijkstra.hpp"

using namespace GeoGraph3D;

DijkstraSearch::DijkstraSearch(Graph* _graph) {
    this->graph = _graph;
}


ResultPath DijkstraSearch::FindPath(unsigned int sourceId, unsigned int targetId, int factorId, double levelSize) {
    ResultPath result;
    result.haveErrors = true;
    if(this->graph != NULL) {
        NodeDistanceHeap minHeap;
        std::map<unsigned int, double> distance;
        distance[sourceId] = 0.0;
        
        const std::map<unsigned int, Node*>* nodes = this->graph->GetNodes();
        if(nodes != NULL) {
            for(std::map<unsigned int, Node*>::const_iterator itN = nodes->begin(); itN != nodes->end(); itN++) {
                if(itN->second != NULL) {
                    unsigned int id = itN->second->GetID();
                    if(id != sourceId) {
                        distance[id] = DBL_MAX;
                    }
                    NodeDistance nds;
                    nds.id = id;
                    nds.distance = distance[id];
                    minHeap.Push(nds);
                }
            }
            minHeap.Sort();
            std::map<unsigned int, Node*> prev;
            while(minHeap.values.size() != 0) {
                NodeDistance u = minHeap.Pop();
                if(u.id == targetId) {
                    break;
                }
                std::map<unsigned int, Edge*>* cmap = this->graph->GetEdges(u.id);
                if(cmap != NULL) {
                    for(std::map<unsigned int, Edge*>::const_iterator itE = cmap->begin(); itE != cmap->end(); itE++) {
                        if(itE->second != NULL) {
                            double weight = itE->second->GetWeight(factorId, levelSize);
                            if(weight < 0) {
                                break;
                            }
                            double alt = distance[u.id] + weight;
                            unsigned int tid = itE->first;
                            if(distance[tid] > alt) {
                                distance[tid] = alt;
                                if(tid != itE->second->GetSource()->GetID()) {
                                    prev[tid] = itE->second->GetSource();
                                }
                                minHeap.UpdateDistance(tid, alt);
                            }
                        }
                    }
                    minHeap.Sort();
                }
            }
            double uId = targetId;
            result.distance = 0.0;
            Node* lastNode = this->graph->GetNode(uId);
            if(lastNode != NULL) {
                result.nodes.insert(result.nodes.begin(), lastNode);
            }
            while(1) {
                std::map<unsigned int, Node*>::iterator itP = prev.find(uId);
                if(itP == prev.end()) {
                    break;
                }
                if(lastNode != NULL) {
                    double distance = this->graph->GetWeight(itP->second->GetID(), lastNode->GetID(), factorId);
                    if(distance > 0) {
                        result.distance += distance;
                    }
                }
                result.nodes.insert(result.nodes.begin(), itP->second);
                uId = itP->second->GetID();
                lastNode = itP->second;
            }
            result.haveErrors = false;
        }
    }
    return result;
}
