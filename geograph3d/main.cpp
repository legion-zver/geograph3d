//
//  main.cpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#include <iostream>
#include "dijkstra.hpp"
#include "test_data.hpp"

using namespace GeoGraph3D;

int main(int argc, const char * argv[]) {
    
    Graph graph;        
    
    // Заполняем граф из примера картой дорог
    FillGraphExample01(&graph);
    
    // Добавляем переходы из примера
    AddTransitionsExample01(&graph);
    
    /*
    Roads roads;
    
    std::vector<Node*> road0;
    road0.push_back(new Node(1, 55.777147765134266, 37.65421418007463));
    road0.push_back(new Node(2, 55.77626678546183, 37.65548018272966));
    roads.AddRoad(road0);
    
    std::vector<Node*> road1;
    road1.push_back(new Node(3, 55.777037643764295, 37.654165900312364));
    road1.push_back(new Node(4, 55.777104018325915, 37.65446362551302));
    road1.push_back(new Node(5, 55.77650966027079, 37.65471038874239));
    road1.push_back(new Node(6, 55.77666202195603, 37.65536484774202));
    roads.AddRoad(road1);
    
    std::vector<Node*> road2;
    road2.push_back(new Node(7, 55.77628488798426, 37.655498958192766));
    road2.push_back(new Node(8, 55.77647798103372, 37.65542385634035));
    road2.push_back(new Node(9, 55.77638596024666, 37.6550912624225));
    road2.push_back(new Node(10, 55.776826451225254, 37.654490447603166));
    roads.AddRoad(road2);
    
    roads.FillGraph(&graph);
    */
    
    unsigned int myLocationId = graph.GetMaxNodeID()+1;
    
    // Берем наше положение и добавляем на него ноду
    graph.AddNode(myLocationId, "MyGeoPosition", 55.77667446707311, 37.65513002872467, 1); // Первый этаж

    // Проводим поиск ближайшей ноды для нашей гео позиции - для создания ребра
    Node* n = graph.GetNearestNode(myLocationId);
    if(n != NULL) {
        // Добавляем два ребра  
        graph.AddEdge(myLocationId, n->GetID());
        graph.AddEdge(n->GetID(), myLocationId);
        
        Node* to = graph.GetNearestNode(55.77661782674582, 37.65478943008929, 1); // Второй этаж;
        if(to != NULL) {
            // Проводим поиск
            DijkstraSearch alg(&graph);
            ResultPath result = alg.FindPath(myLocationId, to->GetID());
            if(result.haveErrors || result.nodes.size() < 2) {
                printf("Not find path. Sorry!\n");
                return -1;
            }
            
            printf("\nGeoJSON Path:\n{\"type\":\"Feature\",\"properties\":{\"stroke\":\"#FF0000\",\"stroke-width\":2,\"stroke-opacity\":1},\"geometry\":{\"type\":\"LineString\",\"coordinates\": [");
            
            // Выводим результат
            for(int i=0; i < result.nodes.size(); i++) {
                Node* n = result.nodes[i];
                if(n != NULL) {
                    if(i > 0) {
                        printf(",[%f, %f]", n->GetLongitude(), n->GetLatitude());
                    } else {
                        printf("[%f, %f]", n->GetLongitude(), n->GetLatitude());
                    }                    
                }
            }
            printf("]}}\n");
            //printf("\nDistance: %f km.\n", result.distance);
        }
    }
    // Очищаем граф
    graph.Clear();
    return 0;
}
