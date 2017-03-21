#pragma once

#ifndef PICKINGRAY_HPP
#define PICKINGRAY_HPP

#include "../3d/vec3.hpp"

namespace cpe
{
class PickingRay
{
public :
    PickingRay();
    /** \brief Compute the intersection of this ray woith the X-Y plane where(Z=0)
     * and writes it back to the provided vector
     */
    void intersectionWithXyPlane(float worldPos[]);

    void setClickPosInWorld(vec3 v);
    void setDirection(vec3 v);
    vec3 getClickPosInWorld();
    vec3 getDirection();

private:
    vec3 clickPosInWorld;
    vec3 direction;

};

}
#endif
