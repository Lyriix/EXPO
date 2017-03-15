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
void read_material_info(std::stringstream& tokens, obj_structure2& obj, int objects)
{
    std::string mtlname;
    tokens >> mtlname;
    obj.material_name = mtlname;
    obj.material_index = 0;//objects;
    //read the corresponding material in mtl file thanks to name and index

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
        int const N_dim=index_face.size(); //TOFIX if there is no texture , we dont add the normal values cause N_dim = 2 (no textures)
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
    bool newObj= true;
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
                    objects++;

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
                //material indexing
                if(first_word=="usemtl")
                    read_material_info(tokens_buffer, structure, objects);
            }

        }

    }
    structures.push_back(structure);// la derniere a pousser
    return structures;
}



std::vector<mesh> load_mesh_file_obj2(const std::string &filename)
{
    std::vector<mesh> meshes_loaded;

    std::vector<obj_structure2> objects = load_file_obj_structure2(filename);

    //FIX ME : Add Normal support
    // do the verification for each object
    int N_vertex_total =0;
    int N_texture_total = 0;

    for(auto& obj : objects)
    {
        //FIX ME: Add normal support
        mesh mesh_loaded;

        bool const is_vertex=obj.data_vertex.size()>0 && obj.data_face_vertex.size()>0;
        bool const is_texture=obj.data_texture.size()>0 && obj.data_face_texture.size()>0;
        //bool const is_normal=obj.data_normal.size()>0 && obj.data_face_normal.size()>0;

        if(is_vertex && !is_texture)
        {
            int const N_face=obj.data_face_vertex.size();
            for(int k_face=0;k_face<N_face;++k_face)
            {
                auto const& polygon=obj.data_face_vertex[k_face];
                int const dim=polygon.size();

                assert(dim>=2);
                for(int k=2;k<dim;++k)
                    mesh_loaded.add_triangle_index({polygon[0]-N_vertex_total,polygon[1]-N_vertex_total,polygon[k]-N_vertex_total});
            }

            int const N_vertex=obj.data_vertex.size();
            N_vertex_total += N_vertex;

            for(int k_vertex=0;k_vertex<N_vertex;++k_vertex)
                mesh_loaded.add_vertex(obj.data_vertex[k_vertex]);
        }

        if(is_vertex && is_texture)
        {
            std::vector<vec3> data_vertex;
            std::vector<vec2> data_texture;

            std::map<int,int> map_vertex;
            std::map<int,int> map_texture;
            long int counter_max=0;

            int const N_face=obj.data_face_vertex.size();

            assert(static_cast<int>(obj.data_face_texture.size())==N_face);
            for(int k_face=0;k_face<N_face;++k_face)
            {
                std::vector<int> const& face_vertex=obj.data_face_vertex[k_face];
                std::vector<int> const& face_texture=obj.data_face_texture[k_face];

                int const dim=face_vertex.size();

                assert(dim>2);
                assert(static_cast<int>(face_texture.size())==dim);
                for(int k_dim=0;k_dim<dim;++k_dim)
                {
                    int const idx_vertex=face_vertex[k_dim] - N_vertex_total;
                    int const idx_texture=face_texture[k_dim] - N_texture_total;

                    std::map<int,int>::const_iterator it_vertex=map_vertex.find(idx_vertex);
                    std::map<int,int>::const_iterator it_texture=map_texture.find(idx_texture);

                    if(it_vertex==map_vertex.end() || it_texture==map_texture.end())
                    {
                        map_vertex[idx_vertex]=counter_max;
                        map_texture[idx_texture]=counter_max;

                        counter_max++;
                        assert(static_cast<int>(obj.data_vertex.size())>idx_vertex);
                        assert(static_cast<int>(obj.data_texture.size())>idx_texture);

                        mesh_loaded.add_vertex(obj.data_vertex[idx_vertex]);
                        mesh_loaded.add_texture_coord(obj.data_texture[idx_texture]);

                        data_vertex.push_back(obj.data_vertex[idx_vertex]);
                        data_texture.push_back(obj.data_texture[idx_texture]);

                        assert(static_cast<int>(data_vertex.size())==counter_max);
                        assert(static_cast<int>(data_texture.size())==counter_max);
                    }
                }

                int const index_0=map_vertex[face_vertex[0]-N_vertex_total];
                for(int k_dim=1;k_dim<dim-1;++k_dim)
                {
                    int const index_1=map_vertex[face_vertex[k_dim] - N_vertex_total];
                    int const index_2=map_vertex[face_vertex[k_dim+1] - N_vertex_total];

                    mesh_loaded.add_triangle_index({index_0, index_1, index_2});
                }
            }
            N_vertex_total += obj.data_vertex.size();
            N_texture_total += obj.data_texture.size();
        }

        mesh_loaded.add_object_name(obj.object_name);
        mesh_loaded.add_material_index(obj.material_index);
        mesh_loaded.add_material_name(obj.material_name);

        mesh_loaded.fill_empty_field_by_default();
        ASSERT_CPE(mesh_loaded.valid_mesh(),"Mesh "+obj.object_name+" is invalid");

        meshes_loaded.push_back(mesh_loaded);
    }
    print_obj_info(meshes_loaded);
    return meshes_loaded;
}

void print_obj_info(std::vector<mesh> meshes)
{
    std::cout << "Loaded meshes informations " << std::endl;
    for(auto const& mesh:meshes)
    {
        std::cout <<"Object : " << mesh.get_object_name() <<", linked to mtl "<< mesh.get_material_name() << " with index "<<mesh.get_material_index()<<std::endl;
        std::cout <<"         Size of vertex : "<< mesh.size_vertex()
                 << ", normal : "<< mesh.size_normal()
                 << ", color : " << mesh.size_color()
                 << ", tex_coord "<< mesh.size_texture_coord()
                 <<", connectivity "<< mesh.size_connectivity() << std::endl;
    }
}

void clean_structure(obj_structure2 &obj)
{
    obj.data_face_normal.clear();
    obj.data_face_texture.clear();
    obj.data_face_vertex.clear();
    obj.data_normal.clear();
    obj.data_texture.clear();
    obj.data_vertex.clear();
    obj.material_index=-1;
    obj.material_name="";
    obj.object_name="";
    //material index object name and ][ will just be reapled
}
}
