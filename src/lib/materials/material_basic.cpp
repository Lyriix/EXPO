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


#include "material_basic.hpp"

#include "../common/error_handling.hpp"


namespace cpe
{

material_basic::material_basic()
    :emission_light(),ambient_light(),diffuse_light(),specular_light(),shininess_parameter()
{}

vec3 material_basic::emission() const{    return emission_light;}
vec3& material_basic::emission()      {    return emission_light;}
vec3 material_basic::ambient() const {    return ambient_light; }
vec3& material_basic::ambient()       {    return ambient_light; }
vec3 material_basic::diffuse() const {    return diffuse_light; }
vec3& material_basic::diffuse()       {    return diffuse_light; }
vec3 material_basic::specular() const{    return specular_light;}
vec3& material_basic::specular()      {    return specular_light;}
float material_basic::shininess() const { return shininess_parameter; }
float& material_basic::shininess()       { return shininess_parameter; }


}