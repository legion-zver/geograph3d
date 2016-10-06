//
//  graph.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include "edge.hpp"

namespace GeoGraph3D {
    #define DBL_MAX 1.79769e+308
    
    // Граф
    class Graph {
    public:
        //MARK: Gets
        unsigned int GetMaxNodeID();
        Node* GetNode(double latitude, double longitude, int level);     // Получить ноду по GEO позиции
        Node* GetNode(unsigned int id);                                     // Получить ноду по ID
        Node* GetNode(std::string tag);                                     // Получить ноду по тегу
        Node* GetNearestNode(double latitude, double longitude, int level, double minRadius = 0.0);
        Node* GetNearestNode(unsigned int id, double minRadius = 0.0);      // Получить ближайщую ноду для ноды с ID (с учетом минимального радиуса поиска)
        Node* GetNodeByIndex(unsigned int index);
        const std::map<unsigned int, Node*>* GetNodes();
        
        unsigned long GetCountNodes();
        Edge* GetEdge(unsigned int sourceId, unsigned int targetId, bool allDirections = true);
        std::map<unsigned int, Edge*>* GetEdges(unsigned int sourceId);
        double GetWeight(unsigned int sourceId, unsigned int targetId, int factorId = -1);
        unsigned long GetCountEdges();
        
        //MARK: Sets
        void  AddNode(Node* node);
        Node* AddNode(unsigned int id, std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        Node* AddNode(unsigned int id, double latitude = 0.0, double longitude = 0.0, int level = 0);
        
        bool RemoveNode(unsigned int id);        
        
        //
        Node* AddNodeAndEdges(std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        Node* AddNodeAndEdges(unsigned int id, std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        
        /*
         AddEdge - добавляем ребро графа
         - sourceId - начало (нода)
         - targetId - конец (нода)
         */
        
        Edge* AddEdge(unsigned int sourceId, unsigned int targetId);
        
        bool RemoveEdgesContainNode(unsigned int nodeId);
        
        //MARK: Clear
        void Clear();
        
    private:
        std::map<unsigned int, Node*> nodes;                                  // ноды графа
        std::map<unsigned int, std::map<unsigned int, Edge*>> edges;          // ребра между нодами
    };
};

#endif /* graph_hpp */
