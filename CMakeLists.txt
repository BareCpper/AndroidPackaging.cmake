# @note 3.20 required for `GENERATED` attribute to be project-wide i.e. Version.h isn't build until build-time
cmake_minimum_required(VERSION 3.20)

#include(GNUInstallDirs)
option(ANDROIDPACKAGING_BUILD_TESTING "Build unit-tests" YES)
option(ANDROIDPACKAGING_BUILD_EXAMPLES "Build examples" NO)

include(CMake/AndroidPackaging-Prerequisites.cmake)

# We support AndroidPackaging.cmake usage before `project(...)
# - This allows implicitly setting the Android Toolchain upon inclusion
# TODO: We could still set project but define the Android toolhcain here first.
get_directory_property(hasParent PARENT_DIRECTORY)
if ( NOT hasParent OR PROJECT_IS_TOP_LEVEL)
	project(AndroidPackaging.cmake)
endif()

include(CMake/AndroidPackaging.cmake)

add_subdirectory(Examples)
if ( NOT ANDROIDPACKAGING_BUILD_EXAMPLES)
    set_property(DIRECTORY Examples PROPERTY EXCLUDE_FROM_ALL)
endif()