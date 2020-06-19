find_path(PNG++_INCLUDE_DIR
  NAMES png++/png.hpp
  PATHS
    "${PNG++_DIR}/include"
    "${PNG++_DIR}/src"
    "${PNG++_DIR}"
    /usr/include
    /usr/local/include
)

if(PNG++_INCLUDE_DIR)
  set(PNG++_FOUND TRUE)
endif(PNG++_INCLUDE_DIR)
