cmake_minimum_required(VERSION 3.22)
project(trollworks-sdk-imgui-sdl CXX)

file(GLOB_RECURSE TROLLWORKS_IMGUI_SDL_SOURCES
  ${PROJECT_SOURCE_DIR}/src/*.cpp
  ${PROJECT_SOURCE_DIR}/vendor/imgui/*.cpp
)

file(GLOB_RECURSE TROLLWORKS_IMGUI_SDL_HEADERS
  ${PROJECT_SOURCE_DIR}/include/*.hpp
  ${PROJECT_SOURCE_DIR}/vendor/imgui/*.h
)

add_library(${PROJECT_NAME} STATIC
  ${TROLLWORKS_IMGUI_SDL_SOURCES}
  ${TROLLWORKS_IMGUI_SDL_HEADERS}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-core/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-backend-sdl/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-backend-sdl/vendor/nlohmann-json/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-backend-sdl/vendor/SDL/upstream/include
  PRIVATE ${PROJECT_SOURCE_DIR}/vendor/trollworks-sdk-backend-sdl/vendor/SDL_image/upstream/include
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -O2 -Wall -Wextra -std=c++23
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/debug")
else()
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/release")
endif()
