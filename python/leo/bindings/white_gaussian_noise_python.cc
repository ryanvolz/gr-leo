/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(white_gaussian_noise.h)                                   */
/* BINDTOOL_HEADER_FILE_HASH(0)                                                    */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/leo/white_gaussian_noise.h>

void bind_white_gaussian_noise(py::module& m)
{

    py::module m_noise = m.def_submodule("noise");
    using white_gaussian_noise = ::gr::leo::noise::white_gaussian_noise;

    py::class_<white_gaussian_noise, gr::leo::generic_noise,
               std::shared_ptr<white_gaussian_noise>>(m_noise, "white_gaussian_noise")

        .def_static("make",
             &white_gaussian_noise::make)

        .def("add_noise",
             &white_gaussian_noise::add_noise,
             py::arg("outbuf"),
             py::arg("inbuf"),
             py::arg("num"),
             py::arg("power"))

        ;
}
