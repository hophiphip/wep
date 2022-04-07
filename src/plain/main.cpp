#include <functional>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>

const int width  = 800,
          height = 600;

std::function<void()> loop_cycle;

void error_callback(int, const char *);
void on_window_resize(GLFWwindow *, int , int);
void process_input(GLFWwindow *);
void main_loop();

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "failed to initialzie glfw\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(width, height, "GL", NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to initialize window\n");
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);

    #ifdef __EMSCRIPTEN__
    #else
        gladLoadGL();
    #endif
    
    glfwSwapInterval(1);

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, on_window_resize);

    loop_cycle = [&] {
        process_input(window);

        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(main_loop, 0, true);
    #else
        while (!glfwWindowShouldClose(window)) {
            main_loop();
        }
    #endif
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void main_loop() { 
    loop_cycle(); 
}

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void on_window_resize(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}