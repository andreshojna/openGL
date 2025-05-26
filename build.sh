INCLUDE_PATH="./deps/GLFW/include/"
LIB_PATH="./deps/GLFW/lib/"

LIBS="-lglfw3 -lpthread -lGL -lm -ldl -lX11 -lpthread"

OUT_FILE="app"

# g++ -I$INCLUDE_PATH -L$LIB_PATH src/application.cpp -lpthread
g++ -I$INCLUDE_PATH -L$LIB_PATH src/application.cpp $LIBS -o $OUT_FILE
