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
#include <vector>

namespace GeoGraph3D {

#ifndef DBL_MAX
    #define DBL_MAX 1.79769e+308
#endif
    
    // Для более правильной сборки под Android
    typedef std::map<unsigned int, Edge*> MapEdges;
    
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
        
        // Генерируем новую ноду которая лежит на любой грани графа
        Node* GenNewNearestNodeInEdges(unsigned int id, double latitude, double longitude, int level);
        
        Node* GetNodeByIndex(unsigned int index);
        const std::map<unsigned int, Node*>* GetNodes();
        
        unsigned long GetCountNodes();
        Edge* GetEdge(unsigned int sourceId, unsigned int targetId, bool allDirections = true);
        MapEdges* GetEdges(unsigned int sourceId);
        
        // FindEdgesForNode - поиск всех связей в котрых присутсвует нода с ID
        std::vector<Edge*> FindEdgesForNode(unsigned int nodeId);
        
        double GetWeight(unsigned int sourceId, unsigned int targetId, int factorId = -1);
        unsigned long GetCountEdges();
        
        //MARK: Sets
        void  AddNode(Node* node);
        Node* AddNode(unsigned int id, std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        Node* AddNode(unsigned int id, double latitude = 0.0, double longitude = 0.0, int level = 0);
        
        bool RemoveNode(unsigned int id, bool restoreBrokeEdges = false);        
        
        //
        Node* AddNodeAndEdges(std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        Node* AddNodeAndEdges(unsigned int id, std::string tag, double latitude = 0.0, double longitude = 0.0, int level = 0);
        
        /*
         AddEdge - добавляем ребро графа
         - sourceId - начало (нода)
         - targetId - конец (нода)
         */
        
        Edge* AddEdge(unsigned int sourceId, unsigned int targetId);
        
        // RemoveEdge - удаляет грань из графа, а также из памяти
        bool RemoveEdge(unsigned int sourceId, unsigned int targetId);
        
        // RemoveEdgesContainNode - удаляем все грани в которых есть нода
        bool RemoveEdgesContainNode(unsigned int nodeId);
        
        //MARK: Clear
        void Clear();
        
    private:
        std::map<unsigned int, Node*> nodes;             // ноды графа
        std::map<unsigned int, MapEdges> edges;          // ребра между нодами
    };
};

#endif /* graph_hpp */
