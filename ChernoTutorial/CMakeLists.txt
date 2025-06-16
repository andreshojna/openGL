cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Output to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add ImGui to CMake list
add_subdirectory(${CMAKE_SOURCE_DIR}/src/vendor/imgui/)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/test/)

# Include directories (e.g., your dependencies)
include_directories(
  deps/GLEW/include/
  deps/GLFW/include/
  src/
  src/vendor/
)

# Add the source files
set(SOURCES
  src/application.cpp
  src/IndexBuffer.cpp
  src/IndexBufferDynamic.cpp
  src/Renderer.cpp
  src/Shader.cpp
  src/Texture.cpp
  src/VertexArray.cpp
  src/VertexBuffer.cpp
  src/VertexBufferLayout.cpp
)
# To check if its using the precompiled headers
# add_compile_options(-H)

# Add executable
add_executable(app ${SOURCES})

# Precompiled header
target_precompile_headers(app PRIVATE "src/pch/pch.hpp")

# Link static libraries
target_link_libraries(app
  PRIVATE
  ${CMAKE_SOURCE_DIR}/deps/GLFW/lib/libglfw3.a
  ${CMAKE_SOURCE_DIR}/deps/GLEW/lib/libGLEW.a
  ${CMAKE_SOURCE_DIR}/src/vendor/stb_image/libstb_image.a
  ImGui
  Test
)

# Link dynamic system libraries
target_link_libraries(app
  PRIVATE
  pthread
  GL
  m
  dl
  X11
)