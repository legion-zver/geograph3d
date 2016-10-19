//
//  graph.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "graph.hpp"
#include <math.h>

using namespace GeoGraph3D;

//MARK: Gets
unsigned int Graph::GetMaxNodeID() {
    unsigned int maxId = 0;
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        if(itN->first > maxId) {
            maxId = itN->first;
        }
    }
    return maxId;
}

Node* Graph::GetNode(std::string tag) {
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        if(itN->second != NULL) {
            if(itN->second->GetTag() == tag) {
                return itN->second;
            }
        }
    }
    return NULL;
}

Node* Graph::GetNode(unsigned int id) {
    std::map<unsigned int, Node*>::iterator v = this->nodes.find(id);
    if(v != this->nodes.end()) {
        return v->second;
    }
    return NULL;
}

Node* Graph::GetNodeByIndex(unsigned int index) {
    if(index < this->nodes.size()) {
        std::map<unsigned int, Node*>::iterator v = this->nodes.begin();
        std::advance(v, index);
        if(v != this->nodes.end()) {
            return v->second;
        }
    }
    return NULL;
}

Node* Graph::GetNode(double latitude, double longitude, int level) {
    return this->GetNearestNode(latitude, longitude, level, -1.0);
}

Node* Graph::GetNearestNode(double latitude, double longitude, int level, double minRadius) {
    double minWeight = DBL_MAX;
    unsigned int minId = 0;
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        if(itN->second != NULL) {
            // Поиск только на одном уровне
            if(itN->second->GetLevel() == level) {
                if(minRadius >= 0.0) {
                    double w = itN->second->DistanceTo(latitude, longitude, longitude);
                    if (w >= minRadius) {
                        if(w < minWeight) {
                            minWeight = w;
                            minId = itN->first;
                        }
                    }
                } else {
                    if(itN->second->GetLatitude() == latitude && itN->second->GetLongitude() == longitude && itN->second->GetLevel() == level) {
                        minId = itN->first;
                        minWeight = 0;
                        break;
                    }
                }
            }
        }
    }
    if(minWeight < DBL_MAX-0.001) {
        return this->GetNode(minId);
    }
    return NULL;
}

Node* Graph::GetNearestNode(unsigned int id, double minRadius) {
    Node* node = this->GetNode(id);
    if(node != NULL) {
        double minWeight = DBL_MAX;
        unsigned int minId = id;
        for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
            if(itN->second != NULL) {
                if(itN->first != id) {
                    // Поиск только на одном уровне
                    if(itN->second->GetLevel() == node->GetLevel()) {
                        double w = itN->second->DistanceTo(node);
                        if (w >= minRadius) {
                            if(w < minWeight) {
                                minWeight = w;
                                minId = itN->first;
                            }
                        }
                    }
                }
            }
        }
        if(minId == id) {
            node = NULL;
        } else {
            node = this->GetNode(minId);
        }
    }
    return node;
}


Node* Graph::GenNewNearestNodeInEdges(unsigned int id, double latitude, double longitude, int level) {    
    Node* node = NULL;
    Edge* minEdge = NULL;
    double minDistance = DBL_MAX;
    Point crossPoint;
    
    // Поиск ближайшей точки на ребрах методом проекции
    for(std::map<unsigned int, MapEdges>::iterator it = this->edges.begin(); it != this->edges.end(); it++) {
        for(MapEdges::iterator itE = it->second.begin(); itE != it->second.end(); itE++) {
            if(itE->second != NULL) {
                Node* src = itE->second->GetSource();
                Node* target = itE->second->GetTarget();
                if(src != NULL && target != NULL) {
                    if(src->GetLevel() == level && target->GetLevel() == level) {
                        Point cross = Node::NearestPointOnLine2D(latitude, longitude, src, target);
                        if(!cross.empty) {
                            double distance = distance2D(latitude, longitude, cross.latitude, cross.longitude);
                            if(distance < minDistance) {
                                minDistance = distance;
                                crossPoint = cross;
                                minEdge = itE->second;
                            }
                        }
                    }
                }
            }
        }
    }    
    
    // Грань найдена
    if(minEdge != NULL) {
        // Теперь нужно встроить новую точку в эту грань и в обратную - для двойного пути
        Node* source = minEdge->GetSource();
        Node* target = minEdge->GetTarget();
        if(source != NULL && target != NULL) {
            minEdge = NULL; // Чтобы не налажать
            if(id == 0) {
                id = this->GetMaxNodeID()+1;
            }            
            node = this->AddNode(id, crossPoint.latitude, crossPoint.longitude, level);
            // Удаляем грани
            this->RemoveEdge(source->GetID(), target->GetID());
            this->RemoveEdge(target->GetID(), source->GetID());
            // Создаем новые грани
            this->AddEdge(source->GetID(), node->GetID());
            this->AddEdge(node->GetID(), source->GetID());
            this->AddEdge(node->GetID(), target->GetID());
            this->AddEdge(target->GetID(), node->GetID());
        }
    }
    return node;
}

