#pragma once

#ifndef BULLET_DEBUG_DRAWER_HPP
#define BULLET_DEBUG_DRAWER_HPP

#include <LinearMath/btIDebugDraw.h>

#include "../3d/mat4.hpp"

#include <GL/glew.h>
namespace cpe {

class BulletDebugDrawer : public btIDebugDraw
{

    int m_debugMode;

public:

    //BulletDebugDrawer();
    virtual ~BulletDebugDrawer();
    //void SetMatrices(mat4 pViewMatrix, mat4 pProjectionMatrix);
    virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
    virtual void drawContactPoint(const btVector3 &,const btVector3 &,btScalar,int,const btVector3 &);
    virtual void reportErrorWarning(const char *){}
    virtual void draw3dText(const btVector3 &,const char *){}
    virtual void setDebugMode(int p){
        m_debugMode = p;
    }
    virtual int getDebugMode(void) const {return 1  ;} //3

};

}


#endif
