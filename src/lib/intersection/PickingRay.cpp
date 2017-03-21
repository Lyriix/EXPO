
#include "PickingRay.hpp"

namespace cpe
{

PickingRay::PickingRay()
    :clickPosInWorld(),direction()
{}

void PickingRay::intersectionWithXyPlane(float worldPos[])
{
    float s = -clickPosInWorld.z() / direction.z();
    worldPos[0] = clickPosInWorld.x()+direction.x()*s;
    worldPos[1] = clickPosInWorld.y()+direction.y()*s;
    worldPos[2] = 0.0f;
}

void PickingRay::setClickPosInWorld(vec3 v)
{
    clickPosInWorld = v;
}

void PickingRay::setDirection(vec3 v)
{
    direction = v;
}

vec3 PickingRay::getClickPosInWorld()
{
    return clickPosInWorld;
}

vec3 PickingRay::getDirection()
{
    return direction;
}
}