const std::map<unsigned int, Node*>* Graph::GetNodes() {
    return &this->nodes;
}

unsigned long Graph::GetCountNodes() {
    return this->nodes.size();
}

std::vector<Edge*> Graph::FindEdgesForNode(unsigned int nodeId) {
    std::vector<Edge*> result;
    for(std::map<unsigned int, MapEdges>::iterator it = this->edges.begin(); it != this->edges.end(); it++) {
        for(MapEdges::iterator itE = it->second.begin(); itE != it->second.end(); itE++) {
            if(itE->second != NULL) {
                if(itE->second->HasNodeID(nodeId)) {
                    result.push_back(itE->second);
                }
            }
        }
    }
    return result;
}

Edge* Graph::GetEdge(unsigned int sourceId, unsigned int targetId, bool allDirections) {
    std::map<unsigned int, MapEdges>::iterator v1 = this->edges.find(sourceId);
    if(v1 == this->edges.end()) {
        v1 = this->edges.find(targetId);
        if(v1 == this->edges.end()) {
            if(!allDirections) {
                return NULL;
            }
            v1 = this->edges.find(sourceId);
            if(v1 == this->edges.end()) {
                v1 = this->edges.find(targetId);
                if(v1 == this->edges.end()) {
                    return NULL;
                }
            }
        }
    }
    MapEdges::iterator v2 = v1->second.find(targetId);
    if(v2 == v1->second.end()) {
        return NULL;
    }
    return v2->second;
}

MapEdges* Graph::GetEdges(unsigned int sourceId) {
    std::map<unsigned int, MapEdges>::iterator v = this->edges.find(sourceId);
    if(v == this->edges.end()) {
        return NULL;
    }
    return &v->second;
}

double Graph::GetWeight(unsigned int sourceId, unsigned int targetId, int factorId) {
    Edge *edge = this->GetEdge(sourceId, targetId);
    if(edge != NULL) {
        return edge->GetWeight(factorId);
    }
    return -1;
}

unsigned long Graph::GetCountEdges() {
    unsigned long count = 0;
    for(std::map<unsigned int, MapEdges>::iterator it = this->edges.begin(); it != this->edges.end(); it++) {
        count += it->second.size();
    }
    return count;
}

//MARK: Sets
void Graph::AddNode(Node* node) {
    if(node != NULL) {
        if(this->nodes.find(node->GetID()) == this->nodes.end()) {
            this->nodes[node->GetID()] = node;
        }
    }
}

Node* Graph::AddNode(unsigned int id, std::string tag, double latitude, double longitude, int level) {
    if(this->nodes.find(id) == this->nodes.end()) {
        Node* n = new Node(id, tag, latitude, longitude, level);
        this->nodes[id] = n;
        return n;
    }
    return NULL;
}

Node* Graph::AddNode(unsigned int id, double latitude, double longitude, int level) {
    if(this->nodes.find(id) == this->nodes.end()) {
        Node* n = new Node(id, latitude, longitude, level);
        this->nodes[id] = n;
        return n;
    }
    return NULL;
}

bool Graph::RemoveNode(unsigned int id, bool restoreBrokeEdges) {
    std::map<unsigned int, Node*>::iterator itN = this->nodes.find(id);
    if(itN == this->nodes.end()) {
        return false;
    }
    if(itN->second == NULL) {
        return false;
    }
    bool removeEdges = true;
    if(restoreBrokeEdges) {
        std::vector<Edge*> edges = FindEdgesForNode(id);
        size_t countEdges = edges.size();
        if(countEdges == 2 || countEdges == 4) {
            // Поиск двух других нод
            unsigned int nodeId1 = 0;
            unsigned int nodeId2 = 0;
            unsigned int tmpId = 0;
            for(int i=0; i < countEdges; i++) {
                if(edges[i] != NULL) {
                    if(nodeId1 == 0) {
                        tmpId = edges[i]->GetSecondID(id);
                        if(tmpId > 0) {
                            nodeId1 = tmpId;
                        }
                    } else if(nodeId2 == 0) {
                        tmpId = edges[i]->GetSecondID(id);
                        if(tmpId > 0 && tmpId != nodeId1) {
                            nodeId2 = tmpId;
                            break;
                        }
                    }
                }
            }
            if(nodeId1 != 0 && nodeId2 != 0) {
                
                // Удаляем наши ребра
                RemoveEdge(id, nodeId1);
                RemoveEdge(nodeId1, id);
                RemoveEdge(id, nodeId2);
                RemoveEdge(nodeId2, id);
                
                // Восстанавливаем связи
                AddEdge(nodeId1, nodeId2);
                AddEdge(nodeId2, nodeId1);
                
                removeEdges = false;
            }
        }
    }
    if(removeEdges)
        this->RemoveEdgesContainNode(id);
    
    this->nodes.erase(itN);
    Node *node = itN->second;
    delete node;
    return true;
}

