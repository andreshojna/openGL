file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_library(ImGui ${SRC_FILES})

include_directories(
  ${CMAKE_SOURCE_DIR}/deps/GLEW/include/
  ${CMAKE_SOURCE_DIR}/deps/GLFW/include/
)