/**
 * @file        Drawer.cpp
 * @author      your name (you@domain.com)
 * @brief       Game object drawing implementation. Not related to a piece of furniture.
 * @version     0.1
 * @date        07-09-2022
 *
 * @copyright   Copyright (c) 2022
 */


#include "pch.h"

#include "LEDA_Graphics.h"
#include "TransformComponent.h"
#include "GraphicsComponent.h"
#include "Drawer.h"

#include <GLFW/glfw3.h>


// WINDOW_STUFF
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;
const char * WINDOW_NAME = "ok";
void WINDOW_RESIZE(GLFWwindow* window, int width, int height) {
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
}

void LEDA::drawInit() {

	glfwInit();

	// OpenGL version 4.6, but use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for os x and ios
	#endif

	// create GLFW window (global)
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (window == NULL) {
		std::cout << "Error: failed to create GLFWindow\n";
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// be glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Error: failed to initialize GLAD! [>:( <-- not glad]\n";
		return;
	}

	// set resize window callback
	glfwSetFramebufferSizeCallback(window, WINDOW_RESIZE);

}

// shapes
float triangle[] = {
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f,
};

void LEDA::drawObjects(std::vector<GameObject*> objects) {

	// get a nice map of objects categorised by materials
	std::unordered_map<std::string, std::vector<GameObject*>> shapes = {};

	for (GameObject* object : objects) {
		GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(*object);
		std::string shape = graphicsComponent->shape;
		if (shapes.find(shape) == shapes.end()) {
			shapes.emplace(shape, std::initializer_list<GameObject*>{ object });
		}
		else {
			shapes.at(shape).push_back(object);
		}
	}

	for (std::pair<const std::string, std::vector<GameObject*>> &it : shapes) {

		const std::string shape = it.first;
		
		// bind the material before drawing all objects with the material

		unsigned int VBO = 0, VAO = 0;

		if (shape == "triangle") {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

			// positions (location 0)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
		}
		else if (shape == "sus") {
			// todo: draw an amogus (not so soon)
		}

		for (GameObject* object : it.second) {

			// get transform data
			TransformComponent* transformComponent = getComponent<TransformComponent>(*object);
			glm::f32* mat = transformMatrix(*transformComponent);

			// get shader too
			GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(*object);
			Shader shader{ graphicsComponent->material };
			
			shader.setMatrix4("projection", transformMatrix(Vector2D(0.0, 0.0), Vector2D(1.0 / WINDOW_WIDTH, 1.0 / WINDOW_HEIGHT), 0.0));
			shader.setMatrix4("transform", mat);

			shader.use();

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

		}
	}

}

// glfwSwapBuffers(window); // ?