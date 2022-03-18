#.rst:
# Find ImGui
# -------------
#
# Finds the ImGui library. This module defines:
#
#  ImGui_FOUND                - True if ImGui is found
#  ImGui_INCLUDE_DIR          - The include directory of ImGui
#  ImGui_SOURCES              - The list of sources to build ImGui
#
# Additionally these variables are defined for internal usage:
#
#  ImGui_INCLUDE_DIR          - Include dir
#

# Finding the root directory of ImGui
find_path(ImGui_INCLUDE_DIR NAMES imgui.h
        HINTS ${ImGui_ROOT} ${ImGui_DIR})
mark_as_advanced(ImGui_INCLUDE_DIR)

if(NOT ImGui_INCLUDE_DIR)
    message(SEND_ERROR "Could not found ImGui.\nTry set ImGui_ROOT or ImGui_DIR.\n" )
endif()

# Find components
file(GLOB ImGui_SOURCES ${ImGui_INCLUDE_DIR}/*.cpp)

if(NOT ImGui_SOURCES)
    message(SEND_ERROR "Could not found any sources for ImGui.\nIs \"${ImGui_INCLUDE_DIR}\" a proper ImGui root directory ?\n" )
endif()
mark_as_advanced(ImGui_SOURCES)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ImGui
        REQUIRED_VARS ImGui_INCLUDE_DIR ImGui_SOURCES HANDLE_COMPONENTS)