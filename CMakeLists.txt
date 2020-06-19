cmake_minimum_required(VERSION 3.12)

project(png2pdf)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

add_definitions(-DPNG2PDF_VERSION="${VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(LIBPODOFO REQUIRED)
if(LIBPODOFO_FOUND)
	message(STATUS "Found the PoDoFo library")
endif(LIBPODOFO_FOUND)

find_package(PNG REQUIRED)
if(PNG_FOUND)
	message(STATUS "Found the PNG library")
endif(PNG_FOUND)

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

add_executable(png2pdf src/main.cpp src/Converter.cpp)

target_link_libraries(
  png2pdf
  ${LIBPODOFO_LIBRARY}
  ${PNG_LIBRARY}
  ${Boost_LIBRARIES}
)

install(TARGETS png2pdf RUNTIME DESTINATION bin)
