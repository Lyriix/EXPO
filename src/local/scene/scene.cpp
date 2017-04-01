

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"
#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"
#include "../interface/myWidgetGL.hpp"
#include "../../lib/mesh/mesh_io.hpp"
#include "../../lib/materials/material_io.hpp"

#include "../../lib/mesh/format/read_obj.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>


using namespace cpe;


void scene::load_scene()
{
    //*****************************************//
    // Preload default structure               //
    //*****************************************//
    texture_default = load_texture_file("data/white.jpg");

    texture_cornea = load_texture_file("data/Blender/eye3d/textures/SighIriT.JPG");
    texture_esclerot = load_texture_file("data/Blender/eye3d/textures/SighSecT.png");
    texture_skin = load_texture_file("data/Blender/eye3d/textures/SighSkiT.png");
    shader_program_id = read_shader("shaders/shader_material.vert",
                                    "shaders/shader_material.frag"); PRINT_OPENGL_ERROR();

    //******************************************//
    //OBJ Mesh                                  //
    //***************************************** //
    mesh_eye = load_mesh_file_obj2("/home/charly/workspace/EXPO/data/Blender/eye3d/sight.obj");

    std::vector<mesh_opengl>::iterator it_mgl = mesh_eye_opengl.begin();

    mesh_eye_opengl.assign(mesh_eye.size(),mesh_opengl());
    for(int i=0; i< mesh_eye.size(); i++)
    {
        mesh_eye.at(i).transform_apply_scale(0.2f);
        mesh_eye.at(i).add_object_index(i);
        mesh_eye_opengl.at(i).fill_vbo(mesh_eye.at(i));
    }


    //**********//
    // MATERIALS //
    //**********//
    material_eye = load_material_file("/home/charly/workspace/EXPO/data/Blender/eye3d/sight.mtl");

    //Link material index and object_material_index by name
    //That should be done while reading the .obj file but in a time coherent work with the result its done in the hard way at this point

    std::map<std::string,int> map_material;
    for(auto const& mat : material_eye)
    {
        map_material[mat.name()] = mat.index();
    }
    for(auto& mesh : mesh_eye)
    {
        std::map<std::string,int>::iterator it_map = map_material.find(mesh.get_material_name());
        if(it_map != map_material.end())
        {
            int idx = it_map->second;
            mesh.add_material_index(idx);
        }
    }

    init_physics();

    std::cout << "REPRINT OBJ INFO WITH MATERIAL INDEX LOADED THIS TIME" << std::endl;
    print_obj_info(mesh_eye);
}

void scene::init_physics()
{
    //build the broadphase
    broadphase = new btDbvtBroadphase();
    //Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    //The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;
    //The world
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    world->setGravity(btVector3(0.f,0.f,0.f));

    //Construction of the physic objects
    //    mStates.assign(mesh_eye.size(),);
    //    int i=0;
    for(auto & me : mesh_eye)
    {
        // Bounding box
        btConvexHullShape* shape = new btConvexHullShape();
        // Adding vertex to the shape/BB
        for( int i=0; i< me.size_vertex() ; i++)
            shape->addPoint(btVector3(me.vertex(i).x(), me.vertex(i).y(), me.vertex(i).z()));
        //property of the shape/bb (position, mass, inertia)
        btTransform transform;
        transform.setIdentity();
        btVector3 localInertia(0,0,0);
        btScalar mass = 0.0f;
        if(mass)
            shape->calculateLocalInertia(mass,localInertia);
        //The motion state (for simulations and displacement)
        btMotionState* motionState = new btDefaultMotionState(transform);
        mStates.push_back(motionState); // Not even sure we need it finally
        //The rigid body
        btRigidBody::btRigidBodyConstructionInfo bodyConstructionInfo(mass, motionState, shape, localInertia);
        btRigidBody* body = new btRigidBody(bodyConstructionInfo);
        body->setUserIndex(me.get_object_index());
        rigidBodies.push_back(body);
        world->addRigidBody(body);
    }
    btDebugDrawer = new cpe::BulletDebugDrawer();
    world->setDebugDrawer(btDebugDrawer);

}

