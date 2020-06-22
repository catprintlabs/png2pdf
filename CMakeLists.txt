cmake_minimum_required(VERSION 3.12)

project(png2pdf)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(EXECUTABLE "png2pdf")

add_definitions(-DPNG2PDF_VERSION="${VERSION}" -DPNG2PDF_EXECUTABLE="${EXECUTABLE}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX AND NOT APPLE)
	set(CMAKE_INSTALL_PREFIX /usr/local CACHE PATH "Installation path")
endif(UNIX AND NOT APPLE)

if(APPLE)
  add_definitions( -DPLATFORM_APPLE )
	message(STATUS "Mac OS X Architectures ${OSX_ARCHITECTURES}")
endif(APPLE)

IF(WIN32)
	SET (CMAKE_INSTALL_PREFIX c:/png2pdf CACHE PATH "Installation path")
endif(WIN32)

add_definitions(-DPREFIX="${CMAKE_INSTALL_PREFIX}")
message(STATUS "png2pdf will be installed under ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(LIBPODOFO REQUIRED)
if(LIBPODOFO_FOUND)
	message(STATUS "Found the PoDoFo library")
endif(LIBPODOFO_FOUND)

find_package(PNG++ REQUIRED)
if(PNG++_FOUND)
	message(STATUS "Found PNG++")
endif(PNG++_FOUND)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

add_executable(png2pdf src/main.cpp src/converter.cpp)

target_link_libraries(
  png2pdf
  ${LIBPODOFO_LIBRARY}
  ${PNG++_LIBRARIES}
  ${Boost_LIBRARIES}
)

install(TARGETS png2pdf RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A utility to convert transparent PNG files to the PDF format")
set(CPACK_PACKAGE_VENDOR "adamcreekroad")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/INSTALL.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_EXECUTABLES ${EXECUTABLE})

include(CPack)
