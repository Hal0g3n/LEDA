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
#include "LEDA_Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace LEDA;

// declare extern variable here
GLFWwindow* LEDA::window;

void resize(GLFWwindow* window, int width, int height);
void initializeInput();
void drawBackground();
void drawForeground();

// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

std::string vertexShaderCode = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 color;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   color = aColor;\n"
    "}\n\0";
std::string fragmentShaderCode = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "in vec3 color;\n"
    "void main() {\n"
    "   FragColor = vec4(color, 1.0f);\n"
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

    // create GLFW window (global)
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Skill Issue?", NULL, NULL);
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

    Shader theshader { vertexShaderCode, fragmentShaderCode };

    // draw the triangle!
    float vertices[] = {
    //   positions           colours
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top middle
    };
    unsigned int indices[] = { // 0-indexed
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    // vertex buffer object, vertex array object, element buffer object
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    initializeInput();

    // main loop
    while (!glfwWindowShouldClose(window)) { // while esc button is not pressed...

        doInput();
        
        drawBackground();

        drawForeground();
        
        // draw third triangle (wow!)
        theshader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    std::cout << "graphics test ends!\n";

    return 0;
}

void resize(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

}

void initializeInput() {

    addKeyTriggerCallback(KEY::KEY_ESCAPE, []() {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

}

void drawBackground() {

    glClearColor(0.123f, 0.456f, 0.789f, 1.0f); // around #1f74c9
    glClear(GL_COLOR_BUFFER_BIT);

}

void drawForeground() {

}