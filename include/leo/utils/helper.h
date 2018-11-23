/*
 * Copyright 2011 Free Software Foundation, Inc.
 *
 * This file was generated by gr_modtool, a tool from the GNU Radio framework
 * This file is a part of gr-leo
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDE_LEO_HELPER_H_
#define INCLUDE_LEO_HELPER_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <leo/api.h>

namespace gr
{
  namespace leo
  {
    namespace utils
    {
      float
      parser_ITU_heatmap (std::string lat_file, std::string lon_file,
                          std::string heatmap_file, float lon, float lat);

      float
      degrees_to_radians(float degrees);

      float
      radians_to_degrees(float radians);
    }
  }
}

#endif /* INCLUDE_LEO_LOG_H_ */
