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

// MARK: MATH GLOBAL
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

double distance2D(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x1-x0, 2)+pow(y1-y0, 2));
}

bool checkPointInLineGeo(double lat0, double lng0, double lat1, double lng1, double lat2, double lng2) {
    bool result;
    if(lat1 > lat2)
        result = (lat0 >= lat2 && lat0 <= lat1);
    else
        result = (lat0 >= lat1 && lat0 <= lat2);
    
    if(lng1 > lng2)
        return result && (lng0 >= lng2 && lng0 <= lng1);
    else
        return result && (lng0 >= lng1 && lng0 <= lng2);
}

//MARK: Constructors

Node::Node(unsigned int _id) {
    this->id = _id;
}

Node::Node(unsigned int _id, std::string _tag, double _latitude, double _longitude, int _level) {
    this->id        = _id;
    this->tag       = _tag;
    this->latitude  = _latitude;
    this->longitude = _longitude;
    this->level     = _level;
}

Node::Node(unsigned int _id, double _latitude, double _longitude, int _level) {
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
int Node::GetLevel() { return this->level; }

/*
Point Node::GetPoint() {
    Point result;
    result.latitude = this->latitude;
    result.longitude = this->longitude;
    return result;
}
*/

//MARK: Math

double Node::DistanceTo(Node* node, double _levelSize) {
    if(node != NULL) {        
        return this->DistanceTo(node->GetLatitude(), node->GetLongitude(), node->GetLevel(), _levelSize);
    }
    return -1.0f;
}

double Node::DistanceTo(double _latitude, double _longitude, int _level, double _levelSize) {
    double d = geoDistance(this->latitude, this->longitude, _latitude, _longitude);
    return sqrt(pow(d, 2) + pow(fabs((this->level - _level)*_levelSize), 2));
}

bool Node::CompareLocation(double _latitude, double _longitude) {
    return this->longitude == _longitude && this->latitude == _latitude;
}

Point Node::FindCrossTwoRays2D(Ray* ray, Node* r0, Node* r1, bool duo) {
    Point result; result.empty = true;
    if(ray != NULL && r0 != NULL && r1 != NULL) {
        double z1 = ray->p1.latitude - ray->p0.latitude;
        double z2 = r1->GetLatitude() - r0->GetLatitude();
        double w1 = ray->p1.longitude - ray->p0.longitude;
        double w2 = r1->GetLongitude() - r0->GetLongitude();
        double k = (z1*(r0->GetLongitude()-ray->p0.longitude)+w1*(ray->p0.latitude-r0->GetLatitude()))/((w1*z2)-(z1*w2));
        double latitude = r0->GetLatitude()+(z2*k);
        double longitude = r0->GetLongitude()+(w2*k);
        if(!(ray->p0.latitude == latitude && ray->p0.longitude == longitude) &&
           !(ray->p1.latitude == latitude && ray->p1.longitude == longitude) &&
           !r0->CompareLocation(latitude, longitude) &&
           !r1->CompareLocation(latitude, longitude)) {
            if(checkPointInLineGeo(latitude, longitude, ray->p0.latitude,ray->p0.longitude,ray->p1.latitude,ray->p1.longitude)) {
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
        return checkPointInLineGeo(latitude, longitude, p0->GetLatitude(), p0->GetLongitude(), p1->GetLatitude(), p1->GetLongitude());
    }
    return false;
}

Point Node::NearestPointOnLine2D(double latitude, double longitude, Node* p0, Node* p1, bool clampToSegment) {
    Point result; result.empty = true;
    if(p0 != NULL && p1 != NULL) {
        if(p0->GetLevel() == p1->GetLevel()) {
            double apx = latitude - p0->GetLatitude();
            double apy = longitude - p0->GetLongitude();
            double abx = p1->GetLatitude() - p0->GetLatitude();
            double aby = p1->GetLongitude() - p0->GetLongitude();
            double ab2 = abx*abx + aby*aby;
            double ap_ab = apx*abx + apy*aby;
            double t = ap_ab / ab2;
            if (clampToSegment) {
                if (t < 0) {
                    t = 0;
                } else if (t > 1) {
                    t = 1;
                }
            }
            result.latitude = p0->GetLatitude() + abx*t;
            result.longitude = p0->GetLongitude() + aby*t;
            result.empty = false;
        }
    }
    return result;
}
