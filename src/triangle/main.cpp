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

const float triangle_vertices[] = {
     0.0f,  0.5f,  0.0f,
     0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

const char *vertex_shader_src = 
    #ifdef __EMSCRIPTEN__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragment_shader_src = 
    #ifdef __EMSCRIPTEN__
    "#version 300 es\n"
    #else
    "#version 330 core\n"
    #endif
    "precision mediump float;\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n"; 

const int log_buffer_size = 512;

char log_buffer[log_buffer_size];

std::function<void()> loop_cycle;

void error_callback(int, const char *);
void on_window_resize(GLFWwindow *, int , int);
void process_input(GLFWwindow *);
void main_loop();

int main() {
    GLuint vertex_buffer_object = 0,
           vertex_array_object  = 0,
           vertex_shader        = 0, 
           fragment_shader      = 0, 
           shader_program       = 0;

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

    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shader_program = glCreateProgram();

    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);

    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);

    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    glLinkProgram(shader_program);

    int shader_program_link_status;

    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_link_status);
    if (!shader_program_link_status) {
        glGetProgramInfoLog(shader_program, log_buffer_size, NULL, log_buffer);
        fprintf(stderr, "%s\n", log_buffer);
        return 3;
    }

    int shader_compilation_status;

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_compilation_status);
    if (!shader_compilation_status) {
        glGetShaderInfoLog(vertex_shader, log_buffer_size, NULL, log_buffer);
        fprintf(stderr, "%s\n", log_buffer);
        return 4;
    }

    loop_cycle = [&] {
        process_input(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vertex_array_object);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    };

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(main_loop, 0, true);
    #else
        while (!glfwWindowShouldClose(window)) {
            main_loop();
        }
    #endif
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

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