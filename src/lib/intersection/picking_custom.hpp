



#pragma once
#ifndef PICKING_CUSTOM_HPP
#define PICKING_CUSTOM_HPP


#include "../../lib/3d/vec3.hpp"
#include "../3d/mat4.hpp"


namespace cpe
{
namespace picking
{

void ScreenPosToWorldRay(int mouseX, //mouse posision in pixel from bottom left corrner of the windoz
                         int mouseY,
                         int screenWidth, // windoz size in pixels
                         int screenHeight,
                         mat4 viewMatrix, //Camera position and orientation
                         mat4 projectionMatrix, //Camera paramters (ratio, fov, near and far planes)
                         vec3& out_origin, // Origin of the tay
                         vec3& out_direction); //direciton in world space of the ray that goes trough the mouse

bool TestRayOBBIntersection(
        vec3 ray_origin,            //Ray origin in world space
        vec3 ray_direction,         //Ray direction (NOT Target position)_ in world space. Must bne nmormalize()
        vec3 aabb_min,              //Minimum XYZ coords of the mesh when not transformed at all
        vec3 aabb_max,              // Maximum XYZ coords. often aabb_min -1 if mesh is centered but not always
        mat4 ModelMatrix,           //Transformation applied to the mesh(which will this ne also applied to its bounding box)
        float& intersection_distance); // OUtput : distance between ray_origin and the intersection with the OBB
}


}


#endif
