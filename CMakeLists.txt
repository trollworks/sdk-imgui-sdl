cmake_minimum_required(VERSION 3.22)
project(trollworks-sdk-imgui-sdl CXX)

add_subdirectory(vendor/trollworks-sdk-backend-sdl)

file(GLOB_RECURSE TROLLWORKS_IMGUI_SDL_SOURCES
  ${PROJECT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE TROLLWORKS_IMGUI_SDL_HEADERS
  ${PROJECT_SOURCE_DIR}/include/*.hpp
)

set(IMGUI_SOURCES
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl2.cpp"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdlrenderer2.cpp"
)

set(IMGUI_HEADERS
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imconfig.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_internal.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_textedit.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/imstb_truetype.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/misc/cpp/imgui_stdlib.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdl2.h"
  "${PROJECT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_sdlrenderer2.h"
)

add_library(${PROJECT_NAME} STATIC
  ${TROLLWORKS_IMGUI_SDL_SOURCES}
  ${TROLLWORKS_IMGUI_SDL_HEADERS}
  ${IMGUI_SOURCES}
  ${IMGUI_HEADERS}
)

if(WIN32)
  target_link_libraries(${PROJECT_NAME}
    trollworks-sdk-backend-sdl
    SDL2-static
    SDL2_image
    opengl32
    glu32
  )
elseif(APPLE)
  target_link_libraries(${PROJECT_NAME}
    trollworks-sdk-backend-sdl
    SDL2-static
    SDL2_image
    opengl
    glu
  )
elseif(UNIX)
  target_link_libraries(${PROJECT_NAME}
    trollworks-sdk-backend-sdl
    SDL2-static
    SDL2_image
    opengl
    glu
  )
else()
  message(FATAL_ERROR "Platform not supported")
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-core/include
  PRIVATE "$<TARGET_PROPERTY:trollworks-sdk-backend-sdl,INTERFACE_INCLUDE_DIRECTORIES>"
  PRIVATE "$<TARGET_PROPERTY:nlohmann_json::nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>"
  PRIVATE "$<TARGET_PROPERTY:SDL2-static,INTERFACE_INCLUDE_DIRECTORIES>"
  PRIVATE "$<TARGET_PROPERTY:SDL2_image,INTERFACE_INCLUDE_DIRECTORIES>"
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -O2 -Wall -Werror -Wextra -std=c++23
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/debug")
else()
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/release")
endif()
