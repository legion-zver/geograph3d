//
//  dijkstra.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef dijkstra_hpp
#define dijkstra_hpp

#include "search.hpp"

namespace GeoGraph3D {
    // Поиск
    class DijkstraSearch {
    public:
        DijkstraSearch(Graph* _graph);
        ResultPath FindPath(unsigned int fromId, unsigned int toId, int factorId = -1, double levelSize = 0.03);

    private:
        Graph* graph;
    };
}

#endif /* dijkstra_hpp */