Edge* Graph::AddEdge(unsigned int sourceId, unsigned int targetId) {
    Node* source = GetNode(sourceId);
    Node* target = GetNode(targetId);
    if(source != NULL && source != target) {
        Edge *edge = this->GetEdge(sourceId, targetId, false);
        if(edge == NULL) {
            edge = new Edge(source, target);
            std::map<unsigned int, MapEdges>::iterator it = this->edges.find(sourceId);
            if(it == this->edges.end()) {
                MapEdges m; m[targetId] = edge;
                this->edges[sourceId] = m;
            } else {
                it->second[targetId] = edge;
            }
        }
        return edge;
    }
    return NULL;
}

bool Graph::RemoveEdge(unsigned int sourceId, unsigned int targetId) {
    MapEdges::iterator it = this->edges[sourceId].find(targetId);
    if(it != this->edges[sourceId].end()) {
        Edge* edge = edges[sourceId][targetId];
        this->edges[sourceId].erase(it);
        if(this->edges[sourceId].size() < 1) {
            std::map<unsigned int, MapEdges>::iterator itM = this->edges.find(sourceId);
            if(itM != this->edges.end()) {
                this->edges.erase(itM);
            }
        }
        if(edge != NULL) {
            delete edge;
        }
        return true;
    }
    return false;
}

bool Graph::RemoveEdgesContainNode(unsigned int nodeId) {
    unsigned long countRemove = 0;
    //Проходимся по граням и удаляем все что связано с текущей нодой
    for(std::map<unsigned int, MapEdges>::iterator itE = this->edges.begin(); itE != this->edges.end(); itE++) {
        bool remove = false;
        if(itE->first == nodeId) {
            remove = true;
        }
        for(MapEdges::iterator itES = itE->second.begin(); itES != itE->second.end(); itES++) {
            if(remove) {
                if(itES->second != NULL) {
                    Edge* edge = itES->second;
                    delete edge;
                }
                itE->second.erase(itES);
                countRemove++;
            } else {
                if(itES->first == nodeId) {
                    if(itES->second != NULL) {
                        Edge* edge = itES->second;
                        delete edge;
                    }
                    itE->second.erase(itES);
                    countRemove++;
                }
            }
        }
        if(remove) {
            this->edges.erase(itE);
        }
    }
    if(countRemove > 0) {
        return true;
    }
    return false;
}

Node* Graph::AddNodeAndEdges(std::string tag, double latitude, double longitude, int level) {
    return this->AddNodeAndEdges(this->GetMaxNodeID()+1, tag, latitude, longitude, level);
}

Node* Graph::AddNodeAndEdges(unsigned int id, std::string tag, double latitude, double longitude, int level) {
    Node* nereast = this->GetNearestNode(latitude, longitude, level);
    if(nereast != NULL) {
        Node* node = this->AddNode(id, tag, latitude, longitude, level);
        if(node != NULL) {
            this->AddEdge(node->GetID(), nereast->GetID());
            this->AddEdge(nereast->GetID(), node->GetID());
            return node;
        }
    }
    return NULL;
}

//MARK: Clear
void Graph::Clear() {
    for(std::map<unsigned int, MapEdges>::iterator itE = this->edges.begin(); itE != this->edges.end(); itE++) {
        for(MapEdges::iterator itES = itE->second.begin(); itES != itE->second.end(); itES++) {
            Edge* edge = itES->second;
            if(edge != NULL) {
                delete edge;
            }
        }
        itE->second.clear();
    }
    this->edges.clear();    
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        Node* node = itN->second;
        if(node != NULL) {
            delete node;
        }
    }
    this->nodes.clear();
}
