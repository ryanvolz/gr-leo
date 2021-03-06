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
/* BINDTOOL_HEADER_FILE(tracker.h)                                         */
/* BINDTOOL_HEADER_FILE_HASH(0)                                                    */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/leo/satellite.h>
#include <gnuradio/leo/tracker.h>

void bind_tracker(py::module& m)
{

    using tracker = ::gr::leo::tracker;

    py::class_<tracker, std::shared_ptr<tracker>>(m, "tracker")
        .def(py::init<gr::leo::satellite::satellite_sptr, const double,
          const double, const double,
          const std::string &, const std::string &,
          const double, const double,
          const double,
          const double,
          gr::leo::generic_antenna::generic_antenna_sptr,
          gr::leo::generic_antenna::generic_antenna_sptr,
          const double,
          const double,
          const double>())

        .def(py::init<const std::string &, const std::string &,
          const std::string &, const double, const double,
          const double, const std::string &,
          const std::string &>())

        .def_static("make",
             &tracker::make,
             py::arg("satellite_info"),
             py::arg("gs_lat"),
             py::arg("gs_lon"),
             py::arg("gs_alt"),
             py::arg("obs_start"),
             py::arg("obs_end"),
             py::arg("time_resolution_us"),
             py::arg("comm_freq_tx"),
             py::arg("comm_freq_rx"),
             py::arg("tx_power_dbm"),
             py::arg("tx_antenna"),
             py::arg("rx_antenna"),
             py::arg("noise_figure"),
             py::arg("noise_temp"),
             py::arg("rx_bw"))

        .def("generate_passlist",
             &tracker::generate_passlist,
             py::arg("time_step"))

        .def("get_satellite_info",
             &tracker::get_satellite_info)

        .def("get_slant_range",
             &tracker::get_slant_range)

        .def("get_elevation_degrees",
             &tracker::get_elevation_degrees)
        
        .def("get_elevation_radians",
             &tracker::get_elevation_radians)

        .def("get_velocity",
             &tracker::get_velocity)

        .def("get_time_resolution_us",
             &tracker::get_time_resolution_us)

        .def("advance_time",
             &tracker::advance_time,
             py::arg("us"))

        .def("is_observation_over",
             &tracker::is_observation_over)

        .def("get_elapsed_time",
             &tracker::get_elapsed_time)

        .def("get_comm_freq_rx",
             &tracker::get_comm_freq_rx)

        .def("get_comm_freq_tx",
             &tracker::get_comm_freq_tx)

        .def("get_altitude",
             &tracker::get_altitude)

        .def("get_latitude",
             &tracker::get_latitude)

        .def("get_lontitude",
             &tracker::get_lontitude)

        .def("get_tx_antenna",
             &tracker::get_tx_antenna)

        .def("get_rx_antenna",
             &tracker::get_rx_antenna)

        .def("get_tx_power_dbm",
             &tracker::get_tx_power_dbm)

        .def("get_noise_figure",
             &tracker::get_noise_figure)

        .def("get_noise_temperature",
             &tracker::get_noise_temperature)

        .def("get_rx_bandwidth",
             &tracker::get_rx_bandwidth)
        ;

}
