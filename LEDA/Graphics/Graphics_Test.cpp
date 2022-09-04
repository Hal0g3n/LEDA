/**
 * @file        Graphics_Test.cpp
 * @author      your name (you@domain.com)
 * @brief       A test for graphics. Skill issue?
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include "pch.h"
#include "LEDA_Graphics.h"

#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void resize(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);
void draw(GLFWwindow* window);

// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";
const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.987f, 0.654f, 0.321f, 1.0f);\n"
    "}\n\0";

int LEDA::test() {

    std::cout << "graphics test runs!\n";

    glfwInit();

    std::cout << "1\n";

    // OpenGL version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for os x and ios
    #endif

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Skill Issue?", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error: failed to create GLFWindow\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // be glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: failed to initialize GLAD! [>:( <-- not glad]\n";
        return -1;
    }

    // set viewport and viewport resize event function
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, resize);

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success; // WHY integer
    char errorLog[512]; // c-style, it's opengl anyway (512 character max)
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cout << "Error: vertex shader compilation failed!\n" << errorLog << '\n';
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors again
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cout << "Error: fragment shader compilation failed!\n" << errorLog << '\n';
    }

    // link both shaders together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, errorLog);
        std::cout << "Error: shader linker failed!\n" << errorLog << '\n';
    }

    // after linking, the other shaders can be deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // draw the square!
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = { // 0-indexed
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // vertex buffer object, vertex array object, element buffer object
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // main loop
    while (!glfwWindowShouldClose(window)) { // while esc button is not pressed...

        input(window);
        
        draw(window);
        
        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    std::cout << "graphics test ends!\n";

    return 0;
}

void resize(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

}

void input(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // be funny and use GLFW_TRUE
    }

}

void draw(GLFWwindow* window) {

    glClearColor(0.123f, 0.456f, 0.789f, 1.0f); // around #1f74c9
    glClear(GL_COLOR_BUFFER_BIT);

}