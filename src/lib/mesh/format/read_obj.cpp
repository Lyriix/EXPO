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


#include "read_obj.hpp"
#include "../../common/error_handling.hpp"
#include "../../mesh/mesh.hpp"

#include <sstream>
#include <fstream>
#include <assert.h>
#include <map>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
namespace cpe
{

std::vector<int> split_face_data2(std::string const& face_data_str)
{
    std::vector<int> data;
    std::string current_str=face_data_str;

    while(current_str.length()>0)
    {
        while(current_str.length()>0 && current_str[0]=='/')
        {
            std::string temp_str=current_str.substr(1,current_str.length()-1);
            current_str=temp_str;
        }

        int value;
        std::stringstream tokenizer(current_str);
        tokenizer>>value;
        data.push_back(value);

        std::string residual;
        tokenizer>>residual;

        current_str=residual;
    }

    return data;
}

void read_vertex_obj2(std::stringstream& tokens,obj_structure2& obj)
{
    vec3 v;
    tokens >> v.x();
    //std::cout << v.x();
    tokens >> v.y();
   // std::cout << v.y();
    tokens >> v.z();
    obj.data_vertex.push_back(v);
}

void read_texture_obj2(std::stringstream& tokens,obj_structure2& obj)
{
    vec2 t;
    tokens >> t.x();
    tokens >> t.y();
    obj.data_texture.push_back(t);
}

void read_normal_obj2(std::stringstream& tokens,obj_structure2& obj)
{
    vec3 n;
    tokens >> n.x();
    tokens >> n.y();
    tokens >> n.z();
    obj.data_normal.push_back(n);
}

void read_name_obj2(std::stringstream &tokens, obj_structure2 &obj)
{
    std::string name;
    tokens >> name;
    obj.object_name = name;
    //std::cout << name;
}

void read_face_obj2(std::stringstream& tokens,obj_structure2& obj)
{
    std::vector<std::vector<int> > face_data;
    while(tokens.good())
    {
        std::string polygon_index_str;
        tokens >> polygon_index_str;

        std::vector<int> const current_data=split_face_data2(polygon_index_str);
        face_data.push_back(current_data);
    }

    std::vector<int> temp_vertex;
    std::vector<int> temp_texture;
    std::vector<int> temp_normal;
    for(auto const& index_face : face_data)
    {
        int const N_dim=index_face.size();
        for(int k_dim=0;k_dim<N_dim;++k_dim)
        {
            int const value=index_face[k_dim];

            switch(k_dim)
            {
            case 0:
                temp_vertex.push_back(value-1);
                break;
            case 1:
                temp_texture.push_back(value-1);
                break;
            case 2:
                temp_normal.push_back(value-1);
                break;
            default:
                std::cerr<<"Error reading file "<<std::endl;
                exit(1);
            }
        }
    }

    if(temp_vertex.size()>0)
        obj.data_face_vertex.push_back(temp_vertex);
    if(temp_texture.size()>0)
        obj.data_face_texture.push_back(temp_texture);
    if(temp_normal.size()>0)
        obj.data_face_normal.push_back(temp_normal);
}


std::vector<obj_structure2> load_file_obj_structure2(std::string const& filename)
{
    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_cpe("Cannot open file "+filename,MACRO_EXCEPTION_PARAMETER);

    std::string buffer;

    std::string mtlfile;
    std::vector<obj_structure2> structures;
    obj_structure2 structure;
    // TO DO
    // Ajout des gestions materiauxx, de gestion iondex, gestion nom ...

    //need to indicate the changement of object
    int objects = 0;
    bool newObj= false;
    //read the whole file
    while(fid.good()==true)
    {
        //read line
        std::getline(fid,buffer);

        if(buffer.size()>0)
        {
            std::stringstream tokens_buffer(buffer);
            std::string first_word;
            tokens_buffer>>first_word;




            //skip comments
            if(first_word.length()>0 && first_word[0]!='#')
            {
                //std::cout << first_word;
                if(first_word == "mtllib")
                    tokens_buffer>>mtlfile;

                if(first_word=="g"){
                    //est ce que cest un nouvel objet
                    if(newObj && objects >0){
                        structures.push_back(structure);
                        clean_structure(structure);
                    }
                    //mise a jour du nouvel objet
                    read_name_obj2(tokens_buffer,structure);

                }

                    //vertices
                    if(first_word=="v")
                        read_vertex_obj2(tokens_buffer,structure);

                    //texture
                    if(first_word=="vt")
                        read_texture_obj2(tokens_buffer,structure);

                    //normal
                    if(first_word=="vn")
                        read_normal_obj2(tokens_buffer,structure);

                    //connectivity
                    if(first_word=="f")
                        read_face_obj2(tokens_buffer,structure);

            }

        }

    }

    return structures;
}



std::vector<mesh> load_mesh_file_obj2(const std::string &filename)
{
    std::vector<mesh> meshes_loaded;
    std::vector<obj_structure2> obj = load_file_obj_structure2(filename);


    //get object name
    //extract this object (while not g) in a tmp file
    //parse
    //test
    //push in vector<mesh>
    return meshes_loaded;
}

void clean_structure(obj_structure2 &obj)
{
    obj.data_face_normal.clear();
    obj.data_face_texture.clear();
    obj.data_face_vertex.clear();
    obj.data_normal.clear();
    obj.data_texture.clear();
    obj.data_vertex.clear();
    //material index object name and ][ will just be reapled
}
}
