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
/* BINDTOOL_HEADER_FILE(monopole_antenna.h)                                   */
/* BINDTOOL_HEADER_FILE_HASH(0)                                                    */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/leo/monopole_antenna.h>

void bind_monopole_antenna(py::module& m)
{

    py::module m_antenna = m.def_submodule("antenna");
    using monopole_antenna = ::gr::leo::antenna::monopole_antenna;


    py::class_<monopole_antenna, gr::leo::generic_antenna,
               std::shared_ptr<monopole_antenna>>(m_antenna, "monopole_antenna")

        .def_static("make",
             &monopole_antenna::make,
             py::arg("type"),
             py::arg("frequency"),
             py::arg("polarization"),
             py::arg("pointing_error"))

        ;
}
