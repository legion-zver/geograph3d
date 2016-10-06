//
//  search.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef search_hpp
#define search_hpp

#include "graph.hpp"
#include <vector>
#include <deque>

namespace GeoGraph3D {    
    struct NodeDistance {
        bool operator<(const NodeDistance &d) const { return distance < d.distance; }
        unsigned int id;
        double distance;
    };
    
    class NodeDistanceHeap {
    public:
        std::deque<NodeDistance> values;
        void Push(NodeDistance d);
        NodeDistance Pop();
        void Sort();
        void UpdateDistance(unsigned int id, double value);
    };
    
    struct ResultPath {
        std::vector<Node*> nodes;
        double             distance;
        bool               haveErrors;        
    };        
}

#endif /* search_hpp */
