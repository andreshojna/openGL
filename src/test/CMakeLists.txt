file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(Test ${SRC_FILES})

include_directories(
  ${CMAKE_SOURCE_DIR}/deps/GLEW/include/
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/vendor/
)