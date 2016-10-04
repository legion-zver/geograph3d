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
    graph.AddNode(myLocationId, "MyGeoPosition", 55.77682041713589, 37.654655277729034, 2); // Первый этаж
    
    // Проводим поиск ближайшей ноды для нашей гео позиции - для создания ребра
    Node* n = graph.GetNearestNode(myLocationId);
    if(n != NULL) {
        // Добавляем ребро
        graph.AddEdge(myLocationId, n->GetID());
        
        Node* to = graph.GetNearestNode(55.77625170002003, 37.65544384717941, 2); // Второй этаж;
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
