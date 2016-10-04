//
//  node.hpp
//  gepgraph3d
//
//  Created by Александр Зверь on 28.09.16.
//  Copyright © 2016 ALEXANDER GARIN. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>
#include <string>
namespace GeoGraph3D {
    // Структура точки
    struct Point {
        double latitude;
        double longitude;
        bool   empty;
    };
    
    // Нода графа
    class Node {
    public:
        //MARK: Constructors
        
        Node(unsigned int _id);
        Node(unsigned int _id, std::string _tag, double _latitude = 0, double _longitude = 0, double _level = 0);
        Node(unsigned int _id, double _latitude = 0, double _longitude = 0, double _level = 0);
        
        //MARK: Sets
        
        void SetTag(std::string _tag);          // Установить тег ноды
        void SetLatitude(double _latitude);     // Установить широту
        void SetLongitude(double _longitude);   // Установить долготу
        void SetLevel(double _level);           // Установить уровень в км
        
        //MARK: Gets
        
        unsigned int    GetID();
        std::string     GetTag();
        double          GetLatitude();
        double          GetLongitude();
        double          GetLevel();        
        bool            CompareLocation(double _latitude, double _longitude);
        
        //MARK: Math
        
        double DistanceTo(Node* node);
        double DistanceTo(double _latitude, double _longitude, double _level);
        
        // CheckPointInLine - Проверяем находится ли точка на линии
        static bool CheckPointInLine2D(double latitude, double longitude, Node* p1, Node* p2);
        
        // FindCrossTwoLines - Поиск точки пересечения двух линий
        static Point FindCrossTwoLines2D(Node* p0, Node* p1, Node* r0, Node* r1, bool duo = true);
        
    private:
        unsigned int    id;         // Идентификатор
        std::string     tag;        // Тег - имя
        double          latitude;   // Широта
        double          longitude;  // Долгота
        double          level;      // Высота
    };
};

#endif /* node_hpp */
