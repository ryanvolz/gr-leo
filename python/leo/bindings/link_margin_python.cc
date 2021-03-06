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
/* BINDTOOL_HEADER_FILE(link_margin.h)                                         */
/* BINDTOOL_HEADER_FILE_HASH(0)                                                    */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/leo/link_margin.h>

void bind_link_margin(py::module& m)
{

    using link_margin = ::gr::leo::link_margin;

    py::class_<link_margin, std::shared_ptr<link_margin>>(m, "link_margin")

        .def_static("make",
             &link_margin::make)

        .def("calc_link_margin",
             &link_margin::calc_link_margin,
             py::arg("total_loss_db"),
             py::arg("satellite_antenna_gain"),
             py::arg("tracker_antenna_gain"),
             py::arg("transmission_power_dbw"),
             py::arg("noise_floor"))

        ;

}
