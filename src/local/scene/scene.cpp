

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"
#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"
#include "../interface/myWidgetGL.hpp"
#include "../../lib/mesh/mesh_io.hpp"

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

    //******************************************//
    //OBJ Mesh                                  //
    //***************************************** //

    SighConj_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighConj_pivot.obj");
    SighConj_pivot.transform_apply_scale(0.002f);
    SighConj_pivot_opengl.fill_vbo(SighConj_pivot);

    SighCorn = load_mesh_file("data/Blender/eye3d/object/obj/SighCorn.obj");
    SighCorn.transform_apply_scale(0.002f);
    SighCorn_opengl.fill_vbo(SighCorn);

    SighCoro_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighCoro_pivot.obj");
    SighCoro_pivot.transform_apply_scale(0.002f);
    SighCoro_pivot_opengl.fill_vbo(SighCoro_pivot);

    SighEsc1 = load_mesh_file("data/Blender/eye3d/object/obj/SighEsc1.obj");
    SighEsc1.transform_apply_scale(0.002f);
    SighEsc1_opengl.fill_vbo(SighEsc1);

    SighEsc2 = load_mesh_file("data/Blender/eye3d/object/obj/SighEsc2.obj");
    SighEsc2.transform_apply_scale(0.002f);
    SighEsc2_opengl.fill_vbo(SighEsc2);

    SighPupi_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighPupi_pivot.obj");
    SighPupi_pivot.transform_apply_scale(0.002f);
    SighPupi_pivot_opengl.fill_vbo(SighPupi_pivot);

    SighReti_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighReti_pivot.obj");
    SighReti_pivot.transform_apply_scale(0.002f);
    SighReti_pivot_opengl.fill_vbo(SighReti_pivot);

    SighSkin_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighSkin_pivot.obj");
    SighSkin_pivot.transform_apply_scale(0.002f);
    SighSkin_pivot_opengl.fill_vbo(SighSkin_pivot);

    SighSkul_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighSkul_pivot.obj");
    SighSkul_pivot.transform_apply_scale(0.002f);
    SighSkul_pivot_opengl.fill_vbo(SighSkul_pivot);

    SighTe01_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe01_pivot.obj");
    SighTe02_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe02_pivot.obj");
    SighTe03_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe03_pivot.obj");
    SighTe04_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe04_pivot.obj");
    SighTe05_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe05_pivot.obj");
    SighTe06_pivot = load_mesh_file("data/Blender/eye3d/object/obj/SighTe06_pivot.obj");
    SighTe01_pivot.transform_apply_scale(0.002f);
    SighTe02_pivot.transform_apply_scale(0.002f);
    SighTe03_pivot.transform_apply_scale(0.002f);
    SighTe04_pivot.transform_apply_scale(0.002f);
    SighTe05_pivot.transform_apply_scale(0.002f);
    SighTe06_pivot.transform_apply_scale(0.002f);
    SighTe01_pivot_opengl.fill_vbo(SighTe01_pivot);
    SighTe02_pivot_opengl.fill_vbo(SighTe02_pivot);
    SighTe03_pivot_opengl.fill_vbo(SighTe03_pivot);
    SighTe04_pivot_opengl.fill_vbo(SighTe04_pivot);
    SighTe05_pivot_opengl.fill_vbo(SighTe05_pivot);
    SighTe06_pivot_opengl.fill_vbo(SighTe06_pivot);

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
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighConj_pivot_opengl.draw();
    texture_SighCorn = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighIriT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighCorn); PRINT_OPENGL_ERROR();
    SighCorn_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighCoro_pivot_opengl.draw();
    texture_SighEsc1 = load_texture_file("/home/charly/workspace/EXPO/data/Blender/eye3d/textures/SighSecT.png");
    glBindTexture(GL_TEXTURE_2D,texture_SighEsc1);
    SighEsc1_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighEsc2_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighPupi_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighReti_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighSkin_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighSkul_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe01_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe02_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe03_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe04_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe05_pivot_opengl.draw();
    glBindTexture(GL_TEXTURE_2D,texture_default);
    SighTe06_pivot_opengl.draw();

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

