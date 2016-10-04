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
    class Roads {
    public:
        // AddRoad - добавление дороги (списка точек)
        bool AddRoad(std::vector<Node*> road);
        // FillGraph - Заполняем граф из дорог
        bool FillGraph(Graph *graph);
        // Clear - очищаем списки дорог и пересечений
        void Clear(bool removeFromMemory);
    private:
        void FindCrossess();
        void ClearCrossess();
        unsigned int GetMaxNodeID();
    private:
        std::vector<std::vector<Node*>> roads;
        std::map<unsigned int, std::vector<unsigned int>> crossess;
    };
}

#endif /* roads_hpp */
