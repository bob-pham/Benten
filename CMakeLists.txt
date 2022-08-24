# CMakeList.txt : CMake project for benten, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(benten VERSION 1.0)

# Add source to this project's executable.
add_executable (benten benten.cpp)

add_library(picture Picture.cpp)
add_library(region Region.cpp)

include_directories(${PROJECT_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET benten PROPERTY CXX_STANDARD 20)
endif()

add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )
find_package(ImageMagick COMPONENTS Magick++)

include_directories(${ImageMagick_INCLUDE_DIRS})

target_link_libraries(region ${ImageMagick_LIBRARIES})

target_link_libraries(picture region)
target_link_libraries(picture ${ImageMagick_LIBRARIES})

target_link_libraries(benten picture)
target_link_libraries(benten ${ImageMagick_LIBRARIES})

