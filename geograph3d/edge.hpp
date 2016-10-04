//
//  edge.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef edge_hpp
#define edge_hpp

#include "node.hpp"
#include <map>

namespace GeoGraph3D {
    // Ребро графа
    class Edge {
    public:
        //MARK: Constructors
        Edge(Node* _source, Node* _target, bool _biDirectional = true);
        
        //MARK: Change
        void AddFactor(unsigned int id, double value);
        void RemoveFactor(unsigned int id);
        
        //MARK: Gets
        Node*   GetSource();
        Node*   GetTarget();
        bool    IsBiDirectional();
        double  GetFactor(unsigned int id);
        unsigned long GetCountFactors();
        double  GetWeight(int factorID = -1);
        
    private:
        Node* source; // Нода источник
        Node* target; // Нода цель
        
        bool biDirectional; // Флаг двунаправленности, по умолчанию true
        
        // Факторы влияющие на прохождение
        std::map<unsigned int, double> factors;
    };
}

#endif /* edge_hpp */
