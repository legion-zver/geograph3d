//
//  edge.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "edge.hpp"

using namespace GeoGraph3D;

//MARK: Constructors

Edge::Edge(Node* _source, Node* _target) {
    this->source = _source;
    this->target = _target;
}

//MARK: Change

void Edge::AddFactor(unsigned int id, double value) {
    this->factors[id] = value;
}

void Edge::RemoveFactor(unsigned int id) {
    std::map<unsigned int,double>::iterator v = this->factors.find(id);
    if(v != this->factors.end()) {
        this->factors.erase(v);
    }
}

//MARK: Gets

Node* Edge::GetSource() { return this->source; }

Node* Edge::GetTarget() { return this->target; }

double Edge::GetFactor(unsigned int id) { return this->factors[id]; }

unsigned long Edge::GetCountFactors() { return this->factors.size(); }

double Edge::GetWeight(int factorID, double levelSize) {
    if(this->source != NULL && this->target != NULL) {
        double f = 1.0f;
        if(factorID >= 0) {
            std::map<unsigned int,double>::iterator v = this->factors.find(factorID);
            if(v != this->factors.end()) {
                f = v->second;
            }
        }
        double distance = this->source->DistanceTo(this->target, levelSize);
        if(distance >= 0.0) {
            return distance*f;
        }
    }
    return -1.0;
}

bool Edge::HasNodeID(unsigned int nodeId) {
    if(source != NULL) {
        if(source->GetID() == nodeId) {
            return true;
        }
    }
    if(target != NULL) {
        if(target->GetID() == nodeId) {
            return true;
        }
    }
    return false;
}

unsigned int Edge::GetSecondID(unsigned int firstId) {
    if(HasNodeID(firstId)) {
        if(source != NULL) {
            if(source->GetID() != firstId) {
                return source->GetID();
            }
        }
        if(target != NULL) {
            if(target->GetID() != firstId) {
                return target->GetID();
            }
        }
    }
    return 0;
}
