GLFW_INCLUDE_PATH="./deps/GLFW/include/"
GLFW_LIB_PATH="./deps/GLFW/lib/"
GLFW_STATIC_LIB="./deps/GLFW/lib/libglfw3.a"

GLEW_INCLUDE_PATH="./deps/GLEW/include/"
GLEW_LIB_PATH="./deps/GLEW/lib/"
GLEW_STATIC_LIB="./deps/GLEW/lib/libGLEW.a"

STATIC_LIBS="$GLEW_STATIC_LIB $GLFW_STATIC_LIB"
DYNAMIC_LIBS="-lpthread -lGL -lm -ldl -lX11 -lpthread"

OUT_FILE="app"

g++ -I$GLFW_INCLUDE_PATH\
    -I$GLEW_INCLUDE_PATH\
    -L$GLFW_LIB_PATH\
    src/application.cpp\
    src/IndexBuffer.cpp\
    src/Renderer.cpp\
    src/VertexBuffer.cpp\
    $STATIC_LIBS\
    $DYNAMIC_LIBS\
    -o $OUT_FILE
