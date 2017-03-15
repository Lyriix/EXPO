/*
** NYU Tandon School of Engineering
** Copyright (C) 2017 Charly Girot
** This program is free software: you can redistribute it and/or modify
** it under the terms of GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed int the hope that it wilil be useful,
** but WITHOUT ANY WARRANTY; without even the implied waranty of
** MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. if not see <http://www.gnu.org/licences/>
*/

#pragma once

#ifndef MATERIAL_BASIC_HPP
#define MATERIAL_BASIC_HPP

#include "../3d/vec3.hpp"
#include "../3d/vec4.hpp"

#include <vector>

namespace cpe{

/** Basic container for a material structure.
 * Used as parent class for other material structures.
 * The material contains:
 * - emission light vec3
 * - ambient light vec3
 * - diffuse light vec 3
 * - specular light vec3
 * - shininess float
 * - Transparency float
 * //Other properties you may desire
 * Issued from OpenGL PRogramming Guide 8th edition - Chapter 7 - PEARSON
 */

class material_basic
{
public:
    material_basic();

protected:

    /** Get set material name */
    std::string name() const;
    std::string& name();
    /** Get/Set materials emission */
    vec3 emission() const;
    vec3& emission();
    /** Get/Set material ambient */
    vec3 ambient() const;
    vec3& ambient();
    /** get/Set diffuse light */
    vec3 diffuse() const;
    vec3& diffuse();
    /** Get/Set specular_light */
    vec3 specular() const;
    vec3& specular();
    /** Get/set shinisses parameter */
    float shininess() const;
    float& shininess();
    /** Get/set transparency parameter */
    float transparency() const;
    float& transparency();
    /** Get/set material index */
    int index() const;
    int& index();


    /** Set material */
    void set_name(std::string const& na);
    void set_emission(vec3 const& v);
    void set_ambient(vec3 const& v);
    void set_diffuse(vec3 const& v);
    void set_specular(vec3 const& v);
    void set_shininess(float const& f);
    void set_transparency(float const& t);
    void set_material_index(int const& mIndex);


private:
    //MATERIAL PROPERTIES
    /** Name of the material */
    std::string name_material;
    /** Internal Storage for emission light */
    vec3 emission_light;
    /** Internal storage for ambient light */
    vec3 ambient_light;
    /** Internal storage for diffuse light */
    vec3 diffuse_light;
    /** Internal storage for specular light */
    vec3 specular_light;
    /** Internal storage for Shininess light parameter */
    float shininess_parameter;
    /** Internal stroage for transparency parameter */
    float transparency_parameter;

    /** Index of this material */
    int material_index;

    // LIGHT PROPERTIES

};


}

#endif


/*
 * http://paulbourke.net/dataformats/mtl/
 * https://people.cs.clemson.edu/~dhouse/courses/405/docs/brief-mtl-file-format.html
Ns      = Phong specular component. Ranges from 0 to 1000. (I've seen various statements about this range (see below))
Kd      = Diffuse color weighted by the diffuse coefficient.//
Ka      = Ambient color weighted by the ambient coefficient. //
Ks      = Specular color weighted by the specular coefficient. //
d       = Dissolve factor (pseudo-transparency). Values are from 0-1. 0 is completely transparent, 1 is opaque. Tr = 1-d
Ni      = Refraction index. Values range from 1 upwards. A value of 1 will cause no refraction. A higher value implies refraction.
illum   = (0, 1, or 2) 0 to disable lighting, 1 for ambient & diffuse only (specular color set to black), 2 for full lighting (see below)
sharpness = ? (see below)
map_Kd  = Diffuse color texture map.
map_Ks  = Specular color texture map.
map_Ka  = Ambient color texture map.
map_Bump = Bump texture map.
map_d   = Opacity texture map.
refl    = reflection type and filename (?)


illum :
0. Color on and Ambient off
1. Color on and Ambient on
2. Highlight on
3. Reflection on and Ray trace on
4. Transparency: Glass on, Reflection: Ray trace on
5. Reflection: Fresnel on and Ray trace on
6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
8. Reflection on and Ray trace off
9. Transparency: Glass on, Reflection: Ray trace off
10. Casts shadows onto invisible surfaces

*/
