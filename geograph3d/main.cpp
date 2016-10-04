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
    
    unsigned int myLocationId = graph.GetMaxNodeID()+1;
    
    // Берем наше положение и добавляем на него ноду
    graph.AddNode(myLocationId, "MyGeoPosition", 55.776171747082f, 37.655123323203f, 2*0.03f); // Второй этаж
    
    // Проводим поиск ближайшей ноды для нашей гео позиции - для создания ребра
    Node* n = graph.GetNearestNode(myLocationId);
    if(n != NULL) {
        // Добавляем ребро
        graph.AddEdge(myLocationId, n->GetID());
        
        Node* to = graph.GetNode(55.776241140207f, 37.655178308487f, 1*0.03f); // Первый этаж
        if(to != NULL) {
            // Проводим поиск
            DijkstraSearch alg(&graph);
            ResultPath result = alg.FindPath(myLocationId, to->GetID());
            if(result.haveErrors) {
                return -1;
            }
            
            // Выводим результат
            for(int i=0; i < result.nodes.size(); i++) {
                Node* n = result.nodes[i];
                if(n != NULL) {
                    if(i > 0) {
                        printf(" -> ");
                    }
                    printf("Node#%d", n->GetID());
                }
            }
            printf("\nDistance: %f km.\n", result.distance);
        }
    }
    // Очищаем граф
    graph.Clear();
    return 0;
}
