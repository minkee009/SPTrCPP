#pragma once

#include<SFML/System/Vector2.hpp>

namespace SPTr {
    struct Line{
        sf::Vector2f frontNormal;
        sf::Vector2f start;
        sf::Vector2f end;

        // 기본 생성자
        Line() : frontNormal(0.0f, 0.0f), start(0.0f, 0.0f), end(0.0f, 0.0f) {}

        // start와 end를 받는 생성자
        Line(const sf::Vector2f& start, const sf::Vector2f& end) 
            : frontNormal(0.0f, 0.0f), start(start), end(end) {}

        // start, end, frontNormal을 받는 생성자
        Line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& frontNormal) 
            : frontNormal(frontNormal), start(start), end(end) {}

        // frontNormal이 설정되었는지 확인하는 메서드
        bool hasFrontNormal() const {
            return frontNormal != sf::Vector2f(0.0f, 0.0f);
        }

        // 선을 벡터로 변환하는 메서드
        sf::Vector2f toVector() const {
            return end - start;
        }

        // 정적 메서드: Line을 벡터로 변환
        static sf::Vector2f lineToVector(const Line& line) {
            return line.end - line.start;
        } 
    };

    struct CustomRaycastHit2D{
        Line hitLine;
        sf::Vector2f normal;
        float distance;
        sf::Vector2f hitPoint;

        CustomRaycastHit2D()
            : hitLine(), normal(0, 0), distance(0.0f), hitPoint(0,0) {}
        
        CustomRaycastHit2D(const Line& hitLine, const sf::Vector2f& normal, float distance, const sf::Vector2f& hitPoint)
            : hitLine(hitLine), normal(normal), distance(distance), hitPoint(hitPoint) {}
    };
    
    class CustomPhysics{
        public:
            static bool raycast2D(const sf::Vector2f& position,const sf::Vector2f& dir,float dist,const Line& line,CustomRaycastHit2D& hitInfo);
            static float cross2D(const sf::Vector2f& v1, const sf::Vector2f& v2);
    };
}