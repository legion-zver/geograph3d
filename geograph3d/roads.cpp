//
//  roads.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 01.10.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "roads.hpp"

using namespace GeoGraph3D;

//#define DEBUG_CROSS
//#define DEBUG_ROADS

bool Roads::AddRoad(std::vector<Node*> nodes, Direction direction) {
    if(nodes.size() > 1) {
        Road newRoad;
        newRoad.nodes = nodes;
        newRoad.direction = direction;
        this->roads.push_back(newRoad);
        return true;
    }
    return false;
}

bool Roads::FillGraph(Graph *graph) {
    if(graph != NULL) {
        graph->Clear();
        
        this->FindCrossess();
        
#ifdef DEBUG_ROADS
        for(unsigned long i = 0; i < this->roads.size(); i++) {
            Node* p0 = NULL; Node* p1 = NULL;
            printf("{\"type\":\"Feature\",\"properties\":{\"id\":%lu},\"geometry\":{\"type\":\"LineString\",\"coordinates\":[", i);
            for(unsigned long ip = 0; ip < this->roads[i].nodes.size(); ip++) {
                if(p0 != NULL) {
                    p1 = this->roads[i].nodes[ip];
                    printf(",[%f, %f]", p1->GetLongitude(), p1->GetLatitude());
                    p0 = p1;
                } else {
                    p0 = this->roads[i].nodes[ip];
                    printf("[%f, %f]", p0->GetLongitude(), p0->GetLatitude());
                }
            }
            printf("]}},\n");
        }
#endif
        
        unsigned long countRoads = this->roads.size();
        for(unsigned long i = 0; i < countRoads; i++) {
            Node* p0 = NULL; Node* p1 = NULL;
            unsigned long countPoints = this->roads[i].nodes.size();
            for(unsigned long ip = 0; ip < countPoints; ip++) {
                if(p0 != NULL) {
                    p1 = this->roads[i].nodes[ip];
                    // Добавляем в граф ноды и создаем ребра
                    graph->AddNode(p1);
                    if(this->roads[i].direction == All || this->roads[i].direction == Forward) {
                        graph->AddEdge(p0->GetID(), p1->GetID());
                    }
                    if(this->roads[i].direction == All || this->roads[i].direction == Backward) {
                        graph->AddEdge(p1->GetID(), p0->GetID());
                    }
                    p0 = p1;
                } else {
                    p0 = this->roads[i].nodes[ip];
                    graph->AddNode(p0);
                }
            }
        }
        // Как только закончили добавлять дороги, добавляем ребра пересечений
        for(std::map<unsigned int, std::vector<unsigned int>>::iterator itCr = this->crossess.begin(); itCr != this->crossess.end();  itCr++) {
            unsigned long count = itCr->second.size();
            for(unsigned long i=0; i < count; i++) {
                graph->AddEdge(itCr->first, itCr->second[i]);
            }
        }
        return true;
    }
    return false;
}

void Roads::Clear(bool removeFromMemory) {
    if(removeFromMemory) {
        this->ClearCrossess();
    } else {
        this->crossess.clear();
    }
    this->roads.clear();
}

void Roads::ClearCrossess() {
    for(std::map<unsigned int, std::vector<unsigned int>>::iterator itCr = this->crossess.begin(); itCr != this->crossess.end();  itCr++) {
        Node* forRemove = NULL;
        for(std::vector<Road>::iterator itR = this->roads.begin(); itR != this->roads.end(); itR++) {
            for(unsigned long i=0; i< itR->nodes.size(); i++) {
                Node* node = itR->nodes.at(i);
                if(node != NULL) {
                    if(node->GetID() == itCr->first) {
                        if(forRemove == NULL) {
                            forRemove = node;
                        }
                        itR->nodes.erase(itR->nodes.begin()+i);
                        break;
                    }
                }
            }
        }
        if(forRemove != NULL) {
            delete forRemove;
        }
    }
    this->crossess.clear();
}

unsigned int Roads::GetMaxNodeID() {
    unsigned int maxId = 0;
    unsigned long countRoads = this->roads.size();
    for(unsigned long i = 0; i < countRoads; i++) {
        unsigned long countPoints = this->roads[i].nodes.size();
        for(unsigned long ip = 0; ip < countPoints; ip++) {
            Node* tmp = this->roads[i].nodes[ip];
            if(tmp != NULL) {
                if(tmp->GetID() > maxId) {
                    maxId = tmp->GetID();
                }
            }
        }
    }
    return maxId;
}

void Roads::FindCrossess() {
    // Откат пересечений
    this->ClearCrossess();
    
    // Расчет ID пересечений
    unsigned int crossId = 1024 + this->GetMaxNodeID()+1;
    
    // Перебор всех отрезков и поиск пересечений
    unsigned long countRoads = this->roads.size();
    for(unsigned long i = 0; i < countRoads; i++) {
        Node* p0 = NULL; Node* p1 = NULL; Node* r0 = NULL; Node* r1 = NULL;
        for(unsigned long ip = 0; ip < this->roads[i].nodes.size(); ip++) {
            if(p0 != NULL) {
                p1 = this->roads[i].nodes[ip];
                // Перебор дорог и сравнение
                for(unsigned long j = 0; j < countRoads; j++) {
                    if(i != j) {
                        for(unsigned long ir = 0; ir < this->roads[j].nodes.size(); ir++) {
                            if(r0 != NULL) {
                                r1 = this->roads[j].nodes[ir];
                                // Проверяем схожесть этажа
                                if(p0->GetLevel() == r0->GetLevel() &&
                                   p1->GetLevel() == r1->GetLevel() &&
                                   p0->GetLevel() == r1->GetLevel()) {
                                    // Поиск точки пересечения
                                    Point cross = Node::FindCrossTwoLines2D(p0, p1, r0, r1);
                                    if(!cross.empty) {
                                        // Если пересечение найдено, тогда формируем точку пересечения и меняем дороги
                                        Node *newNode = new Node(crossId, cross.latitude, cross.longitude, p0->GetLevel());
                                        if(newNode != NULL) {
                                            
#ifdef DEBUG_CROSS
                                            printf("{\"type\":\"Feature\",\"properties\":{\"marker-color\":\"#AA00BB\",\"marker-size\":\"small\",\"id\":%d, \"t-t\":\"%lu - %lu\"},\"geometry\":{\"type\":\"Point\",\"coordinates\":[%f,%f]}},\n", crossId, i, j, cross.longitude, cross.latitude);
#endif
                                            
                                            std::vector<unsigned int> crossList;
                                            
                                            // Добавляем связи точки пересечения
                                            crossList.push_back(p0->GetID());
                                            crossList.push_back(r0->GetID());
                                            crossList.push_back(p1->GetID());
                                            crossList.push_back(r1->GetID());
                                            
                                            this->crossess[(unsigned int)crossId] = crossList;
                                            
                                            this->roads[i].nodes.insert(this->roads[i].nodes.begin()+ip, newNode);
                                            this->roads[j].nodes.insert(this->roads[j].nodes.begin()+ir, newNode);
                                            crossId++;
                                            p1 = newNode;
                                            //ir++;
                                        }
                                    }
                                }
                                r0 = r1;
                            } else {
                                r0 = this->roads[j].nodes[ir];
                            }
                        }
                        r0 = NULL; r1 = NULL;
                    }
                }
                p0 = p1;
            } else {
                p0 = this->roads[i].nodes[ip];
            }
        }
    }
}
