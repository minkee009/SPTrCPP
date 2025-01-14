#include "custom_physics.hpp"

bool SPTr::CustomPhysics::Raycast2D(const sf::Vector2f& position,const sf::Vector2f& dir,float dist,const Line& line,CustomRaycastHit2D& hitInfo){
    hitInfo = CustomRaycastHit2D();

    sf::Vector2f r = dir * dist;
    sf::Vector2f s = line.toVector();

    float rxs = Cross2D(r, s);
    sf::Vector2f cma = line.start - position;

    float t = Cross2D(cma, s) / rxs;
    float u = Cross2D(cma, r) / rxs;

    if(t >= 0.0f && t <= 1.0f 
    && u >= 0.0f && u <= 1.0f){
        hitInfo.hitLine = line;
        hitInfo.distance = t * dist;
        hitInfo.hitPoint = sf::Vector2f(position.x + t * r.x,position.y + t * r.y);
        hitInfo.normal = sf::Vector2f(-s.y, s.x).normalized();
        hitInfo.normal = hitInfo.normal * (hitInfo.normal.dot(dir) < 0 ? -1.0f : 0.0f);
        return true;
    }

    return false;
}

float SPTr::CustomPhysics::Cross2D(const sf::Vector2f& v1, const sf::Vector2f& v2){
    return (v1.x * v2.y) - (v1.y * v2.x);
}

