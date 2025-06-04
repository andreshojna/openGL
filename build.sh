GLFW_INCLUDE_PATH="./deps/GLFW/include/"
GLEW_INCLUDE_PATH="./deps/GLEW/include/"
VENDOR_INCLUDE_PATH="./src/vendor/"

GLFW_LIB_PATH="./deps/GLFW/lib/"
GLEW_LIB_PATH="./deps/GLEW/lib/"

GLFW_STATIC_LIB="./deps/GLFW/lib/libglfw3.a"
GLEW_STATIC_LIB="./deps/GLEW/lib/libGLEW.a"

STATIC_LIBS="$GLEW_STATIC_LIB $GLFW_STATIC_LIB"
DYNAMIC_LIBS="-lpthread -lGL -lm -ldl -lX11 -lpthread"

OUT_FILE="app"

g++ -I$GLFW_INCLUDE_PATH\
    -I$GLEW_INCLUDE_PATH\
    -I$VENDOR_INCLUDE_PATH\
    -L$GLFW_LIB_PATH\
    src/vendor/stb_image/stb_image.cpp\
    src/application.cpp\
    src/IndexBuffer.cpp\
    src/Renderer.cpp\
    src/Shader.cpp\
    src/Texture.cpp\
    src/VertexArray.cpp\
    src/VertexBuffer.cpp\
    src/VertexBufferLayout.cpp\
    $STATIC_LIBS\
    $DYNAMIC_LIBS\
    -o $OUT_FILE
