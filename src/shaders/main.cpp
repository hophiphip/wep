#include <functional>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

bool pause = false;

const int width  = 800,
          height = 600;

const float triangle_vertices[] = {
     // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};

const std::string gl_version = 
    #ifdef __EMSCRIPTEN__
        "#version 300 es\n"
    #else
        "#version 330 core\n"
    #endif
;

const std::string vertex_shader_src = gl_version + R""""(
    layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
    layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
    
    out vec3 ourColor; // output a color to the fragment shader

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor; // set ourColor to the input color we got from the vertex data
    } 
)"""";

const std::string fragment_shader_src = gl_version + R""""(
    precision mediump float;
    
    out vec4 FragColor;  
    in vec3 ourColor;
    
    void main()
    {
        FragColor = vec4(ourColor, 1.0);
    }
)"""";

const int log_buffer_size = 512;

char log_buffer[log_buffer_size];

std::function<void()> loop_cycle;

extern "C" { // https://stackoverflow.com/questions/63877873/emscripten-undefined-exported-function
    void set_pause();
    void unset_pause();
    void toggle_pause();
}

void error_callback(int, const char *);
void on_window_resize(GLFWwindow *, int , int);
void key_callback(GLFWwindow*, int, int, int, int);
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

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(width, height, "GL", NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to initialize window\n");
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);

    #ifdef __EMSCRIPTEN__
    #else
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            fprintf(stderr, "failed to initialize GLAD\n");
            return 2;
        }
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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shader_program = glCreateProgram();

    auto vs = vertex_shader_src.c_str(),
         fs = fragment_shader_src.c_str();

    glShaderSource(vertex_shader, 1, &vs, NULL);
    glCompileShader(vertex_shader);

    glShaderSource(fragment_shader, 1, &fs, NULL);
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
        glfwPollEvents();

        if (!pause) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shader_program);

            float time_value  = glfwGetTime();
            float green_value = (sin(time_value) / 2.0f) + 0.5f;
            int vertex_color_location = glGetUniformLocation(shader_program, "ourColor");
            glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);

            glBindVertexArray(vertex_array_object);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            glfwSwapBuffers(window);
        }
    };

    glfwSetKeyCallback(window, key_callback);

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
    fprintf(stderr, "Error[%d]: %s\n", error, description);
}

void on_window_resize(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void set_pause() {
    pause = true;
}

void unset_pause() {
    pause = false;
}

void toggle_pause() {
    pause = !pause;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        #ifdef __EMSCRIPTEN__
        #else
            toggle_pause();
        #endif
    }
}