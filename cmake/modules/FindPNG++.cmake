if(PNG++_FIND_QUIETLY)
  set(_FIND_PNG_ARG QUIET)
endif()

find_package(PNG ${_FIND_PNG_ARG})

if(PNG_FOUND)
  find_path(PNG++_INCLUDE_DIRS
    NAMES png++/png.hpp
    PATHS
      "${PNG++_DIR}/include"
      "${PNG++_DIR}/src"
      "${PNG++_DIR}"
      /usr/include
      /usr/local/include
  )

  if(PNG++_INCLUDE_DIRS)
    set(PNG++_FOUND TRUE)
    set(PNG++_INCLUDE_DIRS ${PNG++_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})
    set(PNG++_LIBRARIES ${PNG_LIBRARIES})
  endif(PNG++_INCLUDE_DIRS)
endif(PNG_FOUND)
