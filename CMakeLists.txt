cmake_minimum_required(VERSION 3.5)
project(sdlGUI)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/screen.cpp include/screen.h include/GUI_header.h src/widget.cpp include/widget.h include/sdlGUI.h src/section.cpp include/section.h src/button.cpp include/button.h src/push_button.cpp include/push_button.h)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})
include_directories(${OpenGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
add_library(sdlGUI ${SOURCE_FILES} ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${OpenGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(sdlGUI ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

add_executable(testGUI main_test.cpp)
target_link_libraries(testGUI sdlGUI)