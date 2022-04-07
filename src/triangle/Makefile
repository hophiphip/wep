compile:
	gcc main.cpp -std=c++20 -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lglad -lstdc++ -Wall -Wextra -o main

module:
	emcc main.cpp -std=c++20 -lglfw -lGL -lX11 -lpthread -ldl -lstdc++ -Wall -Wextra -s USE_GLFW=3 -s WASM=3 -s MAX_WEBGL_VERSION=3 -s MIN_WEBGL_VERSION=3 -s EXPORT_ES6=1 -s MODULARIZE=1 -s EXPORT_NAME=triangle -s INVOKE_RUN=0 -s EXPORTED_FUNCTIONS='["_main"]' -s EXPORTED_RUNTIME_METHODS='["callMain"]' -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 -s EXIT_RUNTIME=0 -o triangle.js

page:
	emcc main.cpp -std=c++20 -lglfw -lGL -lX11 -lpthread -ldl -lstdc++ -Wall -Wextra -s USE_GLFW=3 -s WASM=3 -s MAX_WEBGL_VERSION=3 -s MIN_WEBGL_VERSION=3 -o page.html