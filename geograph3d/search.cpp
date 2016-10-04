//
//  search.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "search.hpp"

using namespace GeoGraph3D;

// Сортировка
void NodeDistanceHeap::Sort() {
    std::sort(this->values.begin(), this->values.end());
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
