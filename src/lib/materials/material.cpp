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


#include "material.hpp"

#include "../common/error_handling.hpp"

namespace cpe
{

vec3 material::emission() const { return material_basic::emission();}
vec3& material::emission()      {    return material_basic::emission();}
vec3 material::ambient() const {   return material_basic::ambient(); }
vec3& material::ambient()       {    return material_basic::ambient(); }
vec3 material::diffuse() const {    return material_basic::diffuse(); }
vec3& material::diffuse()       {    return material_basic::diffuse(); }
vec3 material::specular() const{ return material_basic::specular();}
vec3& material::specular()      {    return material_basic::specular();}
float material::shininess() const { return material_basic::shininess(); }
float& material::shininess()       { return material_basic::shininess(); }

}
