
/** TP 4ETI - CPE Lyon - 2013/2014 */

#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/gl.h>
#include <GL/glew.h>

#include "../../lib/3d/mat3.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/mesh/mesh.hpp"
#include "../../lib/opengl/mesh_opengl.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include <vector>


class myWidgetGL;

class scene
{
public:

    scene();



    /** \brief Method called only once at the beginning (load off files ...) */
    void load_scene();

    /** \brief Method called at every frame */
    void draw_scene();

    /** Set the pointer to the parent Widget */
    void set_widget(myWidgetGL* widget_param);


private:

    /** Load a texture from a given file and returns its id */
    GLuint load_texture_file(std::string const& filename);

    /** Access to the parent object */
    myWidgetGL* pwidget;

    /** Default id for the texture (white texture) */
    GLuint texture_default;

    /** The id of the shader do draw meshes */
    GLuint shader_program_id;


    // Data of the scene

    cpe::mesh SighConj_pivot, SighCorn, SighCoro_pivot, SighEsc1, SighEsc2, SighPupi_pivot,
            SighReti_pivot, SighSkin_pivot, SighSkul_pivot, SighTe01_pivot, SighTe02_pivot,
            SighTe03_pivot, SighTe04_pivot, SighTe05_pivot, SighTe06_pivot;
    cpe::mesh_opengl SighConj_pivot_opengl, SighCorn_opengl, SighCoro_pivot_opengl,
                SighEsc1_opengl, SighEsc2_opengl, SighPupi_pivot_opengl,
                SighReti_pivot_opengl, SighSkin_pivot_opengl, SighSkul_pivot_opengl,
                SighTe01_pivot_opengl, SighTe02_pivot_opengl, SighTe03_pivot_opengl,
                SighTe04_pivot_opengl, SighTe05_pivot_opengl, SighTe06_pivot_opengl;
    GLuint texture_SighConj_pivot, texture_SighCorn, texture_SighEsc1;



    /** Variable for Dragon */
    float tps=0.0f;
    float op = 1.0f;

};

#endif