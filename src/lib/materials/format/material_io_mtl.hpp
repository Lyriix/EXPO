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
#ifndef MATERIAL_IO_OBJ_HPP
#define MATERIAL_IO_OBJ_HPP

#include "../../3d/vec3.hpp"
#include <vector>
namespace cpe
{

class material;

/** Load  material informations from an MTL file */
std::vector<material> load_material_file_mtl(std::string const& filename);

/** an mtl structure following the definition of an mtl file */
struct mtl_structure
{
    std::string material_name;
    vec3 data_emission; //Ke
    vec3 data_ambient; //Ka
    vec3 data_diffuse; //Kd
    vec3 data_specular; //Ks
    float data_shininess; //Ns
    float data_transparency; //d
    int index;
};

/** Read an mtl file and return a material structure */
std::vector<mtl_structure> load_file_mtl_structure(std::string const& filename);

/** read material name */
void read_name_mtl(std::stringstream& tokens, mtl_structure& mtl, int idx);
/** Read phong specular component Ns */
void read_phong_mtl(std::stringstream& tokens, mtl_structure& mtl);
/** Ka : read ambient color */
void read_ambient_mtl(std::stringstream& tokens, mtl_structure& mtl);
/** Kd : read diffuse color */
void read_diffuse_mtl(std::stringstream& tokens, mtl_structure& mtl);
/** Ks Read specular color */
void read_specular_mtl(std::stringstream& tokens, mtl_structure& mtl);
/** Read emission parameter Ke */
void read_emission_mtl(std::stringstream& tokens, mtl_structure& mtl);
/** Read transparency parameter d */
void read_transparency_mtl(std::stringstream& tokens, mtl_structure& mtl);

void clean_structure(mtl_structure &mat);
void print_materials_info(std::vector<material> materials);

}

#endif
