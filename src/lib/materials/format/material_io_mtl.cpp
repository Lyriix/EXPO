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

#include "material_io_mtl.hpp"
#include "../../common/error_handling.hpp"
#include "../../materials/material.hpp"

#include <sstream>
#include <fstream>

namespace cpe
{

std::vector<mtl_structure> load_file_mtl_structure(const std::string &filename)
{
    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_cpe("Cannot open file"+filename,MACRO_EXCEPTION_PARAMETER);

    std::string buffer;

    std::vector<mtl_structure> structures;
    mtl_structure structure;

    int materials = 0;
    int newMat = true;
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
                //skip newmtl BAH NON
                if(first_word=="newmtl")
                {
                    if(newMat && materials>0){
                        structures.push_back(structure);
                        //clean_structure(structure); No need her, we jsut replace all values
                    }
                    read_name_mtl(tokens_buffer, structure, materials);
                    materials++;
                }
                //Ns : phong specular component (Shininess)
                if( first_word=="Ns")
                    read_phong_mtl(tokens_buffer,structure);

                //Ka : Ambient color weighted by the ambient coefficient
                if( first_word=="Ka")
                    read_ambient_mtl(tokens_buffer,structure);

                //Kd : Diffuse color weighted by the diffuse coefficient
                if( first_word=="Kd" )
                    read_diffuse_mtl(tokens_buffer,structure);

                //Ks : Specular color weighted by the specular coefficient
                if( first_word=="Ks" )
                    read_specular_mtl(tokens_buffer,structure);

                //Ke : Emission color weighted by the emission coefficient
                if( first_word=="Ke" )
                    read_emission_mtl(tokens_buffer,structure);
                //Ni
                //d
                if( first_word=="d")
                    read_transparency_mtl(tokens_buffer, structure);
                //illum
                //mapKd
                //refl

            }
        }
    }
    structures.push_back(structure); //push the last one
    return structures;
}

std::vector<material> load_material_file_mtl(std::string const& filename)
{
    std::vector<material> materials_loaded;

    std::vector<mtl_structure> mtls = load_file_mtl_structure(filename);

    for(auto const& mtl : mtls)
    {
        material material_loaded;
        //We should do some verifications
        material_loaded.set_name(mtl.material_name);
        material_loaded.set_ambient(mtl.data_ambient);
        material_loaded.set_diffuse(mtl.data_diffuse);
        material_loaded.set_emission(mtl.data_emission);
        material_loaded.set_specular(mtl.data_specular);
        material_loaded.set_shininess(mtl.data_shininess);
        material_loaded.set_transparency(mtl.data_transparency);
        material_loaded.set_material_index(mtl.index);
        materials_loaded.push_back(material_loaded);
    }


    //print materials info
    print_materials_info(materials_loaded);
    return materials_loaded;
}

void read_name_mtl(std::stringstream &tokens, mtl_structure &mtl, int idx)
{
    std::string name;
    tokens >> name;
    mtl.material_name = name;
    mtl.index = idx;
}

void read_phong_mtl(std::stringstream& tokens, mtl_structure& mtl)
{
    float Ns;
    tokens >> Ns;
    mtl.data_shininess = Ns;
}

void read_ambient_mtl(std::stringstream& tokens, mtl_structure& mtl)
{
    vec3 Ka;
    tokens >> Ka.x();
    tokens >> Ka.y();
    tokens >> Ka.z();
    mtl.data_ambient = Ka;
}

void read_diffuse_mtl(std::stringstream& tokens, mtl_structure& mtl)
{
    vec3 Kd;
    tokens >> Kd.x();
    tokens >> Kd.y();
    tokens >> Kd.z();
    mtl.data_diffuse = Kd;
}

void read_specular_mtl(std::stringstream& tokens, mtl_structure& mtl)
{
    vec3 Ks;
    tokens >> Ks.x();
    tokens >> Ks.y();
    tokens >> Ks.z();
    mtl.data_specular = Ks;
}

void read_emission_mtl(std::stringstream& tokens, mtl_structure& mtl)
{
    vec3 Ke;
    tokens >> Ke.x();
    tokens >> Ke.y();
    tokens >> Ke.z();
    mtl.data_emission = Ke;
}

void read_transparency_mtl(std::stringstream &tokens, mtl_structure &mtl)
{
    float d;
    tokens >> d ;
    mtl.data_transparency = d;
}



void print_materials_info(std::vector<material> materials)
{
    std::cout<< "################" << std::endl;
    std::cout<< "Loaded materials info" << std::endl;
    for (auto const& mat : materials)
    {
        std::cout <<"Material : " << mat.name() <<" of index : " << mat.index() << std::endl;
        std::cout <<"       Ka : " << mat.ambient() << ", Kd :" << mat.diffuse() << std::endl;
        std::cout <<"       Ke : " << mat.emission() << ", Ks :" << mat.specular() << std::endl;
        std::cout <<"       Ns : " << mat.shininess() <<", d : " << mat.transparency() << std::endl;
    }
}
}
