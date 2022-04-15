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

namespace Renderer {
    const int width = 800, height = 600;

    GLFWwindow *window;

    const std::function<void()> draw = [] {
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    int initialize_glfw(GLFWerrorfun on_error_callback) {
        glfwSetErrorCallback(on_error_callback);

        if (!glfwInit()) {
            fprintf(stderr, "failed to initialzie glfw\n");
            return 1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        return 0;
    }

    int initialize_window() {
        window = glfwCreateWindow(width, height, "GL", NULL, NULL);

        if (!window) {
            fprintf(stderr, "failed to initialize window\n");
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(window);

        return 0;
    }

    void initialize_gl(GLFWframebuffersizefun on_window_resize, GLFWkeyfun on_key_callback) {
        #ifdef __EMSCRIPTEN__
        #else
            gladLoadGL();
        #endif

        glfwSwapInterval(1);

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, on_window_resize);

        glfwSetKeyCallback(window, on_key_callback);
    }

    void main_loop() { draw(); };

    void start() {
        #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(main_loop, 0, true);
        #else
            while (!glfwWindowShouldClose(window)) {
                main_loop();
            }
        #endif
    }

    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

void on_error_callback(int, const char *);
void on_window_resize(GLFWwindow *, int , int);
void on_key_callback(GLFWwindow*, int, int, int, int);

int main() {
    if (Renderer::initialize_glfw(on_error_callback)) {
        return 1;
    }

    if (Renderer::initialize_window()) {
        return 1;
    }
    
    Renderer::initialize_gl(on_window_resize, on_key_callback);

    Renderer::start();
    
    Renderer::cleanup();

    return 0;
}

void on_error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void on_window_resize(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}