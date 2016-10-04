//
//  roads.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 01.10.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "roads.hpp"

using namespace GeoGraph3D;

bool Roads::AddRoad(std::vector<Node*> road) {
    if(road.size() > 1) {
        this->roads.push_back(road);
        return true;
    }
    return false;
}

bool Roads::FillGraph(Graph *graph) {
    if(graph != NULL) {
        graph->Clear();
        this->FindCrossess();        
        unsigned long countRoads = this->roads.size();
        for(unsigned long i = 0; i < countRoads; i++) {
            Node* p0 = NULL; Node* p1 = NULL;
            unsigned long countPoints = this->roads[i].size();
            for(unsigned long ip = 0; ip < countPoints; ip++) {
                if(p0 != NULL) {
                    p1 = this->roads[i][ip];
                    // Добавляем в граф ноды и создаем ребра
                    graph->AddNode(p1);
                    graph->AddEdge(p0->GetID(), p1->GetID());
                    p0 = p1;
                } else {
                    p0 = this->roads[i][ip];
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
        for(std::vector<std::vector<Node*>>::iterator itR = this->roads.begin(); itR != this->roads.end(); itR++) {
            for(unsigned long i=0; i< itR->size(); i++) {
                Node* node = itR->at(i);
                if(node != NULL) {
                    if(node->GetID() == itCr->first) {
                        if(forRemove == NULL) {
                            forRemove = node;
                        }
                        itR->erase(itR->begin()+i);
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
        unsigned long countPoints = this->roads[i].size();
        for(unsigned long ip = 0; ip < countPoints; ip++) {
            Node* tmp = this->roads[i][ip];
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
        unsigned long countPoints = this->roads[i].size();
        Node* p0 = NULL; Node* p1 = NULL; Node* r0 = NULL; Node* r1 = NULL;
        for(unsigned long ip = 0; ip < countPoints; ip++) {
            if(p0 != NULL) {
                p1 = this->roads[i][ip];
                // Перебор дорог и сравнение
                for(unsigned long j = 0; j < countRoads; j++) {
                    if(i != j) {
                        unsigned long countRayPoints = this->roads[j].size();
                        for(unsigned long ir = 0; ir < countRayPoints; ir++) {
                            if(r0 != NULL) {
                                r1 = this->roads[j][ir];
                                
                                // Поиск точки пересечения
                                Point cross = Node::FindCrossTwoLines2D(p0, p1, r0, r1);
                                if(!cross.empty) {
                                    // Проверяем схожесть этажа
                                    if((p0->GetLevel() == r0->GetLevel() && p1->GetLevel() == r1->GetLevel()) ||
                                       (p1->GetLevel() == r0->GetLevel() && p0->GetLevel() == r1->GetLevel())) {
                                        
                                        double level = (p0->GetLevel() + p1->GetLevel() + r0->GetLevel() + r1->GetLevel())/4;
                                        // Если пересечение найдено, тогда формируем точку пересечения и меняем дороги
                                        Node *newNode = new Node(crossId, cross.latitude, cross.longitude, level);
                                        if(newNode != NULL) {
                                            std::vector<unsigned int> crossList;
                                            crossList.push_back(p0->GetID());
                                            crossList.push_back(r0->GetID());
                                            crossList.push_back(p1->GetID());
                                            crossList.push_back(r1->GetID());
                                            this->crossess[(unsigned int)crossId] = crossList;
                                            this->roads[i].insert(this->roads[i].begin()+ip, newNode);
                                            this->roads[j].insert(this->roads[j].begin()+ir, newNode);
                                            ir++; ip++;
                                            crossId++;
                                        }
                                    }
                                }
                                r0 = r1;
                            } else {
                                r0 = this->roads[j][ir];
                            }
                        }
                    }
                }
                p0 = p1;
            } else {
                p0 = this->roads[i][ip];
            }
        }
    }
}
