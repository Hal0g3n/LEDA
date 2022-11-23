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

#include <iterator>


// WINDOW_STUFF
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;
const char * WINDOW_NAME = "ok"; // not used
void WINDOW_RESIZE(GLFWwindow* window, int width, int height) {
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
}

void LEDA::initializeDrawer() {

	std::cout << "initializing drawer..." << std::endl;

	glfwInit();

	// OpenGL version 4.6, but use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for os x and ios
	#endif

	// create GLFW window (global)
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, LEDA::windowTitle.c_str(), NULL, NULL);
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
unsigned int triangle_[] = {
	0, 1, 2,
};
float rectangle[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
};
unsigned int rectangle_[] = {
	0, 1, 3,
	1, 2, 3,
};

void LEDA::drawObjects(std::vector<GameObject*> objects) {

	// get a nice map of objects categorised by shapes
	std::unordered_map<std::string, std::vector<GameObject*>> shapes = {};

	for (GameObject* object : objects) {
		GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
		if (graphicsComponent == nullptr) continue;
		std::string shape = graphicsComponent->shape;
		if (shapes.find(shape) == shapes.end()) {
			shapes.emplace(shape, std::initializer_list<GameObject*>{ object });
		}
		else {
			shapes.at(shape).push_back(object);
		}
	}

	// camera projection somethings
	glm::f32* projectionMatrix = transformMatrix(Vector2D(0.0, 0.0), Vector2D(1.0 / WINDOW_WIDTH, 1.0 / WINDOW_HEIGHT), 0.0);

	// actually draw the objects in this loop
	for (std::pair<const std::string, std::vector<GameObject*>> &it : shapes) {

		const std::string shape = it.first;
		
		// bind the shape before drawing all objects with the same shape

		unsigned int VAO = 0, VBO = 0, EBO = 0;

		unsigned int numberOfVertices = 0;

		if (shape == "triangle") {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_), triangle_, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);

			numberOfVertices = std::size(triangle_);
		}
		else if (shape == "rectangle" || shape == "square") {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_), rectangle_, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);

			numberOfVertices = std::size(rectangle_);
		}
		else if (shape == "sus") {
			// TODO: draw an amogus (not so soon)
		}

		for (GameObject* object : it.second) {

			// get transform data
			TransformComponent* transformComponent = getComponent<TransformComponent>(object);
			glm::f32* objectMatrix = transformMatrix(*transformComponent);

			// get shader too
			GraphicsComponent* graphicsComponent = getComponent<GraphicsComponent>(object);
			Shader shader{ graphicsComponent->material };

			// set shader uniforms
			shader.setMatrix4("projection", projectionMatrix);
			shader.setMatrix4("transform", objectMatrix);
			// TODO: replace with object color
			shader.setFloat4("color", 0.0, 0.0, 0.0, 0.0);

			shader.use();

			glBindVertexArray(VAO);
			if (EBO != 0) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			}
			glDrawElements(GL_TRIANGLES, numberOfVertices, GL_UNSIGNED_INT, 0);

		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

	}

}

void LEDA::updateDrawer(std::vector<GameObject*> objects) {

	// draw background colour
	glClearColor(0.123f, 0.456f, 0.789f, 1.0f); // around #1f74c9
	glClear(GL_COLOR_BUFFER_BIT);

	drawObjects(objects);

	glfwSwapBuffers(window);

}

void LEDA::freeDrawer() {

	std::cout << "killing drawer..." << std::endl;

	glfwTerminate();

}