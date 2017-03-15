

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


using namespace cpe;


void scene::load_scene()
{



    //*****************************************//
    // Preload default structure               //
    //*****************************************//
    texture_default = load_texture_file("data/white.jpg");
     shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag"); PRINT_OPENGL_ERROR();
   /* shader_program_id = read_shader("shaders/shader_material.vert",
                                    "shaders/shader_material.frag"); PRINT_OPENGL_ERROR();*/

    //******************************************//
    //OBJ Mesh                                  //
    //***************************************** //
    mesh_eye = load_mesh_file_obj2("/home/charly/workspace/EXPO/data/Blender/eye3d/sight3.obj");
    std::vector<mesh>::iterator it_mesh = mesh_eye.begin();
    std::vector<mesh_opengl>::iterator it_mgl = mesh_eye_opengl.begin();

    mesh_eye_opengl.assign(mesh_eye.size(),mesh_opengl());
    for(int i=0; i< mesh_eye.size(); i++)
    {
        mesh_eye.at(i).transform_apply_scale(0.2f);
        mesh_eye.at(i).fill_color_normal();
        mesh_eye_opengl.at(i).fill_vbo(mesh_eye.at(i));
    }

    /*SighConj_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighConj_pivot.obj");
        SighConj_pivot.transform_apply_scale(0.002f);
        SighConj_pivot_opengl.fill_vbo(SighConj_pivot);*/

    //**********//
    // MATERIALS //
    //**********//

    //*****************************************//
    // Generate user defined mesh              //
    //*****************************************//

}

void scene::draw_scene()
{
    //Setup uniform parameters
    glUseProgram(shader_program_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();






    //Draw the meshes

    /*for(auto& mgl : mesh_eye_opengl)
    {
        glBindTexture(GL_TEXTURE_2D,texture_default);
        mgl.draw();
    }*/
    int l = 0;
    for(int i=l; i<mesh_eye.size() ; ++i)
    {
       // glBindTexture(GL_TEXTURE_2D,texture_default);
        mesh_eye_opengl.at(i).draw();
    }
    //texture_SighConj_pivot = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighIriT.png");

    /* vec3 di = vec3(1.0,0.5,0.2);
    vec3 am = vec3(1.0,0.5,0.2);
    float N = 0.5;

    vec3& em  =  SighConj_pivot_material.emission();
    glUniform3fv(get_uni_loc(shader_program_id,"material[0].emission"),1,em.pointer());                        PRINT_OPENGL_ERROR();*/
    //glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighConj_pivot_opengl.draw();
/*

    texture_SighCorn = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighIriT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighCorn); PRINT_OPENGL_ERROR();
    //SighCorn_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighCoro_pivot_opengl.draw();

    texture_SighEsc1 = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighSecT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighEsc1);
    SighEsc1_opengl.draw();

    texture_SighEsc2 = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighSecT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighEsc2);
    //SighEsc2_opengl.draw();

    //texture_SighPupi_pivot = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/")
    em  = vec3(0.5,0.0,1.0);// SighPupi_pivot_material.emission();
    glUniform3fv(get_uni_loc(shader_program_id,"material[0].emission"),1,em.pointer());
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighPupi_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighReti_pivot_opengl.draw();

    texture_SighSkin_pivot = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighSkiT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighSkin_pivot);
    //SighSkin_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighSkul_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe01_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe02_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe03_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe04_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe05_pivot_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);
    //SighTe06_pivot_opengl.draw();*/

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

