# Render plain color

## References
- [Learn OpenGL](https://learnopengl.com/Introduction)
- [Emscripten](https://emscripten.org/)

## Requirements
- [GCC](https://gcc.gnu.org/)
- [Make](https://www.gnu.org/software/make/)
- [GLFW](https://www.glfw.org/download.html)
- [GLAD](https://glad.dav1d.de/)
- [Emscripten](https://emscripten.org/)
 
OR

- [Docker](https://www.docker.com/)

## Compile JS/WASM module (with Docker)
1. Make sure you have `Docker` installed.
2. Compile `JS` module
```sh
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk make module
``` 
**Reference**: https://hub.docker.com/r/emscripten/emsdk

## Compile binary (without Docker)
### Setup
1. Make sure you have `gcc` or `clang` (or any other C/C++ compiler) installed.
2. Install `GLFW`: https://www.glfw.org/download.html
3. Install `GLAD`: https://glad.dav1d.de/
    - Unzip downloaded `glad.zip`.
    - Go to downloaded `glad` directory.
    - Copy `include/{glad,KHR}` folders to `/usr/include`. 
        (Or into project local include directory. **NOTE** This way `GLAD` must be included as `#include "glad/glad.h"`).
    - Compile `glad.c` in `glad/src`:
        ```sh
        g++ -c glad.c
        ```
    - Compile static library
        ```sh
        ar rcs libglad.a glad.o
        ```
    - Copy `libglad.a` to `/usr/lib` (Or into project local lib directory).
### Compilation
Compile executable
```sh
make compile
```

## Compile JS/WASM module (without Docker)
```sh
make module
```