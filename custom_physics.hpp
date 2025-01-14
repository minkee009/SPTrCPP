#pragma once

#include<SFML/System/Vector2.hpp>

namespace SPTr {
    struct Line{
        sf::Vector2f frontNormal;
        sf::Vector2f start;
        sf::Vector2f end;

        // �⺻ ������
        Line() : frontNormal(0.0f, 0.0f), start(0.0f, 0.0f), end(0.0f, 0.0f) {}

        // start�� end�� �޴� ������
        Line(const sf::Vector2f& start, const sf::Vector2f& end) 
            : frontNormal(0.0f, 0.0f), start(start), end(end) {}

        // start, end, frontNormal�� �޴� ������
        Line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Vector2f& frontNormal) 
            : frontNormal(frontNormal), start(start), end(end) {}

        // frontNormal�� �����Ǿ����� Ȯ���ϴ� �޼���
        bool hasFrontNormal() const {
            return frontNormal != sf::Vector2f(0.0f, 0.0f);
        }

        // ���� ���ͷ� ��ȯ�ϴ� �޼���
        sf::Vector2f toVector() const {
            return end - start;
        }

        // ���� �޼���: Line�� ���ͷ� ��ȯ
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
            static bool Raycast2D(const sf::Vector2f& position,const sf::Vector2f& dir,float dist,const Line& line,CustomRaycastHit2D& hitInfo);
            static float Cross2D(const sf::Vector2f& v1, const sf::Vector2f& v2);
    };
}