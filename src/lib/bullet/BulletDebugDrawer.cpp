


#include "BulletDebugDrawer.hpp"
#include "../3d/vec3.hpp"
#include "GL/glext.h"
namespace cpe {


/*
BulletDebugDrawer::BulletDebugDrawer()
    :m_debugMode(0)
{}*/

BulletDebugDrawer::~BulletDebugDrawer()
{}


void BulletDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color){
    glColor3f(color.x(), color.y(), color.z());
    glBegin(GL_LINES);
    glVertex3f(from.x(), from.y(), from.z());
    glVertex3f(to.x(), to.y(), to.z());
    glEnd();
}

/*void BulletDebugDrawer::SetMatrices(mat4 pViewMatrix, mat4 pProjectionMatrix){
    glUseProgram(0); // Use Fixed-function pipeline (no shaders)
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&pViewMatrix(0,0));
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&pProjectionMatrix(0,0));
}*/
void BulletDebugDrawer::drawContactPoint(const btVector3 & pOnB,const btVector3 & nOnB,btScalar distance,int lifeTime,const btVector3 & color)
{

    glColor3f(color.x(), color.y(), color.z());
    glBegin(GL_LINES);
    glVertex3f(pOnB.x(), pOnB.y(), pOnB.z());
    glVertex3f(nOnB.x(), nOnB.y(), nOnB.z());
    glEnd();

}



}
