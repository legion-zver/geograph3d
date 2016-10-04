# GeoGraph3D - библиотека для поиска маршрутов в 3х мерном геолокационном графе

## Графическое представление

![exmaple1](/example1.png)

На рисунке выше представлен 3х мерный граф с нодами (вершинами) A,B,C,D,E,F,G,H,I.

Каждая нода (вершина) имеет такие параметры как идентификатор (id), тег (имя), широта, долгота (GEO позиция) и **уровень (расстояние в километрах от самого нижнего слоя (этажа в нашем случае))**. Первый слой (этаж) состоит из нод G, F, H, I. Второй слой (этаж) состоит из нод A, B, C, D, F. Слои (этажи) соединены через ноды B,F. 

В итоге мы имеем следующие ребра:

* A-B;
* B-C;
* B-D; 
* D-E;
* B-F;
* F-G;
* F-H;
* F-I.

Также на рисунке, зеленым пунктиром, показан найденный маршрут от ноды (вершины) A до ноды (вершины) I, с слоя (этажа) 2 до слоя (этажа) 1: A->B->F->H->I.

## Пример использования (main.cpp)

```c++
#include <iostream>
#import "dijkstra.hpp"

using namespace GeoGraph3D;

int main(int argc, const char * argv[]) {

    Graph graph;
    // Добавляем ноды (вершины) графа 
    // Первый этаж
    graph.AddNode(1, "A", 0.0, 0.0, 0.0);
    graph.AddNode(2, "B", 0.1, 0.1, 0.0);
    graph.AddNode(3, "C", 10.2, 50.2, 0.0);
    graph.AddNode(4, "D", 0.3, 20.3, 0.0);
    graph.AddNode(5, "E", 20.1, 10, 0.0);
    graph.AddNode(6, "F", -10.0, -2, 0.0);
    graph.AddNode(8, "H", 10, 10, 0.0);
    // Второй этаж
    graph.AddNode(7, "G", -1, 10, 0.025);    
    graph.AddNode(9, "I", 200, 1, 0.025);
    graph.AddNode(10, "G", 1, -10, 0.025);
    
    // Добавляем ребра графа
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 4);
    graph.AddEdge(4, 3);
    graph.AddEdge(4, 5);
    graph.AddEdge(4, 6);
    graph.AddEdge(6, 7);
    graph.AddEdge(3, 8);
    graph.AddEdge(3, 9);
    graph.AddEdge(7, 10);
    graph.AddEdge(9, 10);    
    
    // Берем наше положение и добавляем на него ноду
    graph.AddNode(999, "MyGeoPosition", 1.0, 1.0, 0.0);    
    // Проводим поиск ближайшей ноды для нашей гео позиции - для создания ребра
    Node* n = graph.GetNearestNode(999);
    if(n != NULL) {
      // Добавляем ребро
      graph.AddEdge(999, n->GetID());
    
      // Проводим поиск
      DijkstraSearch alg(&graph);
      ResultPath result = alg.FindPath(999, 10);
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
    // Очищаем граф
    graph.Clear();
    return 0;
}

```

## Примечание

**ОБЯЗАТЕЛЬНО ОЧИЩАЙТЕ (graph.Clear()) ГРАФ КОГДА ПРЕКРАТИЛИ С НИМ РАБОТАТЬ ИЛИ ПРИ УДАЛЕНИИ ОБЪЕКТА ГРАФА**

