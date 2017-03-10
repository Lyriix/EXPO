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
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "material_basic.hpp"

namespace cpe
{
 /** A derivated class for material_basic giving public access to modfifier */
class material : public material_basic
{
public:
    using material_basic::material_basic;

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
    /** Get/set material index */
    int index() const;
    int& index();

    /** Set material */
    void set_emission(vec3 const& v);
    void set_ambient(vec3 const& v);
    void set_diffuse(vec3 const& v);
    void set_specular(vec3 const& v);
    void set_shininess(float const& f);
    void set_material_index(int const& mIndex);
};
}

#endif
