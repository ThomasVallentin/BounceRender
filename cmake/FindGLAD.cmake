find_path(GLAD_INCLUDE_DIR
        NAMES glad/glad.h
        HINTS ${GLAD_ROOT}
        PATH_SUFFIXES include)

find_library(GLAD_LIBRARIES
        NAMES glad.a glad.lib
        HINTS ${GLAD_ROOT}
        PATH_SUFFIXES lib)

set(GLAD_FOUND "NO")
if (GLAD_INCLUDE_DIR AND GLAD_LIBRARIES)
    set(GLAD_FOUND "YES")
    message("Found GLAD")
else ()
    message(SEND_ERROR "Could not find GLAD")
endif()
