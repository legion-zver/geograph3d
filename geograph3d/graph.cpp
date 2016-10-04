//
//  graph.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "graph.hpp"

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

Node* Graph::GetNode(double latitude, double longitude, double level) {
    return this->GetNearestNode(latitude, longitude, level, 0.0);
}

Node* Graph::GetNearestNode(double latitude, double longitude, double level, double minRadius) {
    double minWeight = DBL_MAX;
    unsigned int minId = 0;
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        if(itN->second != NULL) {
            // Поиск только на одном уровне
            if(itN->second->GetLevel() == level) {
                if(minRadius > 0.0) {
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
    if(minWeight != DBL_MAX) {
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

const std::map<unsigned int, Node*>* Graph::GetNodes() {
    return &this->nodes;
}

unsigned long Graph::GetCountNodes() {
    return this->nodes.size();
}

Edge* Graph::GetEdge(unsigned int sourceId, unsigned int targetId, bool onlyForward) {
    bool backward = false;
    std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator v1 = this->edgesForward.find(sourceId);
    if(v1 == this->edgesForward.end()) {
        if(onlyForward) {
            return NULL;
        }
        v1 = this->edgesBackward.find(sourceId);
        if(v1 == this->edgesBackward.end()) {
            return NULL;
        }
        backward = true;
    }
    std::map<unsigned int, Edge*>::iterator v2 = v1->second.find(targetId);
    if(v2 == v1->second.end()) {
        if(backward || onlyForward) {
            return NULL;
        }
        v1 = this->edgesBackward.find(sourceId);
        if(v1 == this->edgesBackward.end()) {
            return NULL;
        }
        v2 = v1->second.find(targetId);
        if(v2 == v1->second.end()) {
            return NULL;
        }
    }
    return v2->second;
}

std::map<unsigned int, Edge*>* Graph::GetEdges(unsigned int sourceId, bool forward) {
    std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator v;
    if(forward) {
        v = this->edgesForward.find(sourceId);
        if(v == this->edgesForward.end()) {
            return NULL;
        }
    } else {
        v = this->edgesBackward.find(sourceId);
        if(v == this->edgesBackward.end()) {
            return NULL;
        }
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
    for(std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator it = this->edgesForward.begin(); it != this->edgesForward.end(); it++) {
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

Node* Graph::AddNode(unsigned int id, std::string tag, double latitude, double longitude, double level) {
    if(this->nodes.find(id) == this->nodes.end()) {
        Node* n = new Node(id, tag, latitude, longitude, level);
        this->nodes[id] = n;
        return n;
    }
    return NULL;
}

Node* Graph::AddNode(unsigned int id, double latitude, double longitude, double level) {
    if(this->nodes.find(id) == this->nodes.end()) {
        Node* n = new Node(id, latitude, longitude, level);
        this->nodes[id] = n;
        return n;
    }
    return NULL;
}

bool Graph::RemoveNode(unsigned int id) {
    std::map<unsigned int, Node*>::iterator itN = this->nodes.find(id);
    if(itN == this->nodes.end()) {
        return false;
    }
    if(itN->second == NULL) {
        return false;
    }
    this->RemoveEdgesContainNode(id);
    this->nodes.erase(itN);
    Node *node = itN->second;
    delete node;
    return true;
}

Edge* Graph::AddEdge(unsigned int sourceId, unsigned int targetId, bool biDistance) {
    Node* source = GetNode(sourceId);
    Node* target = GetNode(targetId);
    if(source != NULL && source != target) {
        Edge *edge = this->GetEdge(sourceId, targetId, !biDistance);
        if(edge == NULL) {
            edge = new Edge(source, target, biDistance);
            std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator it = this->edgesForward.find(sourceId);
            if(it == this->edgesForward.end()) {
                // Создаем
                std::map<unsigned int, Edge*> m;
                m[targetId] = edge;
                this->edgesForward[sourceId] = m;
            } else {
                it->second[targetId] = edge;
            }
            if(biDistance) {
                it = this->edgesBackward.find(targetId);
                if(it == this->edgesBackward.end()) {
                    // Создаем
                    std::map<unsigned int, Edge*> m;
                    m[sourceId] = edge;
                    this->edgesBackward[targetId] = m;
                } else {
                    it->second[sourceId] = edge;
                }
            }
        }
        return edge;
    }
    return NULL;
}

bool Graph::RemoveEdgesContainNode(unsigned int nodeId) {
    unsigned long countRemove = 0;
    //Проходимся по граням и удаляем все что связано с текущей нодой
    for(std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator itE = this->edgesForward.begin(); itE != this->edgesForward.end(); itE++) {
        bool remove = false;
        if(itE->first == nodeId) {
            remove = true;
        }
        for(std::map<unsigned int, Edge*>::iterator itES = itE->second.begin(); itES != itE->second.end(); itES++) {
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
            this->edgesForward.erase(itE);
        }
    }
    for(std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator itE = this->edgesBackward.begin(); itE != this->edgesBackward.end(); itE++) {
        bool remove = false;
        if(itE->first == nodeId) {
            remove = true;
        }
        for(std::map<unsigned int, Edge*>::iterator itES = itE->second.begin(); itES != itE->second.end(); itES++) {
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
            this->edgesBackward.erase(itE);
        }
    }
    if(countRemove > 0) {
        return true;
    }
    return false;
}

//MARK: Clear
void Graph::Clear() {
    for(std::map<unsigned int, std::map<unsigned int, Edge*>>::iterator itE = this->edgesForward.begin(); itE != this->edgesForward.end(); itE++) {
        for(std::map<unsigned int, Edge*>::iterator itES = itE->second.begin(); itES != itE->second.end(); itES++) {
            Edge* edge = itES->second;
            if(edge != NULL) {
                delete edge;
            }
        }
        itE->second.clear();
    }
    this->edgesForward.clear();
    this->edgesBackward.clear();
    for(std::map<unsigned int, Node*>::iterator itN = this->nodes.begin(); itN != this->nodes.end(); itN++) {
        Node* node = itN->second;
        if(node != NULL) {
            delete node;
        }
    }
    this->nodes.clear();
}
