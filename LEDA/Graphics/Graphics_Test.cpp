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

using namespace LEDA::Input;

// declare extern variable here
GLFWwindow* LEDA::window;

void resize(GLFWwindow* window, int width, int height);
void initializeInput2();
void drawBackground();
void drawForeground();

// settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

double x = 200.0;
double y = 200.0;
double x2 = -400.0;
double y2 = -400.0;
double s = 1.0;
double rotation = 0.0;

std::string vertexShaderCode = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 color;\n"
    "uniform mat4 transform;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "   gl_Position = projection * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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

    // OpenGL version 3.3, latest version is 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 6
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

    Shader theShader { "solid" };

    // draw the triangle!
    float vertices[] = {
    //   positions           colours
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*
    // colours
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */

    glBindVertexArray(0);

    initializeInput();
    initializeInput2();

    // main loop
    while (!glfwWindowShouldClose(window)) { // while esc button is not pressed...

        doInput();

        if (keyPressed(KEY::KEY_UP) || keyPressed(KEY::KEY_W)) y += 0.1;
        if (keyPressed(KEY::KEY_DOWN) || keyPressed(KEY::KEY_S)) y -= 0.1;
        if (keyPressed(KEY::KEY_LEFT) || keyPressed(KEY::KEY_A)) x -= 0.1;
        if (keyPressed(KEY::KEY_RIGHT) || keyPressed(KEY::KEY_D)) x += 0.1;
        if (keyPressed(KEY::KEY_SPACE) || keyPressed(KEY::KEY_Q)) rotation -= 0.005;
        if (keyPressed(KEY::KEY_F) || keyPressed(KEY::KEY_E)) rotation += 0.005;
        if (keyPressed(KEY::KEY_Z)) rotation -= 0.05;
        if (keyPressed(KEY::KEY_X)) rotation += 0.05;
        if (keyPressed(KEY::KEY_C)) s -= 0.05;
        if (keyPressed(KEY::KEY_V)) s += 0.05;
        
        drawBackground();

        drawForeground();
        
        // draw third triangle (wow!)

        // glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, )

        //theShader.setMatrix4("projection", transformMatrix(Vector2D(0.0, 0.0), Vector2D(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT), 0.0));
        //theShader.setMatrix4("transform", transformMatrix(Vector2D(x, y), Vector2D(100, 100), rotation));
        unsigned int projectionLocation = glGetUniformLocation(theShader.id, "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, transformMatrix(Vector2D(0.0, 0.0), Vector2D(2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT), 0.0));

        unsigned int transformLocation = glGetUniformLocation(theShader.id, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transformMatrix(Vector2D(x, y), Vector2D(100, 100), rotation));

        theShader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glUseProgram(0);

        /*
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {

                unsigned int transformLocation2 = glGetUniformLocation(theShader.id, "transform");
                glUniformMatrix4fv(transformLocation2, 1, GL_FALSE, transformMatrix(Vector2D(i * 80 - 800, j * 80 - 800), Vector2D(100 * s, 100 * s), rotation));

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);

            }
        }
        */

        glfwSwapBuffers(window);

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    std::cout << "graphics test ends!\n";

    return 0;
}

void resize(GLFWwindow* window, int width, int height) {

    // glViewport(0, 0, width, height);
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);

}

void initializeInput2() {

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