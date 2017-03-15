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
    :emission_light(),ambient_light(),diffuse_light(),specular_light(),shininess_parameter(),transparency_parameter(),name_material(),material_index()
{}
std::string material_basic::name() const {return name_material;}
std::string& material_basic::name() {return name_material;}
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
float material_basic::transparency() const { return transparency_parameter;}
float& material_basic::transparency()       { return transparency_parameter;}

int material_basic::index() const { return material_index;}
int& material_basic::index() { return material_index;}

void material_basic::set_name(std::string const& na){ name_material = na;}
void material_basic::set_emission(vec3 const& v){ emission_light = v; }
void material_basic::set_ambient(vec3 const& v) { ambient_light = v; }
void material_basic::set_diffuse(vec3 const& v){  diffuse_light = v; }
void material_basic::set_specular(vec3 const& v){ specular_light = v;}
void material_basic::set_shininess(float const& f){shininess_parameter = f;}
void material_basic::set_transparency(const float &t){transparency_parameter =t;}
void material_basic::set_material_index(const int &mIndex) {material_index = mIndex; }

}
