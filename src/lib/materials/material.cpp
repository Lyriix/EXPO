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

std::string material::name() const { return material_basic::name();}
std::string& material::name() { return material_basic::name();}
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
float material::transparency() const { return material_basic::transparency();}
float& material::transparency() {return material_basic::transparency();}
int material::index() const { return material_basic::index(); }
int& material::index() { return material_basic::index(); }

void material::set_name(std::string const& na){material_basic::set_name(na);}
void material::set_emission(vec3 const& v){ material_basic::set_emission(v); }
void material::set_ambient(vec3 const& v) { material_basic::set_ambient(v); }
void material::set_diffuse(vec3 const& v){  material_basic::set_diffuse(v); }
void material::set_specular(vec3 const& v){ material_basic::set_specular(v);}
void material::set_shininess(float const& f){ material_basic::set_shininess(f);}
void material::set_transparency(const float &t){material_basic::set_transparency(t);}
void material::set_material_index(int const& mIndex){ material_basic::set_material_index(mIndex);}
}
