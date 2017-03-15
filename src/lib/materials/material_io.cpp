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

#include "material_io.hpp"

#include "material.hpp"
#include "../common/error_handling.hpp"

#include "format/material_io_mtl.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <cassert>

namespace cpe
{

std::vector<material> load_material_file(const std::string& filename)
{
    if(filename.find(".mtl")!=std::string::npos || filename.find(".MTL")!=std::string::npos)
        return load_material_file_mtl(filename);
    else
        throw cpe::exception_cpe("Unknown extension for material file "+filename,EXCEPTION_PARAMETERS_CPE);
}


}
