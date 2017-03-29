#include "picking_custom.hpp"

#include "../../lib/3d/vec4.hpp"

#include <cmath>
#include <glm/gtc/matrix_inverse.hpp>
// http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/

namespace cpe{
namespace picking{

void ScreenPosToWorldRay(int mouseX, int mouseY,
                         int screenWidth, int screenHeight,
                         mat4 viewMatrix, mat4 projectionMatrix,
                         vec3 cam_position, mat3 cam_orientation,
                         vec3 &out_origin, vec3 &out_direction)
{
//    The ray starts and End positions, in Normalized device coordinates
    glm::vec4 lRayStart_NDC = glm::vec4(
                ((float)mouseX/(float)screenWidth - 0.5f) * 2.0f,  //[0, 1024] => [-1,1]
                ((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
                30.0f,
                1.0f);

//    glm::vec4 lRayStart_NDC = glm::vec4(
//                cam_position.x(),  //[0, 1024] => [-1,1]
//                cam_position.y(),
//                cam_position.z(),
//                1.0f);
    glm::vec4 lRayEnd_NDC(
                ((float)mouseX/(float)screenWidth - 0.5f )*2.0f,
                ((float)mouseY/(float)screenHeight - 0.5f) *2.0f,
                1e-4f,
                1.0f);


    //The projection matric goes from Camera space to NDC
    //So the inverse goes from NDC to Camera Space
        glm::mat4 glmProj = glm::mat4(projectionMatrix(0,0), projectionMatrix(0,1), projectionMatrix(0,2), projectionMatrix(0,3),
                                      projectionMatrix(1,0), projectionMatrix(1,1), projectionMatrix(1,2), projectionMatrix(1,3),
                                      projectionMatrix(2,0), projectionMatrix(2,1), projectionMatrix(2,2), projectionMatrix(2,3),
                                      projectionMatrix(3,0), projectionMatrix(3,1), projectionMatrix(3,2), projectionMatrix(3,3));
//    glm::mat4 glmProj = glm::mat4(projectionMatrix(0,0), projectionMatrix(1,0), projectionMatrix(2,0), projectionMatrix(3,0),
//                                  projectionMatrix(0,1), projectionMatrix(1,1), projectionMatrix(2,1), projectionMatrix(3,1),
//                                  projectionMatrix(0,2), projectionMatrix(1,2), projectionMatrix(2,2), projectionMatrix(3,2),
//                                  projectionMatrix(0,3), projectionMatrix(1,3), projectionMatrix(2,3), projectionMatrix(3,3));

    glm::mat4 InverseProjectionMatrix = glm::inverse(glmProj);

    //The view matric goes from world space to camera space the inverse do the opposite
//        glm::mat4 glmView = glm::mat4(viewMatrix(0,0), viewMatrix(0,1), viewMatrix(0,2), viewMatrix(0,3),
//                                      viewMatrix(1,0), viewMatrix(1,1), viewMatrix(1,2), viewMatrix(1,3),
//                                      viewMatrix(2,0), viewMatrix(2,1), viewMatrix(2,2), viewMatrix(2,3),
//                                      viewMatrix(3,0), viewMatrix(3,1), viewMatrix(3,2), viewMatrix(3,3));

//    glm::mat4 glmView = glm::mat4(viewMatrix(0,0), viewMatrix(1,0), viewMatrix(2,0), viewMatrix(3,0),
//                                  viewMatrix(0,1), viewMatrix(1,1), viewMatrix(2,1), viewMatrix(3,1),
//                                  viewMatrix(0,2), viewMatrix(1,2), viewMatrix(2,2), viewMatrix(3,2),
//                                  viewMatrix(0,3), viewMatrix(1,3), viewMatrix(2,3), viewMatrix(3,3));
    glm::mat4 glmView = glm::mat4(cam_orientation(0,0),-cam_orientation(1,0),cam_orientation(2,0) ,0.0f,//       cam_position.x(),
                                  cam_orientation(0,1),-cam_orientation(1,1),cam_orientation(2,1) ,0.0f,//       cam_position.y(),
                                  cam_orientation(0,2),-cam_orientation(1,2),cam_orientation(2,2) ,0.0f,//       cam_position.z(),
                                  cam_position.x(),cam_position.y(),cam_position.z(),1.0f);

//    glm::mat4 glmView = glm::mat4(cam_orientation(0,0),cam_orientation(0,1),cam_orientation(0,2) ,cam_position.x(),//       cam_position.x(),
//                                  cam_orientation(1,0),cam_orientation(1,1),cam_orientation(1,2) ,cam_position.y(),//       cam_position.y(),
//                                  cam_orientation(2,0),cam_orientation(2,1),cam_orientation(2,2) ,cam_position.z(),//       cam_position.z(),
//                                  0.0f,0.0f,0.0f,1.0f);


//    glm::mat4 glmView = glm::mat4(cam_orientation(0,0),-cam_orientation(1,0),cam_orientation(2,0) ,cam_position.x(),//       cam_position.x(),
//                                  cam_orientation(0,1),-cam_orientation(1,1),cam_orientation(2,1) ,cam_position.y(),//       cam_position.y(),
//                                  cam_orientation(0,2),-cam_orientation(1,2),cam_orientation(2,2) ,cam_position.z(),//       cam_position.z(),
//                                  0.0f,0.0f,0.0f,1.0f);


    glm::mat4 InverseViewMatrix = glm::inverse(glmView);

    glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;        lRayStart_camera/=lRayStart_camera.w;
    glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera;     lRayStart_world /=lRayStart_world .w;
    glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;          lRayEnd_camera  /=lRayEnd_camera  .w;
    glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;       lRayEnd_world   /=lRayEnd_world   .w;




    glm::vec3 lRayDir_world = glm::vec3(lRayEnd_world.x - lRayStart_world.x,
                                        lRayEnd_world.y - lRayStart_world.y,
                                        lRayEnd_world.z - lRayStart_world.z);
    lRayDir_world = glm::normalize(lRayDir_world);

    out_origin = vec3(lRayStart_world.x,lRayStart_world.y,lRayStart_world.z);
//    out_direction = vec3(lRayDir_world.x,lRayDir_world.y,lRayDir_world.z);
        out_direction = vec3(lRayEnd_world.x, lRayEnd_world.y, lRayEnd_world.z);
//vec3 tmp = out_origin;
//out_origin = out_direction;
//out_direction = tmp;

    std::cout << "start NDC   " << lRayStart_NDC.x << " " << lRayStart_NDC.y << " " << lRayStart_NDC.z << " " << lRayStart_NDC.w << std::endl;
    std::cout << "end NDC   " << lRayEnd_NDC.x << " " << lRayEnd_NDC.y << " " << lRayEnd_NDC.z << " " << lRayEnd_NDC.w << std::endl;
    std::cout << "start cam   " << lRayStart_camera.x << " " << lRayStart_camera.y << " " << lRayStart_camera.z << " " << lRayStart_camera.w << std::endl;
    std::cout << "end cam   " << lRayEnd_camera.x << " " << lRayEnd_camera.y << " " << lRayEnd_camera.z << " " << lRayEnd_camera.w << std::endl;
    std::cout << "out origin : "<< out_origin << std::endl;
    std::cout <<"out direction : " << out_direction << std::endl;
    std::cout << "### "<< std::endl;
}
//https://github.com/opengl-tutorials/ogl/blob/master/misc05_picking/misc05_picking_custom.cpp


bool TestRayOBBIntersection(vec3 ray_origin, vec3 ray_direction, vec3 aabb_min, vec3 aabb_max, mat4 ModelMatrix, float &intersection_distance)
{
    //Intersection method from Real-Time rendering and Essential Mathematics for game

    float tMin = 0.0f;
    float tMax = 1000000.0f;
    vec3 OBBposition_worldspace = vec3(ModelMatrix(3,0), ModelMatrix(3,1), ModelMatrix(3,2));
    vec3 delta = OBBposition_worldspace - ray_origin;

    //Intersection test with 2 planes perpendicculat to the OBB's x axis
    {
        vec3 xaxis(ModelMatrix(0,0), ModelMatrix(0,1), ModelMatrix(0,2));
        float e = dot(xaxis, delta);
        float f = dot(ray_direction, xaxis);

        if(fabs(f) > 0.001f)
        {
            float t1 = (e+aabb_min.x())/f;   //Intersection with the "left" plane
            float t2 = (e+aabb_max.x())/f;   //Intersection with the "right" plane
            //t1 and t2 now contain distances between ray origin and ray plane intersections

            //We want t1 to represent the nearest intersection
            //so if its not the case inverse t1 and t2
            if(t1>t2){ float w=t1; t1=t2; t2=w;}

            //tMax is the nearest far intersection (amongst the X,Y,Z planes pairs)
            if(t2 < tMax)
                tMax = t2;

            //tMin is the farthest "near" intersection (amongst the X,Y,Z) plane
            if(t1 > tMin)
                tMin = t1;

            //And there is the trick
            //If "far" is closer than "near" then there is NO intersection
            //See the images in the tutorials for the visual explanation
            if(tMax < tMin)
                return false;

        }
        else
        {
            //Rare case : the ray is almost parallel to the planes so they don't have any intersections
            if(-e+aabb_min.x() > 0.0f || -e + aabb_max.x() < 0.0f)
                return false;
        }
    }


    //Intersection test with the 2 planes perpendicluar to the OBB's y axis
    //Exactly the same thing than above
    {
        vec3 yaxis= vec3(ModelMatrix(1,0), ModelMatrix(1,1), ModelMatrix(1,2));
        float e = dot(yaxis, delta);
        float f = dot(ray_direction, yaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+aabb_min.y())/f;
            float t2 = (e+aabb_max.y())/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+aabb_min.y() > 0.0f || -e+aabb_max.y() < 0.0f)
                return false;
        }
    }

    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
        vec3 zaxis = vec3(ModelMatrix(2,0), ModelMatrix(2,1), ModelMatrix(2,2));
        float e = dot(zaxis, delta);
        float f = dot(ray_direction, zaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+aabb_min.z())/f;
            float t2 = (e+aabb_max.z())/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+aabb_min.z() > 0.0f || -e+aabb_max.z() < 0.0f)
                return false;
        }
    }

    intersection_distance = tMin;
    return true;
}



}
}
