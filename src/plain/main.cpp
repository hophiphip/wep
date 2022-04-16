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

    bool pause = false;

    GLFWwindow *window;

    const std::function<void()> draw = [] {
        glfwPollEvents();

        if (!pause) {
            glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
        }
    };

    void setPause(const bool isPaused) {
        pause = isPaused;
    }

    int initializeGlfw(GLFWerrorfun onErrorCallback) {
        glfwSetErrorCallback(onErrorCallback);

        if (!glfwInit()) {
            fprintf(stderr, "failed to initialzie glfw\n");
            return 1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        return 0;
    }

    int initializeWindow() {
        window = glfwCreateWindow(width, height, "GL", NULL, NULL);

        if (!window) {
            fprintf(stderr, "failed to initialize window\n");
            glfwTerminate();
            return 1;
        }

        glfwMakeContextCurrent(window);

        return 0;
    }

    void initializeGl(GLFWframebuffersizefun onWindowResize, GLFWkeyfun onKeyCallback) {
        #ifdef __EMSCRIPTEN__
        #else
            gladLoadGL();
        #endif

        glfwSwapInterval(1);

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window, onWindowResize);

        glfwSetKeyCallback(window, onKeyCallback);
    }

    void mainLoop() { draw(); };

    void start() {
        #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(mainLoop, 0, true);
        #else
            while (!glfwWindowShouldClose(window)) {
                mainLoop();
            }
        #endif
    }

    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

extern "C" { // // https://stackoverflow.com/questions/63877873/emscripten-undefined-exported-function
    void setPause(const bool isPaused) {
        Renderer::setPause(isPaused);
    }
}

void onErrorCallback(int, const char *);
void onWindowResize(GLFWwindow *, int , int);
void onKeyCallback(GLFWwindow*, int, int, int, int);

int main() {
    if (Renderer::initializeGlfw(onErrorCallback)) {
        return 1;
    }

    if (Renderer::initializeWindow()) {
        return 1;
    }
    
    Renderer::initializeGl(onWindowResize, onKeyCallback);

    Renderer::start();
    
    Renderer::cleanup();

    return 0;
}

void onErrorCallback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void onWindowResize(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        #ifdef __EMSCRIPTEN__
        #else
            Renderer::setPause(!Renderer::pause);
        #endif
    }
}