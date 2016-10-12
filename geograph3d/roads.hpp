//
//  roads.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 01.10.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef roads_hpp
#define roads_hpp

#include "graph.hpp"
#include <vector>

namespace GeoGraph3D {
    
    enum Direction {
        Forward,
        Backward,
        All
    };
    
    // Для более правильной сборки под Android
    typedef std::vector<unsigned int> IntArray;
    
    // Для внутреннего хранения
    struct Road {
        std::vector<Node*> nodes;
        Direction direction;
    };
    
    class Roads {
    public:
        // AddRoad - добавление дороги (списка точек)
        bool AddRoad(std::vector<Node*> nodes, Direction direction = All);
        // FillGraph - Заполняем граф из дорог
        bool FillGraph(Graph *graph);
        // Clear - очищаем списки дорог и пересечений
        void Clear(bool removeFromMemory);
    private:        
        void FindCrossess();
        void ClearCrossess();
        unsigned int GetMaxNodeID();
    private:
        std::vector<Road> roads;
        std::map<unsigned int, IntArray> crossess;
    };
}

#endif /* roads_hpp */
