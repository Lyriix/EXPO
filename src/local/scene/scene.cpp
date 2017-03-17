

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
    /*shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag"); PRINT_OPENGL_ERROR();*/
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
        mesh_eye.at(i).fill_color(vec3(1.0f,1.0f,1.0f));
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
            int idx = it_map->second; //map_material.at(it_map);
            mesh.add_material_index(idx);
        }

    }
    std::cout << "REPRINT OBJ INFO WITH MATERIAL INDEX LOADED THIS TIME" << std::endl;
    print_obj_info(mesh_eye);


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

    //send material info

    //glUniform1i(get_uni_loc(shader_program_id,"NumMaterials"),material_eye.size()); PRINT_OPENGL_ERROR();
    //glUniform1i(get_uni_loc(shader_program_id,"NumMaterials"),1); PRINT_OPENGL_ERROR();
    for(auto& mat :material_eye)
    {
        //material mat = material_eye.at(0);
        //std::cout << mat.index() << std::endl;
        std::stringstream ss;
        ss << mat.index();
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



        glUniform3fv(get_uni_loc(shader_program_id, c_str_emission),1,mat.emission().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_ambient),1,mat.ambient().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_diffuse),1,mat.diffuse().pointer()); PRINT_OPENGL_ERROR();
        glUniform3fv(get_uni_loc(shader_program_id, c_str_specular),1,mat.specular().pointer()); PRINT_OPENGL_ERROR();
        glUniform1f(get_uni_loc(shader_program_id, c_str_shininess),mat.shininess()); PRINT_OPENGL_ERROR();
        glUniform1f(get_uni_loc(shader_program_id, c_str_transparency),mat.transparency()); PRINT_OPENGL_ERROR();
    }
    //send all the info to the shader then in the loop only send the index
    int l = 0;
    for(int i=l; i<mesh_eye.size() ; ++i)
    {
        // glBindTexture(GL_TEXTURE_2D,texture_default);
        //send material info
        glUniform1i(get_uni_loc(shader_program_id,"index_mat"),i);
        mesh_eye_opengl.at(i).draw();
    }
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
    std::cout << "@@@@@@@@@"<<std::endl;
    for(auto & mesh : mesh_eye)
    {
        names.push_back(mesh.get_material_name());
        std::cout <<"###"<< mesh.get_object_name() << std::endl;
    }
    return names;
}
