# Copyright 2011,2012,2016,2018,2019 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-leo
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

list(APPEND leo_sources
	utils/helper.cc
    generic_antenna.cc
	yagi_antenna_impl.cc
	custom_antenna_impl.cc
	helix_antenna_impl.cc
	monopole_antenna_impl.cc
	dipole_antenna_impl.cc
	parabolic_reflector_antenna_impl.cc
	quadrifilar_helix_antenna_impl.cc
	satellite.cc
	tracker.cc
	generic_attenuation.cc
	atmospheric_gases_itu_impl.cc
	atmospheric_gases_regression_impl.cc
	free_space_path_loss_impl.cc
	precipitation_itu_impl.cc
	generic_noise.cc
	white_gaussian_noise.cc
	antenna_pointing_loss_impl.cc
	link_margin.cc
	generic_model.cc
	leo_model_impl.cc
	channel_model_impl.cc
)

set(leo_sources "${leo_sources}" PARENT_SCOPE)
if(NOT leo_sources)
    MESSAGE(STATUS "No C++ sources... skipping lib/")
    return()
endif(NOT leo_sources)

add_library(gnuradio-leo SHARED ${leo_sources})
set_property(TARGET sgp4 PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(gnuradio-leo PUBLIC
	gnuradio::gnuradio-runtime
	gnuradio::gnuradio-blocks
	gnuradio::gnuradio-pmt
	${Boost_LIBRARIES}
	Volk::volk
	PRIVATE sgp4
)

target_include_directories(gnuradio-leo
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
	PUBLIC $<BUILD_INTERFACE:${sgp4_SOURCE_DIR}>
    PUBLIC $<INSTALL_INTERFACE:include>
  )
set_target_properties(gnuradio-leo PROPERTIES DEFINE_SYMBOL "gnuradio_leo_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-leo PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

target_compile_definitions(gnuradio-leo
    PUBLIC GR_LEO_REL_DATA_PATH=\"${GR_PKG_DATA_DIR}\"
)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-leo)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND test_leo_sources
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-leo)

if(NOT test_leo_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT test_leo_sources)

foreach(qa_file ${test_leo_sources})
    GR_ADD_CPP_TEST("leo_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
