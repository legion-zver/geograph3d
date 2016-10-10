//
//  search.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "search.hpp"
#include <algorithm>

using namespace GeoGraph3D;

// Функция сравнения
/*
static bool nodeDistanceCompare(const NodeDistance &d1, const NodeDistance &d2) {
    return d1.distance < d2.distance;
}
*/

// Сортировка
void NodeDistanceHeap::Sort() {
    std::sort(this->values.begin(), this->values.end());//, nodeDistanceCompare);
}

void NodeDistanceHeap::Push(NodeDistance d) {
    this->values.push_back(d);
}

NodeDistance NodeDistanceHeap::Pop() {
    NodeDistance first = this->values.front();
    this->values.pop_front();
    return first;
}

void NodeDistanceHeap::UpdateDistance(unsigned int id, double value) {
    for(unsigned long i = 0; i < this->values.size(); i++) {
        if(this->values[i].id == id) {
            this->values[i].distance = value;
            break;
        }
    }
}
