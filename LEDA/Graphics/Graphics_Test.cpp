/**
 * @file        Graphics_Test.h
 * @author      your name (you@domain.com)
 * @brief       A test for graphics. Skill issue?
 * @version     0.1
 * @date        22-08-2022
 *
 * @copyright   Copyright (c) 2022
 */

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void resize(GLFWwindow* window, int width, int height);
void input(GLFWwindow* window);
void draw(GLFWwindow* window);

// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;


int main() {

    glfwInit();

    // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac, haha

    // create GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Skill Issue?", NULL, NULL);
    if (window == NULL) {
        std::cout << "Error: failed to create GLFWindow" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // set viewport and viewport resize event function
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, resize);

    // be glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: failed to initialize GLAD! [>:( <-- not glad]" << '\n';
        return -1;
    }

    // main loop
    while (!glfwWindowShouldClose(window)) // while esc button is not pressed...
    {
        input(window);
        
        draw(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void resize(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

}

void input(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

}

void draw(GLFWwindow* window) {

    glClearColor(0.123f, 0.456f, 0.789f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

}