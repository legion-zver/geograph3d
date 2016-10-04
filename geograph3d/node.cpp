//
//  node.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include "node.hpp"
#include <math.h>

using namespace GeoGraph3D;

// MARK: Constants
#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0

//MARK: Constructors

Node::Node(unsigned int _id) {
    this->id = _id;
}

Node::Node(unsigned int _id, std::string _tag, double _latitude, double _longitude, double _level) {
    this->id        = _id;
    this->tag       = _tag;
    this->latitude  = _latitude;
    this->longitude = _longitude;
    this->level     = _level;
}

Node::Node(unsigned int _id, double _latitude, double _longitude, double _level) {
    this->id        = _id;
    this->latitude  = _latitude;
    this->longitude = _longitude;
    this->level     = _level;
}

//MARK: Sets

void Node::SetTag(std::string _tag) { this->tag = _tag; }
void Node::SetLatitude(double _latitude) { this->latitude = _latitude; }
void Node::SetLongitude(double _longitude) { this->longitude = _longitude; }
void Node::SetLevel(double _level) { this->level = _level; }

//MARK: Gets

unsigned int Node::GetID() { return this->id; }
std::string Node::GetTag() { return this->tag; }
double Node::GetLatitude() { return this->latitude; }
double Node::GetLongitude() { return this->longitude; }
double Node::GetLevel() { return this->level; }

//MARK: Math

double degToRad(double deg) {
    return (deg * PI / 180.0f);
}

// geoDistance - расстояние между двумя GEO точками
double geoDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double lat1 = degToRad(latitude1);
    double lng1 = degToRad(longitude1);
    double lat2 = degToRad(latitude2);
    double lng2 = degToRad(longitude2);
    double d_lat = fabs(lat1 - lat2);
    double d_lng = fabs(lng1 - lng2);
    return EARTH_RADIUS_KM*(2 * asin(sqrt(pow(sin(d_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(d_lng / 2), 2))));
}

double Node::DistanceTo(Node* node) {
    if(node != NULL) {        
        return this->DistanceTo(node->GetLatitude(), node->GetLongitude(), node->GetLevel());
    }
    return -1.0f;
}

double Node::DistanceTo(double _latitude, double _longitude, double _level) {
    double d = geoDistance(this->latitude, this->longitude, _latitude, _longitude);
    return sqrt(pow(d, 2) + pow(fabs(this->level - _level), 2));
}

bool Node::CompareLocation(double _latitude, double _longitude) {
    return this->longitude == _longitude && this->latitude == _latitude;
}

Point Node::FindCrossTwoLines2D(Node* p0, Node* p1, Node* r0, Node* r1, bool duo) {
    Point result; result.empty = true;
    if(p0 != NULL && p1 != NULL && r0 != NULL && r1 != NULL) {
        double z1 = p1->GetLatitude() - p0->GetLatitude();
        double z2 = r1->GetLatitude() - r0->GetLatitude();
        double w1 = p1->GetLongitude() - p0->GetLongitude();
        double w2 = r1->GetLongitude() - r0->GetLongitude();
        double k = (z1*(r0->GetLongitude()-p0->GetLongitude())+w1*(p0->GetLatitude()-r0->GetLatitude()))/((w1*z2)-(z1*w2));
        double latitude = r0->GetLatitude()+(z2*k);
        double longitude = r0->GetLongitude()+(w2*k);
        if(!p0->CompareLocation(latitude, longitude) &&
           !p1->CompareLocation(latitude, longitude) &&
           !r0->CompareLocation(latitude, longitude) &&
           !r1->CompareLocation(latitude, longitude)) {
            if(Node::CheckPointInLine2D(latitude, longitude, p0, p1)) {
                if(!duo) {
                    result.latitude = latitude;
                    result.longitude = longitude;
                    result.empty = false;
                } else if(Node::CheckPointInLine2D(latitude, longitude, r0, r1)) {
                    result.latitude = latitude;
                    result.longitude = longitude;
                    result.empty = false;
                }
            }
        }
    }
    return result;
}

bool Node::CheckPointInLine2D(double latitude, double longitude, Node* p0, Node* p1) {
    if(p0 != NULL && p1 != NULL) {
        bool result;
        if(p0->GetLatitude() > p1->GetLatitude())
            result = (latitude >= p1->GetLatitude() && latitude <= p0->GetLatitude());
        else
            result = (latitude >= p0->GetLatitude() && latitude <= p1->GetLatitude());
        
        if(p0->GetLongitude() > p1->GetLongitude())
            return result && (longitude >= p1->GetLongitude() && longitude <= p0->GetLongitude());
        else
            return result && (longitude >= p0->GetLongitude() && longitude <= p1->GetLongitude());
    }
    return false;
}
