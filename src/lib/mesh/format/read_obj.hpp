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

#ifndef READ_OBJ_HPP
#define READ_OBJ_HPP

#include <vector>
#include "../../3d/vec3.hpp"
#include "../../3d/vec2.hpp"
#include <string>
namespace cpe
{
class mesh;

/** Load a mesh structure from a obj file */
std::vector<mesh> load_mesh_file_obj2(std::string const& filename);

/** An obj structure following the definition of an obj file : it will be used as array containing multiple object/meshes*/
struct obj_structure2
{
    std::string object_name;

    std::vector<vec3> data_vertex;
    std::vector<vec2> data_texture;
    std::vector<vec3> data_normal;

    std::vector<std::vector<int>> data_face_vertex;
    std::vector<std::vector<int>> data_face_texture;
    std::vector<std::vector<int>> data_face_normal;

    std::string material_name;
    int material_index = 0;
};

/** Split a given string of face f from obj style into a set of values.
 *
 *  ex. 1/2 4/5 7/8 -> 1 2 4 5 7 8
 *      1/2/3 4/4/1 4/7/8 -> 1 2 3 4 4 1 4 7 8
 *      1//3 4//1 7//9 -> 1 3 4 1 7 9
 *      4 7 8 4 -> 4 7 8 4
 *
*/
std::vector<int> split_face_data2(std::string const& face_data_str);

/** Read an obj file and return an obj structure. */
std::vector<obj_structure2> load_file_obj_structure2(std::string const& filename);


void read_vertex_obj2(std::stringstream& tokens,obj_structure2& obj);
void read_texture_obj2(std::stringstream& tokens,obj_structure2& obj);
void read_name_obj2(std::stringstream& tokens, obj_structure2& obj);
void read_material_info(std::stringstream& tokens, obj_structure2& obj, int objects);
void create_temporary_obj(std::stringstream& tokens);
void clean_structure(obj_structure2& obj);

void print_obj_info(std::vector<mesh> meshes);

}

#endif