void scene::draw_scene()
{
    glFlush();
    //Setup uniform parameters
    glUseProgram(shader_program_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();


    //Draw the meshes

    //send material info
    int i= 0;
    for(auto& mes :mesh_eye)
    {
        int mat_index = mes.get_material_index();
        material mat = material_eye.at(mat_index);
        //material mat = material_eye.at(0);
        //std::cout << mat.index() << std::endl;
        std::stringstream ss;
        ss << mat_index;
        //ss << mat.index();
        std::string e = "material["+ss.str() + "].emission";
        std::string a = "material["+ss.str() + "].ambient";
        std::string d = "material["+ss.str() + "].diffuse";
        std::string s = "material["+ss.str() + "].specular";
        std::string shi = "material["+ss.str() + "].shininess";
        std::string tr = "material["+ss.str() + "].transparency";

        const char *c_str_emission = e.c_str();
        const char *c_str_ambient = a.c_str();
        const char *c_str_diffuse = d.c_str();
        const char *c_str_specular = s.c_str();
        const char *c_str_shininess = shi.c_str();
        const char *c_str_transparency = tr.c_str();

        //std::cout << mat_index << std::endl;

        glUniform1i(get_uni_loc(shader_program_id,"index_mat"),mat_index);
        glUniform3fv(get_uni_loc(shader_program_id, c_str_emission),1,mat.emission().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_ambient),1,mat.ambient().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_diffuse),1,mat.diffuse().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_specular),1,mat.specular().pointer()); PRINT_OPENGL_ERROR();
        glUniform1f(get_uni_loc(shader_program_id, c_str_shininess),mat.shininess()); PRINT_OPENGL_ERROR();
        glUniform1f(get_uni_loc(shader_program_id, c_str_transparency),mat.transparency()); PRINT_OPENGL_ERROR();

        vec3 light(0.5,0.5,0.5);
        glUniform3fv(get_uni_loc(shader_program_id, "light"),1,light.pointer()); PRINT_OPENGL_ERROR();
        //Hack for display all the meshes after initialization of the list
        if(firstTranslation)
        {
            mes.transform_apply_translation(vec3(0.0001f,0.0001f,0.0001f));
            mesh_eye_opengl.at(i).fill_vbo(mes);


        }

        if( (mes.get_object_name() == "Cornea"))        {           glBindTexture(GL_TEXTURE_2D,texture_cornea);  PRINT_OPENGL_ERROR();        }
        else if( (mes.get_object_name() == "Esclerot1" ))        {           glBindTexture(GL_TEXTURE_2D,texture_default);  PRINT_OPENGL_ERROR();        }
        else if( mes.get_object_name() == "Skin") { glBindTexture(GL_TEXTURE_2D,texture_skin); PRINT_OPENGL_ERROR(); }
        else {  glBindTexture(GL_TEXTURE_2D,texture_default);  PRINT_OPENGL_ERROR(); }


        if(!mes.get_hide_status())
            mesh_eye_opengl.at(i).draw();
        i++;

    }

    firstTranslation = false;
    world->stepSimulation(1.0f/pwidget->get_nav().fps() , 1);
    glLineWidth(2.5);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);

    glVertex3f(out_origin.x(),out_origin.y(), out_origin.z());
    glVertex3f(out_direction.x(), out_direction.y(), out_direction.z());
    glEnd();
    if(drawDebugbullet)
        world->debugDrawWorld();

}


scene::scene()
    :shader_program_id(0)
{}


GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}


std::vector<std::string> scene::get_meshes_names()
{
    std::vector<std::string> names;
    for(auto & mesh : mesh_eye)
    {
        names.push_back(mesh.get_object_name());

    }
    return names;
}

std::vector<cpe::mesh>& scene::get_meshes()
{
    return mesh_eye;
}



void scene::picking(int x, int y)
{
    std::pair<vec3,vec3> out = pwidget->get_nav().ray_world_space_cam1(x,y);
    out_origin = out.first;
    out_direction = out.second*1000.0f;

    btCollisionWorld::ClosestRayResultCallback RayCallBack(
                btVector3(out_origin.x(),out_origin.y(), out_origin.z()),
                btVector3(out_direction.x(), out_direction.y(), out_direction.z()));
    world->rayTest(btVector3(out_origin.x(),out_origin.y(), out_origin.z()),
                   btVector3(out_direction.x(), out_direction.y(), out_direction.z()),
                   RayCallBack);

    if(RayCallBack.hasHit())
    {
        btVector3 pickPos = RayCallBack.m_hitPointWorld;
        btRigidBody* body_tmp = (btRigidBody*)btRigidBody::upcast(RayCallBack.m_collisionObject);
        if(body_tmp)
        {
            m_pickedBody = body_tmp;
            m_savedState = m_pickedBody->getActivationState();
            m_pickedBody->setActivationState(DISABLE_DEACTIVATION);
            btVector3 localPivot = body_tmp->getCenterOfMassTransform().inverse() * pickPos;
            btPoint2PointConstraint* p2p = new btPoint2PointConstraint(*body_tmp, localPivot);
            world->addConstraint(p2p); //,TRUE);
            m_pickedConstraint = p2p;

            std::cout << mesh_eye.at(m_pickedBody->getUserIndex()).get_material_name() << std::endl;

        }
    }
}

void scene::pick_and_move(float tr_x, float tr_y)
{
    camera_matrices const& cam = pwidget->camera();

    if(m_pickedBody && m_pickedConstraint)
    {
        btPoint2PointConstraint* pickCon = static_cast<btPoint2PointConstraint*>(m_pickedConstraint);
        if(pickCon)
        {
            vec3 trans = vec3(tr_x, -tr_y, 0.f);
            trans = cam.normal * trans;
            //            std::cout << trans << std::endl;
            trans.z() = - trans.z();
            m_pickedBody->getWorldTransform().setOrigin(
                        m_pickedBody->getWorldTransform().getOrigin()
                        + btVector3( trans.x(), trans.y(), trans.z()));
            int index = m_pickedBody->getUserIndex();
            mesh_eye.at(index).transform_apply_translation(trans);
            mesh_eye_opengl.at(index).fill_vbo(mesh_eye.at(index));
        }
    }
}

void scene::remove_picking_constraint()
{
    if(m_pickedConstraint != 0)
    {
        m_pickedBody->getMotionState();
        m_pickedBody->forceActivationState(m_savedState);
        //        m_pickedBody->forceActivationState(ACTIVE_TAG);
        //        m_pickedBody->activate();
        world->removeConstraint(m_pickedConstraint);
        delete m_pickedConstraint;
        m_pickedConstraint = 0;
        m_pickedBody = 0;

    }
}

void scene::dealloc()
{
    delete world;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

void scene::change_draw_state_mesh_index(int index, bool state)
{
    mesh_eye.at(index).set_hide_status(state);

}

void scene::set_debug_draw_bullet(bool is_on)
{
    drawDebugbullet = is_on;
}
